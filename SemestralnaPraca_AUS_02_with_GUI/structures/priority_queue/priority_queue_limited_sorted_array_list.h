﻿#pragma once

#include "priority_queue_sorted_array_list.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueLimitedSortedArrayList : public PriorityQueueSortedArrayList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueLimitedSortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueLimitedSortedArrayList(const PriorityQueueLimitedSortedArrayList<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany utriedenym ArrayList-om, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je prioritny front typu PriorityQueueLimitedSortedArrayList. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual PriorityQueueSortedArrayList<T>& operator=(const PriorityQueueSortedArrayList<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		virtual PriorityQueueLimitedSortedArrayList<T>& operator=(const PriorityQueueLimitedSortedArrayList<T>& other);

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front plny. </exception>  
		void push(const int priority, const T& data) override;

		/// <summary>
		///  Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou.
		///  V pripade, ze je prioritny front plny, odstrani polozku s najmensou prioritou z prioritneho frontu a vrati smernik na nu. 
		///  V opacnom pripade vrati nullptr. 
		/// </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		/// <returns> Smernik na odstranenu polozku alebo nullptr. </returns>
		PriorityQueueItem<T>* pushAndRemove(const int priority, const T& data);

		/// <summary> Vrati najmensiu prioritu nachadzajucu sa v prioritnom fronte. </summary>
		/// <returns> Najmensiu priorita nachadzajuca sa v prioritnom fronte. </returns>
		int minPriority() const;

		/// <summary>
		///  Pokusi sa zmenit kapacitu prioritneho frontu. 
		///  Kapacitu je mozne zmensit len ak nova kapacita nie je mensia ako aktualny pocet poloziek v prioritnom fronte. 
		///  V opacnom pripade nedojde k zmene kapacity. 
		/// </summary>
		/// <param name = "capacity"> Nova kapacita. </param>
		/// <returns> true, ak sa kapacitu podarilo zmenit, false inak. </returns>
		bool trySetCapacity(size_t capacity);

	private:
		/// <summary> Kapacita prioritneho frontu. </summary>
		size_t capacity_;
	};

	template<typename T>
	PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList() :
		PriorityQueueSortedArrayList<T>(),
		capacity_(2)
	{
	}

	template<typename T>
	PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(const PriorityQueueLimitedSortedArrayList<T>& other) :
		PriorityQueueSortedArrayList<T>(other),
		capacity_(other.capacity_)
	{
	}

	template<typename T>
	Structure* PriorityQueueLimitedSortedArrayList<T>::clone() const
	{
		return new PriorityQueueLimitedSortedArrayList<T>(*this);
	}

	template<typename T>
	inline PriorityQueueLimitedSortedArrayList<T>& PriorityQueueLimitedSortedArrayList<T>::operator=(const PriorityQueueLimitedSortedArrayList<T>& other)
	{
		if (this == &other) {
			return *this;
		}
		list_->clear();
		capacity_ = other.capacity_;
		for (PriorityQueueItem<T> * item : *other.list_) {
			list_->add(new PriorityQueueItem<T>(*item));
		}
		return *this;
	}

	template<typename T>
	void PriorityQueueLimitedSortedArrayList<T>::push(const int priority, const T & data)
	{
		if (list_->size() < capacity_)
			list_->add(new PriorityQueueItem<T>(priority, data));
		else
			throw std::logic_error("Queue is full!");
	}

	template<typename T>
	inline PriorityQueueItem<T>* PriorityQueueLimitedSortedArrayList<T>::pushAndRemove(const int priority, const T & data) {
		PriorityQueueItem<T>* output;
		int priority_ = minPriority();
		if (priority < minPriority() || list_->size() < capacity_)
			push(priority, data);
		else
			return new PriorityQueueItem<T>(priority, data);
		if (list_->size() > capacity_) {
			for (PriorityQueueItem<T> * item : *list_) {
				if (item->getPriority() == priority_) {
					output = item;
					list_->tryRemove(item);
					return output;
				}
			}
			return nullptr;
		}
		else
			return nullptr;
	}

	template<typename T>
	inline int PriorityQueueLimitedSortedArrayList<T>::minPriority() const
	{
		if (list_->size() == 0)
			return 0;
		int priority = (*list_)[0]->getPriority();
		for (PriorityQueueItem<T> * item : *list_) {
			if (item->getPriority() > priority)
				priority = item->getPriority();
		}
		return priority;
	}

	template<typename T>
	inline bool PriorityQueueLimitedSortedArrayList<T>::trySetCapacity(size_t capacity)
	{
		if (capacity == this->capacity_)
			return false;
		if (capacity < list_->size())
			return false
		else {
			capacity_ = capacity;
			return true;
		}
	}
}

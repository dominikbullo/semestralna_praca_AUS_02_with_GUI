#pragma once
#include"Area.h"

template <typename T, typename O>
class Kriterium
{
public:
	virtual T evaluate(const O& o) const = 0;
};

class KriteriumNazov : public Kriterium<std::string, Area>
{
public:
	std::string evaluate(const Area& a) const override { return a.getName(); }
};

class KriteriumPrislusnostObce : public Kriterium<bool, Obec>
{
public:
	bool evaluate(const Obec& o) const override { return o.isIn(*area_); }
	void setArea(Area* area) { this->area_ = area; }
private:
	Area * area_;
};

class KriteriumVolici : public Kriterium<int, Area>
{
public:
	KriteriumVolici(int kolo) :kolo(kolo) {};
	int evaluate(const Area& a) const override { return a.getPocetVolicov(kolo); }
private:
	int kolo;
};

class KriteriumVydaneObalky : public Kriterium<int, Area>
{
public:
	KriteriumVydaneObalky(int kolo) :kolo(kolo) {};
	int evaluate(const Area& a) const override { return a.getPocetVydanychObalok(kolo); }
private:
	int kolo;
};

class KriteriumUcast : public Kriterium<double, Area>
{
public:
	KriteriumUcast(int kolo) :kolo(kolo) {};
	double evaluate(const Area& a) const override { return a.getUcastVolicov(kolo); }
private:
	int kolo;
};

class KriteriumOdovzdaneObalky : public Kriterium<double, Area>
{
public:
	KriteriumOdovzdaneObalky(int kolo) :kolo(kolo) {};
	double evaluate(const Area& a) const override { return a.getPocetOdovzdanychObalok(kolo); }
private:
	int kolo;
};
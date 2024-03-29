#include "Nacitanie.h"
#define REMOVE_SPACES(x) remove_if(x.begin(), x.end(), isspace);

using namespace std;


Nacitanie::Nacitanie()
{
	krajeSorted = new structures::BinarySearchTree<string, Kraj*>();
	okresySorted = new structures::BinarySearchTree<string, Okres*>();
	obceSorted = new structures::BinarySearchTree<string, Obec*>();

	obceUnsorted = new structures::UnsortedSequenceTable<string, Obec*>();

	this->loadData();
}


Nacitanie::~Nacitanie()
{
	obceUnsorted->clear();
	delete obceUnsorted;

	for (auto * item : *obceSorted)
	{
		delete obceSorted->remove(item->getKey());
	}
	obceSorted->clear();
	delete obceSorted;

	for (auto * item : *okresySorted)
	{
		delete okresySorted->remove(item->getKey());
	}
	okresySorted->clear();
	delete okresySorted;

	for (auto * item : *krajeSorted)
	{
		delete krajeSorted->remove(item->getKey());
	}
	krajeSorted->clear();
	delete krajeSorted;
}

void Nacitanie::loadData()
{
	// NOTE: toto nefunguje spr�vne pri poron�van� oby�ajn�ch stringov,
	//lebo by som musel robi� in� na��tavanie, do wstringov, 
	// t�m p�dom zmeni� komplet na��vatanie & �trukt�ry & GUI...
	// neskoro som si to v�imol, nebol �as to prerobi�.

	this->loadDataKraje("spolu_kraje.csv");
	this->loadDataOkresy("spolu_okresy.csv");
	this->loadDataObce("spolu_obce.csv");

	//this->loadDataKraje("spolu_kraje_without_accents.csv");
	//this->loadDataOkresy("spolu_okresy_without_accents.csv");
	//this->loadDataObce("spolu_obce_without_accents.csv");
}


void Nacitanie::loadDataKraje(string nazovSuboru)
{
	ifstream file(nazovSuboru);
	if (!file.is_open()) cout << "ERROR file OPEN" << endl;
	string tmp, nazovKraja;
	int kolo = -1;

	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku

	while (file.good())
	{
		getline(file, tmp, ';');		// Kod kraja
		getline(file, nazovKraja, ';');	// Nazov kraja

		Kraj* tempArea = new Kraj(nazovKraja);

		kolo = 1;
		getline(file, tmp, ';');	// Po�et okrskov
		getline(file, tmp, ';');	// Po�et zap�san�ch voli�ov

		tempArea->setPocetVolicov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Po�et vydan�ch ob�lok
		tempArea->setPocetVydanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// ��as� voli�ov v %
		tempArea->setUcastVolicov(std::stod(tmp), kolo);
		getline(file, tmp, ';');	// Po�et odovzdan�ch ob�lok
		tempArea->setPocetOdovzdanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Podiel odovzdan�ch ob�lok v %
		getline(file, tmp, ';');	// Po�et platn�ch hlasov v�etk�ch kandid�tov
		tempArea->setPocetPlatnychHlasov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	//  Podiel platn�ch hlasov v�etk�ch kandid�tov v %

		// 2.kolo
		kolo = 2;

		getline(file, tmp, ';');	// Po�et zap�san�ch voli�ov - 2.kolo
		tempArea->setPocetVolicov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Po�et vydan�ch ob�lok - 2.kolo
		tempArea->setPocetVydanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// ��as� voli�ov v % - 2.kolo
		tempArea->setUcastVolicov(std::stod(tmp), kolo);
		getline(file, tmp, ';');	// Po�et odovzdan�ch ob�lok - 2.kolo
		tempArea->setPocetOdovzdanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Podiel odovzdan�ch ob�lok v % - 2.kolo
		getline(file, tmp, ';');	// Po�et platn�ch hlasov v�etk�ch kandid�tov - 2.kolo
		tempArea->setPocetPlatnychHlasov(std::stoi(tmp), kolo);
		getline(file, tmp);	// Podiel platn�ch hlasov v�etk�ch kandid�tov v % - 2.kolo

		this->pridajKraj(tempArea);
	}

}
void Nacitanie::loadDataOkresy(string nazovSuboru)
{
	ifstream file(nazovSuboru);
	if (!file.is_open()) cout << "ERROR file OPEN" << endl;
	string tmp, nazovObce, nazovOkresu, nazovKraja;
	int kolo = -1;

	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku

	while (file.good())
	{
		getline(file, tmp, ';');		// Kod kraja
		getline(file, nazovKraja, ';');	// Nazov kraja
		getline(file, tmp, ';');		// Kod  �zemn�ho obvodu
		getline(file, tmp, ';');	// Nazov  �zemn�ho obvodu
		getline(file, tmp, ';');		// Kod okresu
		getline(file, nazovOkresu, ';');	// Nazov okresu

		Okres* tempArea = new Okres(nazovOkresu, nazovKraja);

		// 1.kolo
		kolo = 1;

		getline(file, tmp, ';');	// Po�et okrskov
		getline(file, tmp, ';');	// Po�et zap�san�ch voli�ov
		tempArea->setPocetVolicov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Po�et vydan�ch ob�lok
		tempArea->setPocetVydanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// ��as� voli�ov v %
		tempArea->setUcastVolicov(std::stod(tmp), kolo);
		getline(file, tmp, ';');	// Po�et odovzdan�ch ob�lok
		tempArea->setPocetOdovzdanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Podiel odovzdan�ch ob�lok v %
		getline(file, tmp, ';');	// Po�et platn�ch hlasov v�etk�ch kandid�tov
		tempArea->setPocetPlatnychHlasov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	//  Podiel platn�ch hlasov v�etk�ch kandid�tov v %

		// 2.kolo
		kolo = 2;

		getline(file, tmp, ';');	// Po�et zap�san�ch voli�ov
		tempArea->setPocetVolicov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Po�et vydan�ch ob�lok
		tempArea->setPocetVydanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// ��as� voli�ov v %
		tempArea->setUcastVolicov(std::stod(tmp), kolo);
		getline(file, tmp, ';');	// Po�et odovzdan�ch ob�lok
		tempArea->setPocetOdovzdanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Podiel odovzdan�ch ob�lok v %
		getline(file, tmp, ';');	// Po�et platn�ch hlasov v�etk�ch kandid�tov
		tempArea->setPocetPlatnychHlasov(std::stoi(tmp), kolo);
		getline(file, tmp);	//  Podiel platn�ch hlasov v�etk�ch kandid�tov v %

		this->pridajOkres(tempArea);
	}
}
void Nacitanie::loadDataObce(string nazovSuboru)
{
	ifstream file(nazovSuboru);
	if (!file.is_open()) cout << "ERROR file OPEN" << endl;
	string tmp, nazovObce, nazovOkresu, nazovKraja;
	int kolo = -1;

	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku
	getline(file, tmp); // vynechaj hlavi�ku

	//while (file.good() && this->obceSorted->size() < 50) {
	while (file.good()) {
		getline(file, tmp, ';');		// Kod kraja
		getline(file, nazovKraja, ';');	// Nazov kraja
		getline(file, tmp, ';');		// K�d �zemn�ho obvodu
		getline(file, tmp, ';');		// N�zov �zemn�ho obvodu

		getline(file, tmp, ';');		// K�d okresu
		getline(file, nazovOkresu, ';');// N�zov okresu

		getline(file, tmp, ';');		// K�d obce
		getline(file, nazovObce, ';');	// N�zov obce

		Obec* tempArea = new Obec(nazovObce, nazovKraja, nazovOkresu);

		// 1. kolo 
		kolo = 1;

		getline(file, tmp, ';');	// Po�et okrskov
		getline(file, tmp, ';');	// Po�et zap�san�ch voli�ov
		tempArea->setPocetVolicov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Po�et vydan�ch ob�lok
		tempArea->setPocetVydanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// ��as� voli�ov v %
		tempArea->setUcastVolicov(std::stod(tmp), kolo);
		getline(file, tmp, ';');	// Po�et odovzdan�ch ob�lok
		tempArea->setPocetOdovzdanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Podiel odovzdan�ch ob�lok v %
		getline(file, tmp, ';');	// Po�et platn�ch hlasov v�etk�ch kandid�tov
		tempArea->setPocetPlatnychHlasov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	//  Podiel platn�ch hlasov v�etk�ch kandid�tov v %

		// 2.kolo
		kolo = 2;

		getline(file, tmp, ';');	// Po�et zap�san�ch voli�ov
		tempArea->setPocetVolicov(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Po�et vydan�ch ob�lok
		tempArea->setPocetVydanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// ��as� voli�ov v %
		tempArea->setUcastVolicov(std::stod(tmp), kolo);
		getline(file, tmp, ';');	// Po�et odovzdan�ch ob�lok
		tempArea->setPocetOdovzdanychObalok(std::stoi(tmp), kolo);
		getline(file, tmp, ';');	// Podiel odovzdan�ch ob�lok v %
		getline(file, tmp, ';');	// Po�et platn�ch hlasov v�etk�ch kandid�tov
		tempArea->setPocetPlatnychHlasov(std::stoi(tmp), kolo);
		getline(file, tmp);	//  Podiel platn�ch hlasov v�etk�ch kandid�tov v %

		this->pridajObec(tempArea);
	}
}
void Nacitanie::pridajObec(Obec* area)
{
	// NOTE mo�nos� upravy met�dy insert -> met�da nevie poriadne porovn�va� UNICODE znaky
	if (obceSorted->containsKey(area->getName())) {
		area->makeUniqueNazov();
		cout << "Find duplicates -> renamed to: " << area->getName() << endl;
	}

	area->calculateSumValuesForBothRounds();
	obceSorted->insert(area->getName(), area);
	obceUnsorted->insertHard(area->getName(), area);
}
void  Nacitanie::pridajOkres(Okres* area)
{
	area->calculateSumValuesForBothRounds();
	okresySorted->insert(area->getName(), area);
}

void  Nacitanie::pridajKraj(Kraj* area)
{
	area->calculateSumValuesForBothRounds();
	krajeSorted->insert(area->getName(), area);
}
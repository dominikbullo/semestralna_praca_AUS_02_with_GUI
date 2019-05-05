#pragma once
#include <iostream> 
#include <string> 
using namespace std;
class Area
{
public:
	Area(std::string nazov);
	~Area();

	std::string getName() const { return this->nazov; }
	void toString();

	int getPocetVydanychObalok() { return this->pocetVydanychObalok; }
	int getPocetOdovzdanychObalok() { return this->pocetOdovzdanychObalok; }
	int getPocetPlatnychHlasov() { return this->pocetPlatnychHlasov; }
	int getPocetVolicov() { return this->pocetVolicov; }
	float getUcastVolicov() { return this->ucast; }

	void setPocetVydanychObalok(int pocet) { this->pocetVydanychObalok = pocet; }
	void setPocetOdovzdanychObalok(int pocet) { this->pocetOdovzdanychObalok = pocet; }
	void setPocetPlatnychHlasov(int pocet) { this->pocetPlatnychHlasov = pocet; }
	void setPocetVolicov(int pocet) { this->pocetVolicov = pocet; }
	void setUcastVolicov(float pocet) { this->ucast = pocet; }

private:
	std::string nazov;

	int pocetVydanychObalok;
	int pocetOdovzdanychObalok;
	int pocetPlatnychHlasov;
	int pocetVolicov;

	float ucast;

protected:
	void setName(std::string name) { this->nazov = name; };
};

class Kraj : public Area
{
public:
	Kraj(std::string nazov) : Area(nazov)
	{
		cout << "Created Kraj " << nazov << endl;
	}
};

class Okres : public Area
{
public:
	Okres(std::string nazov, std::string nazovKraja) :
		nazovKraja(this->nazovKraja), Area(nazov)
	{
		cout << "Created Okres " << nazov << endl;
	}
private:
	std::string nazovKraja;
};

class Obec : public Area
{
public:
	Obec(std::string nazov, std::string nazovKraja, std::string nazovOkresu) :
		nazovKraja(nazovKraja), nazovOkresu(nazovOkresu), Area(nazov)
	{
		cout << "Created Obec " << nazov << endl;
	}
	bool isIn(Area& area);
	void makeUniqueNazov();
	void makeUniqueVolici();
	void makeUniqueUcast();

private:
	std::string nazovKraja;
	std::string nazovOkresu;
};


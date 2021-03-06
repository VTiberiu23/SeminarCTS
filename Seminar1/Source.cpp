#include "pch.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

// Modificarile propuse se gasesc pe linile 12, 13, 29, 108, 178

enum TipTranzactie { INTRARE, IESIRE };

// 1.Toate { si } sa fie pe linii individuale
// 2.Contructorii sa fie delimitati de spatii pentru a putea fi mai vizibili
struct Tranzactie {
	TipTranzactie tip;
	float valoare;
	Tranzactie() {
		tip = INTRARE;
		valoare = 0;
	}
	Tranzactie(TipTranzactie v_tip, float v_valoare) {
		tip = v_tip;
		valoare = v_valoare;
	}
	friend ostream& operator<<(ostream& co, const Tranzactie& t);
	friend istream& operator>>(istream& ci, Tranzactie& t);
};

// 3.Evitarea folosirii prescurtarilor sau explicarea lor prin comentarii pentru a putea fi intelese mai bine; Ex: co si ci 
ostream& operator<<(ostream& co, const Tranzactie& t) {
	co << "Tranzactie tip ";
	if (t.tip == INTRARE)
		cout << "INTRARE";
	else
		cout << "IESIRE";
	co << " in valoare de " << t.valoare << " lei.";
	return co;
}

istream& operator>>(istream& ci, Tranzactie& t) {
	int aux;
	cout << "CITIRE TRANZACTIE" << endl;
	cout << "Tip Tranzactie( 1 - INTRARE / 2 - IESIRE ): ";
	cin >> aux;
	if (aux == 1)
		t.tip = INTRARE;
	else
		t.tip = IESIRE;
	cout << "Valoare: ";
	ci >> t.valoare;
	return ci;
}

class ContBancar {
protected:
	string titular;
	unsigned int nr_tranzactii;
	Tranzactie* tranzactii;
	float sold;
	const string IBAN;

	string static genereazaIBAN();
public:
	ContBancar();
	ContBancar(string v_titular, unsigned int v_nr_tranzactii, Tranzactie* v_tranzactii, float v_sold, string v_IBAN);
	ContBancar(string v_titular, unsigned int v_nr_tranzactii = 0, Tranzactie* v_tranzactii = NULL, string v_IBAN = genereazaIBAN());
	ContBancar(const ContBancar& c);
	~ContBancar();

	string getTitular();
	void setTitular(string v_titular);
	int getNrTranzactii();
	void setNrTranzactii(unsigned int v_nr_tranzactii);
	Tranzactie* getTranzactii();
	void setTranzactii(Tranzactie* v_tranzactii, unsigned int v_nr_tranzactii);
	float getSold();
	void setSold(float v_sold);
	string getIBAN();

	void afisare();

	ContBancar& operator=(const ContBancar& c);
	friend ostream& operator<<(ostream& co, const ContBancar& c);
	friend istream& operator>>(istream& ci, ContBancar& c);
	Tranzactie operator[](int index);
	ContBancar& operator++();
	ContBancar operator++(int);
	ContBancar& operator--();
	ContBancar operator--(int);
	ContBancar& operator+=(const ContBancar& c);
	ContBancar& operator+=(float plus_sold);
	bool operator<(const ContBancar& c);
	bool operator>(const ContBancar& c);
	bool operator==(const ContBancar& c);
	bool operator>=(const ContBancar& c);
	bool operator<=(const ContBancar& c);
	ContBancar operator!();
	string operator()();
	operator int();
	operator float();
	operator string();
	ContBancar operator+(const ContBancar& c);
	ContBancar operator+(float plus_sold);
	ContBancar operator-(const ContBancar& c);
	ContBancar operator-(float minus_sold);
};

// 4.Main-ul sa fie la final de cod, nu la mijlocul sau
int main()
{
	srand(time(NULL));

	cout << endl << "CONSTRUCTOR DEFAULT (c)" << endl;
	ContBancar c;
	c.afisare();

	cout << endl << "CONSTRUCTOR TOTI PARAMETRII (c1)" << endl;
	Tranzactie tranzactii[] = { Tranzactie(INTRARE, 200), Tranzactie(IESIRE, 150.5), Tranzactie(INTRARE, 99.23) };
	ContBancar c1(string("Anton Andreea"), 3, tranzactii, 253.4, string("RO00TEST0000000000000000"));
	c1.afisare();

	cout << endl << "CONSTRUCTOR VALORI IMPLICITE (c2)" << endl;
	ContBancar c2(string("Popescu Ion"));
	c2.afisare();

	cout << endl << "GETTERI SI SETTERI" << endl;
	cout << "c1(c-tor toti parametrii) are: " << endl;
	cout << "IBAN: " << c1.getIBAN() << endl;
	cout << "Titular: " << c1.getTitular() << endl;
	cout << "Sold: " << c1.getSold() << endl;
	cout << "Nr. Tranzactii: " << c1.getNrTranzactii() << endl;
	Tranzactie* tranzactii2 = c1.getTranzactii();
	if (tranzactii) {
		for (int i = 0; i < c1.getNrTranzactii(); i++) {
			cout << i + 1 << ". " << tranzactii2[i] << endl;
 		}
	}

	cout << endl << "c1 modificat: " << endl;
	Tranzactie tranzactii3[] = { Tranzactie(IESIRE, 2200), Tranzactie(IESIRE, 38.5) };
	c1.setTitular("Mircea Cartarescu");
	c1.setSold(1.2);
	c1.setTranzactii(tranzactii3, 2);
	c1.afisare();

	cout << endl << "OPERATOR =" << endl;
	c2 = c1;
	cout << c2 << endl;
	
	cout << endl << "OPERATOR >>" << endl;
	cin >> c2;
	cout << endl << "CONT BANCAR: " << endl << c2 << endl;

	cout << endl << "OPERATOR []" << endl;
	int index;
	cout << "Index:"; cin >> index;
	cout << c2[index] << endl;

	cout << endl << "OPERATOR ++" << endl;
	cout << "-> pre:" << endl << ++c2;
	cout << "Sold: " << c2.getSold() << endl << endl;
	cout << "-> post:" << endl << c2++;
	cout << "Sold: " << c2.getSold() << endl;

	cout << endl << "OPERATOR --" << endl;
	cout << "-> pre: " << endl << --c2;
	cout << "Sold: " << c2.getSold() << endl << endl;;
	cout << "-> post: " << endl << c2--;
	cout << "Sold: " << c2.getSold() << endl;

	cout << endl << "OPERATOR +=" << endl;
	cout << c2 << c1 << endl;
	c2 += c1;
	cout << "-> modificare: " << endl << c2 << endl;

	cout << endl << "OPERATORI <,>,==,>=,<=" << endl;

	// 5.Folosirea { } pentru if else chiar daca este doar o linie de cod la fiecare
	if (c2 < c1)
		cout << c2.getTitular() << " are un sold mai mic ca " << c1.getTitular() << endl;
	else 
		cout << c2.getTitular() << " NU are un sold mai mic ca " << c1.getTitular() << endl;
	if (c2 > c1)
		cout << c2.getTitular() << " are un sold mai mare ca " << c1.getTitular() << endl;
	else
		cout << c2.getTitular() << " NU are un sold mai mare ca " << c1.getTitular() << endl;
	if (c2 == c1)
		cout << c2.getTitular() << " are un sold egal cu cel al lui " << c1.getTitular() << endl;
	else
		cout << c2.getTitular() << " NU are un sold egal cu cel al lui " << c1.getTitular() << endl;
	if (c2 >= c1)
		cout << c2.getTitular() << " are un sold mai mare sau egal ca " << c1.getTitular() << endl;
	else
		cout << c2.getTitular() << " NU are un sold mai mare sau egal ca " << c1.getTitular() << endl;
	if (c2 <= c1)
		cout << c2.getTitular() << " are un sold mai mic sau egal ca " << c1.getTitular() << endl;
	else
		cout << c2.getTitular() << " NU are un sold mai mic sau egal ca " << c1.getTitular() << endl;

	cout << endl << "OPERATOR !" << endl;
	cout << !c2 << endl;

	cout << endl << "OPERATOR ()" << endl;
	cout << c2() << endl;

	cout << endl << "OPERATORI CAST" << endl;
	cout << "-> int(): " << int(c2) << endl;
	cout << "-> float(): " << float(c2) << endl;
	cout << "-> string(): " << string(c2) << endl;

	cout << endl << "OPERATORI +,-" << endl;
	cout << "c2 = " << endl << c2 << "c1 = " << endl << c1 << endl;
	cout << "-> + obiect: " << endl << c2 + c1 << endl;
	cout << "-> + float: " << endl <<  c2 + float(503.24) << endl;
	cout << "-> - obiect: " << endl << c2 - c1 << endl;
	cout << "-> - float: " << endl << c2 - float(503.24) << endl;

	return 0;
}

string ContBancar::genereazaIBAN() {
	string IBAN = "RO";
	string primeleDoua = to_string(rand() % 9 + 1) + to_string(rand() % 9 + 1);
	string ind_banca = "RZBR";
	string ultimele = "";
	for (int i = 0; i < 16; i++) {
		ultimele += to_string(rand() % 9 + 1);
	}
	IBAN += primeleDoua + ind_banca + ultimele;

	return IBAN;
}

ContBancar::ContBancar() 
	: IBAN(genereazaIBAN())
{
	this->titular = "Necunoscut";
	this->nr_tranzactii = 0;
	this->tranzactii = NULL;
	this->sold = 0.0;
}
ContBancar::ContBancar(string v_titular, unsigned int v_nr_tranzactii, Tranzactie* v_tranzactii, float v_sold, string v_IBAN) 
	: IBAN(v_IBAN)
{
	this->titular = v_titular;
	this->nr_tranzactii = v_nr_tranzactii;
	if (v_tranzactii) {
		this->tranzactii = new Tranzactie[this->nr_tranzactii];
		for (int i = 0; i < this->nr_tranzactii; i++) {
			this->tranzactii[i] = v_tranzactii[i];
		}
	}
	else {
		this->tranzactii = NULL;
	}
	this->sold = v_sold;
}
ContBancar::ContBancar(string v_titular, unsigned int v_nr_tranzactii, Tranzactie* v_tranzactii, string v_IBAN)
	:  IBAN(v_IBAN)
{
	this->titular = v_titular;
	this->nr_tranzactii = v_nr_tranzactii;
	if (v_tranzactii) {
		this->tranzactii = new Tranzactie[this->nr_tranzactii];
		for (int i = 0; i < this->nr_tranzactii; i++) {
			this->tranzactii[i] = v_tranzactii[i];
		}
	}
	else {
		this->tranzactii = NULL;
	}
	this->sold = 0.0;
}
ContBancar::ContBancar(const ContBancar& c) 
	: IBAN(c.IBAN)
{
	this->titular = c.titular;
	this->nr_tranzactii = c.nr_tranzactii;
	if (c.tranzactii) {
		this->tranzactii = new Tranzactie[this->nr_tranzactii];
		for (int i = 0; i < this->nr_tranzactii; i++) {
			this->tranzactii[i] = c.tranzactii[i];
		}
	}
	else {
		this->tranzactii = NULL;
	}
	this->sold = c.sold;
}
ContBancar::~ContBancar() {
	if (this->tranzactii)
		delete[] this->tranzactii;
}

string ContBancar::getTitular() {
	return this->titular;
}
void ContBancar::setTitular(string v_titular) {
	this->titular = v_titular;
}
int ContBancar::getNrTranzactii() {
	return this->nr_tranzactii;
}
void ContBancar::setNrTranzactii(unsigned int v_nr_tranzactii) {
	this->nr_tranzactii = v_nr_tranzactii;
}
Tranzactie* ContBancar::getTranzactii() {
	return this->tranzactii;
}
void ContBancar::setTranzactii(Tranzactie* v_tranzactii, unsigned int v_nr_tranzactii) {
	if (v_tranzactii) {
		this->nr_tranzactii = v_nr_tranzactii;
		if (this->tranzactii) {
			delete[] this->tranzactii;
		}
		this->tranzactii = new Tranzactie[this->nr_tranzactii];
		for (int i = 0; i < this->nr_tranzactii; i++) {
			this->tranzactii[i] = v_tranzactii[i];
		}
	}
}
float ContBancar::getSold() {
	return this->sold;
}
void ContBancar::setSold(float v_sold) {
	this->sold = v_sold;
}
string ContBancar::getIBAN() {
	return this->IBAN;
}

void ContBancar::afisare() {
	cout << "IBAN: " << this->IBAN << endl;
	cout << "Titular: " << this->titular << endl;
	cout << "Sold: " << this->sold << " lei" << endl;
	cout << "Nr. tranzactii: " << this->nr_tranzactii << endl;
	if (this->tranzactii) {
		for (int i = 0; i < this->nr_tranzactii; i++) {
			cout << i + 1 << ". " << this->tranzactii[i] << endl;
		}
	}
	cout << endl;
}

ostream& operator<<(ostream& co, const ContBancar& c) {
	co << "IBAN: " << c.IBAN << endl;
	co << "Titular: " << c.titular << endl;
	co << "Sold: " << c.sold << " lei" << endl;
	co << "Nr. tranzactii: " << c.nr_tranzactii << endl;
	if (c.tranzactii) {
		for (int i = 0; i < c.nr_tranzactii; i++) {
			co << i + 1 << ". " << c.tranzactii[i] << endl;
		}
	}
	co << endl;
	return co;
}
istream& operator>>(istream& ci, ContBancar& c) {
	cout << "CITIRE CONT BANCAR" << endl;
	cout << "Titular: "; 
	getline(ci, c.titular);
	cout << "Sold: ";
	ci >> c.sold;
	cout << "Nr. Tranzactii: ";
	ci >> c.nr_tranzactii;
	if (c.tranzactii)
		delete[] c.tranzactii;
	c.tranzactii = new Tranzactie[c.nr_tranzactii];
	for (int i = 0; i < c.nr_tranzactii; i++) {
		cout << i + 1 << ". ";
		ci >> c.tranzactii[i];
	}
	return ci;
}
ContBancar& ContBancar::operator=(const ContBancar& c) {
	this->titular = c.titular;
	this->nr_tranzactii = c.nr_tranzactii;
	if (this->tranzactii) {
		delete[] this->tranzactii;
	}
	if (c.tranzactii) {
		this->tranzactii = new Tranzactie[this->nr_tranzactii];
		for (int i = 0; i < this->nr_tranzactii; i++) {
			this->tranzactii[i] = c.tranzactii[i];
		}
	}
	else {
		this->tranzactii = NULL;
	}
	this->sold = c.sold;

	return *this;
}
Tranzactie ContBancar::operator[](int index) {
	if (index >= 0 && index < this->nr_tranzactii && this->tranzactii) {
		return this->tranzactii[index];
	}
}
ContBancar& ContBancar::operator++() {
	this->sold++;
	return *this;
}
ContBancar ContBancar::operator++(int) {
	ContBancar c = *this;
	this->sold++;
	return c;
}
ContBancar& ContBancar::operator--() {
	this->sold--;
	return *this;
}
ContBancar ContBancar::operator--(int) {
	ContBancar c = *this;
	this->sold--;
	return c;
}
ContBancar& ContBancar::operator+=(const ContBancar& c) {
	this->sold += c.sold;
	return *this;
}
ContBancar& ContBancar::operator+=(float plus_sold) {
	this->sold += plus_sold;
	return *this;
}
bool ContBancar::operator<(const ContBancar& c) {
	return this->sold < c.sold;
}
bool ContBancar::operator>(const ContBancar& c) {
	return this->sold > c.sold;
}
bool ContBancar::operator==(const ContBancar& c) {
	return this->sold == c.sold;
}
bool ContBancar::operator>=(const ContBancar& c) {
	return this->sold >= c.sold;
}
bool ContBancar::operator<=(const ContBancar& c) {
	return this->sold <= c.sold;
}
ContBancar ContBancar::operator!() {
	ContBancar gol;
	return gol;
}
string ContBancar::operator()() {
	return this->IBAN;
}
ContBancar::operator int() {
	return this->nr_tranzactii;
}
ContBancar::operator float() {
	return this->sold;
}
ContBancar::operator string() {
	return this->titular;
}
ContBancar ContBancar::operator+(const ContBancar& c) {
	ContBancar rez = *this;
	rez.sold += c.sold;
	return rez;
}
ContBancar ContBancar::operator+(float plus_sold) {
	ContBancar rez = *this;
	rez.sold += plus_sold;
	return rez;
}
ContBancar ContBancar::operator-(const ContBancar& c) {
	ContBancar rez = *this;
	rez.sold -= c.sold;
	return rez;
}
ContBancar ContBancar::operator-(float minus_sold) {
	ContBancar rez = *this;
	rez.sold -= minus_sold;
	return rez;
}
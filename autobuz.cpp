#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Autobuz
{
private:
	const int idAutobuz;
	static int nrAutobuze;
	int capacitate;
	int nrPersoaneImbarcate;
	char* producator;

public:
	Autobuz() : idAutobuz(++nrAutobuze)
	{
		this->capacitate = 0;
		this->nrPersoaneImbarcate = 0;
		this->producator = new char[strlen("NA") + 1];
		strcpy(this->producator, "NA");
	}

	// constructorul cu parametri contine validari
	Autobuz(int capacitateInit, int nrPersoaneImbarcateInit, char* producatorInit) : idAutobuz(++nrAutobuze)
	{
		if (capacitateInit > 0)
			this->capacitate = capacitateInit;
		else
			this->capacitate = 0;

		if (nrPersoaneImbarcateInit >= 0 && nrPersoaneImbarcateInit <= this->capacitate)
			this->nrPersoaneImbarcate = nrPersoaneImbarcateInit;
		else
			this->nrPersoaneImbarcate = 0;

		if (producatorInit != nullptr)
		{
			this->producator = new char[strlen(producatorInit) + 1];
			strcpy(this->producator, producatorInit);
		}
		else
		{
			this->producator = new char[strlen("NA") + 1];
			strcpy(this->producator, "NA");
		}
	}

	~Autobuz()
	{
		if (this->producator != nullptr)
		{
			delete[] this->producator;
		}
	}

	Autobuz(const Autobuz& f) : idAutobuz(++nrAutobuze)
	{
		this->capacitate = f.capacitate;
		this->nrPersoaneImbarcate = f.nrPersoaneImbarcate;
		this->producator = new char[strlen(f.producator) + 1];
		strcpy(this->producator, f.producator);
	}

	// get si set
	char* getProducator()
	{
		char* copieProducator = new char[strlen(this->producator) + 1];
		strcpy(copieProducator, this->producator);
		return copieProducator;
	}

	void setProducator(char* producatorNou)
	{
		if (producatorNou != nullptr)
		{
			if (this->producator != nullptr)
			{
				delete[] this->producator;
			}
			this->producator = new char[strlen(producatorNou) + 1];
			strcpy(this->producator, producatorNou);
		}
	}

	int getCapacitate()
	{
		return this->capacitate;
	}

	void setCapacitate(int capacitateNoua)
	{
		if (capacitateNoua > 0 && capacitateNoua >= this->nrPersoaneImbarcate)
		{
			this->capacitate = capacitateNoua;
		}
	}

	// op=
	Autobuz& operator=(const Autobuz& f)
	{
		// p0 protectie auto-atribuire
		if (this == &f)
		{
			return *this;
		}
		// p1 dezaloc ce am dinamic
		if (this->producator != nullptr)
		{
			delete[] this->producator;
		}
		// p2 refac obiectul dupa f
		this->capacitate = f.capacitate;
		this->nrPersoaneImbarcate = f.nrPersoaneImbarcate;
		this->producator = new char[strlen(f.producator) + 1];
		strcpy(this->producator, f.producator);
		// p3 return *this
		return *this;
	}

	// afisare pe aceeasi linie, separat prin "; "
	friend ostream& operator<<(ostream& out, const Autobuz& f)
	{
		out << f.idAutobuz << "; ";
		out << f.capacitate << "; ";
		out << f.nrPersoaneImbarcate << "; ";
		out << f.producator;
		return out;
	}
};

int Autobuz::nrAutobuze = 0;

int main()
{
	Autobuz a1;

	char prod[] = "Mercedes";
	Autobuz a2(50, 20, prod);
	Autobuz a3(30, 40, prod);          // 40 > 30, deci nrPersoaneImbarcate = 0
	cout << a2 << endl;
	cout << a3 << endl;

	Autobuz a4 = a2;                   // constructor de copiere
	cout << a4 << endl;

	a2.setCapacitate(60);
	cout << a2.getCapacitate() << endl;
	a2.setCapacitate(10);              // respins, 20 persoane nu incap
	cout << a2.getCapacitate() << endl;

	char* p = a2.getProducator();
	cout << p << endl;
	delete[] p;

	char prodNou[] = "Volvo";
	a2.setProducator(prodNou);
	p = a2.getProducator();
	cout << p << endl;
	delete[] p;

	Autobuz a5;
	a5 = a2;                           // operator=
	a5 = a5;                           // auto-atribuire
	cout << a5 << endl;

	return 0;
}
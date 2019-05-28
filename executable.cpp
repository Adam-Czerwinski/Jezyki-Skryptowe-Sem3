#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Dzialanie {
private:
	int a;
	int b;
	char znak;
public:
	Dzialanie() {
		a = 0; b = 0; znak = ' ';
	}
	Dzialanie(int a, int b, char znak) {
		this->a = a; this->b = b; this->znak = znak;
	}

	bool operator==(const Dzialanie &ob) const {

		if ((znak == '+' && ob.znak == '+') || (znak == '*' && ob.znak == '*'))
		{
			if ((a == ob.a && b == ob.b) || (a == ob.b && b == ob.a))
				return true;
		}

		if (a == ob.a && b == ob.b && znak == ob.znak)
			return true;

		return false;
	}

	friend ostream& operator<<(ostream &os, const Dzialanie &ob);

};

ostream& operator<<(ostream &os, const Dzialanie &ob) {
	os << ob.a << " " << ob.znak << " " << ob.b << " = ";
	if (ob.znak == '+')
		os << ob.a + ob.b;
	else if (ob.znak == '-')
		os << ob.a - ob.b;
	else if (ob.znak == '*')
		os << ob.a * ob.b;
	else if (ob.znak == '/')
		os << ob.a / ob.b;
	else
		os << "Problem ze znakiem!";
	os << endl;
	return os;
}

bool sprawdzCzyPierwsza(int val) {

	if (val < 2)
		return false;

	bool isPrime = true;

	for (int i = 2; i <= val / 2; ++i)
	{
		if (val % i == 0)
		{
			isPrime = false;
			break;
		}
	}

	return isPrime;
}

int main(int argc, char *argv[]) {

	vector<int> dane;
	int temp{};
	string filepathIN = argv[1];
	ifstream fileRead(filepathIN);
	string filenameIN;
	int pom{};
	int count = 0;
	pom = filepathIN.find_last_of('\\');
	filenameIN.assign(filepathIN, pom + 1, filepathIN.size());

	//----------------------------------WCZYTYWANIE DANYCH Z PLIKU
	//Sprawdzenie czy siê uda³o otworzyæ plik
	if (!fileRead.is_open())
	{
		cout << "Nie udalo sie otworzyc pliku " << filenameIN << endl;

		system("goto :Koniec");
		return 10;
	}
	
	//Wczytywanie danych z pliku
	while (!fileRead.eof())
	{
		if (!(fileRead >> temp))
			break;

		dane.push_back(temp);
		count++;					//zliczenia WSZYSTKICH danych
	}	
	fileRead.close();
	
	//Pozbycie siê zduplikowanych danych
	for (int i = 0; i < dane.size(); i++)
	{
		for (int j = 0; j < dane.size(); j++)
		{
			if (i == j)
				continue;

			if (dane.at(i) == dane.at(j))
			{
				dane.erase(dane.begin() + i);
				j--;								//po u¿yciu metody erase iterator siê przesuwa (nie wnika³em) dlatego trzeba j--
			}
		}
	}
	//----------------------------------KONIEC WCZYTYWANIA DANYCH Z PLIKU



	//----------------------------------WERYFIKACJA DANYCH
	if (count < 2)
	{
		cout << "Za malo danych! W pliku " << filenameIN << " musza znajdowac sie przynajmniej 2 wartosci calkowite!" << endl;
		return 3;
	}

	if (fileRead.eof())
	{
		cout << "Pomyslnie wczytano dane z pliku " << filenameIN << endl;
	}else if (fileRead.fail())
	{
		cout << "Sprawdz poprawnosc wprowadzonych danych w pliku " << filenameIN << endl;
		return 1;
	}else if (fileRead.bad())
	{
		cout << "Problem z wczytaniem danych z pliku " << filenameIN << endl;
		return 2;
	}
	

	//----------------------------------KONIEC WERYFIKACJI DANYCH



	//----------------------------------OBLICZENIA
	vector<Dzialanie> obliczenia;
	int dodawanie;
	int odejmowanie;
	int mnozenie;
	int dzielenie;
	int reszta;
	for (int i = 0; i < dane.size(); i++)
	{
		for (int j = 0; j < dane.size(); j++)
		{
			if (i == j)
				continue;

			dodawanie = dane.at(i) + dane.at(j);
			odejmowanie = dane.at(i) - dane.at(j);
			mnozenie = dane.at(i) * dane.at(j);

			if (dane.at(j) != 0)
			{
				reszta = dane.at(i) % dane.at(j);
				if (!reszta) {
					dzielenie = dane.at(i) / dane.at(j);
					if (sprawdzCzyPierwsza(dzielenie))
						obliczenia.push_back(Dzialanie(dane.at(i), dane.at(j), '/'));
				}
			}
			if (sprawdzCzyPierwsza(dodawanie))
				obliczenia.push_back(Dzialanie(dane.at(i), dane.at(j), '+'));
			if (sprawdzCzyPierwsza(odejmowanie))
				obliczenia.push_back(Dzialanie(dane.at(i), dane.at(j), '-'));
			if (sprawdzCzyPierwsza(mnozenie))
				obliczenia.push_back(Dzialanie(dane.at(i), dane.at(j), '*'));
		}
	}

	/*cout << "Przed:" << endl;
	for (int i = 0; i < obliczenia.size(); i++)
	{
		cout <<i<<": "<< obliczenia.at(i);
	}*/

	//Pozbycie siê zduplikowanych wyników
	for (int i = 0; i < obliczenia.size(); i++)
	{
		for (int j = 0; j < obliczenia.size(); j++)
			if (i != j)
				if (obliczenia.at(i) == obliczenia.at(j))
				{
					obliczenia.erase(obliczenia.begin() + i);
					j--;
				}
	}
	
	/*cout << "Po" << endl;
	for (int i = 0; i < obliczenia.size(); i++)
	{
		cout <<i<<": "<< obliczenia.at(i);
	}*/

	//---------------------------------KONIEC OBLICZEÑ



	//---------------------------------WYPISANIE DANYCH DO PLIKU
	string filenameOut = filenameIN;

	//zmienienie np. in1.txt na out1.txt
	filenameOut[0] = 'o';
	filenameOut[1] = 'u';
	filenameOut.insert(filenameOut.begin() + 2, 't');

	//zamienienie œcie¿ki z ...\in\in1.txt na np ...\out\out1.txt
	string filepathOut;
	filepathOut.assign(filepathIN.begin(), filepathIN.end() - 10);
	filepathOut += "out\\" + filenameOut;

	ofstream fileWrite(filepathOut);

	for (int i = 0; i < obliczenia.size(); i++)
	{
		fileWrite << obliczenia.at(i);
	}

	fileWrite.close();

	//----------------------------------KONIEC WYPISYWANIA DANYCH DO PLIKU

	return 0;
}

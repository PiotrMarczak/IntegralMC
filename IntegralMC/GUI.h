//Klasy i funkcje s³u¿¹ce do komukijacji z urzytkowinikiem

#ifndef GUI_h
#define GUI_h

using namespace std;

//Klasa zajmuj¹ca siê komunikowaniem z uzytkownikiem.
//wyœwietlanie i pobieranie danych
class GUI
{
private:
	//spis zdan dla terminala
	//tytul pracy
	string tytul = "Obliczanie calki metoda Monte Carlo z wykorzystaniem technik CUDA, OpenMP, MPI.";
	//rozdzialy
	string roz_1 = "1: Wykryj dostepne urzadzenia";
	string roz_2 = "2: Kalibracja urzadzen";
	string roz_3 = "3: Wybierz urzadzenia";
	string roz_4 = "4: Wprowadz funkcje do calkowania";
	string roz_5 = "5: Oblicz calke funkcji";
	string roz_0 = "0: Wyjdz";
	//rozmowa z urzytkownikem
	string podaj_dane_menu_glowne = "wybierz numer i potwierdz ";

	//zmienne klasy
	//zmienna sterowanie terminala



public:
	GUI();
	~GUI();

	int terminal_sterujacy = 0;

	//Obsluga pracy z urzytkownikiem
	
	void ekran_glowny();//ekran glowny
	
	void Dane_urzadzen(Device_Sum *D_S_T, int MPISize);//wyswietla dane urz¹dzeñ
	
	int wprowadzanie_danych();//Pobieranie danych od urzytkownika



};





#endif
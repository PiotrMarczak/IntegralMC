#include "stdafx.h"

using namespace std;

GUI::GUI()
{
}
GUI::~GUI()
{
}

//napisz zabezpieczenie danych
int GUI::wprowadzanie_danych() {
	int zmienna_wlasna;
	cin >> zmienna_wlasna;
	if (!cin)
	{
		cout << "wprowadzono zle \n";

		cin.clear(); // czyœcimy flagi b³êdu strumienia
		cin.sync(); // czyœcimy bufor strumienia
	}
	else
	{
		return zmienna_wlasna;

	}

	return 0;
}

//przypisanie rozdzialow do tablicy
void GUI::ekran_glowny() {

	//wyswietl rozdzialy
	cout << tytul << "\n";
	cout << roz_1 << "\n";
	cout << roz_2 << "\n";
	cout << roz_3 << "\n";
	cout << roz_4 << "\n";
	cout << roz_5 << "\n";
	cout << roz_0 << "\n";
	cout << podaj_dane_menu_glowne << endl;

}

void GUI::Dane_urzadzen(Device_Sum *D_S_T, int MPISize){
	cout << "Wykryta ilosc hostow: " << MPISize << endl;
	for (int i = 0; i < MPISize; i++) {
		cout << "Jestem: " << D_S_T[i].host_name << " host: " << D_S_T[i].id_host << endl;
		cout << "Rdzeni procesora: " << D_S_T[i].core_size << endl;
		cout << "Zgodnych kart graficznych: " << D_S_T[i].cuda_size << endl;
		for (int j = 0; j < D_S_T[i].cuda_size; j++) {
			cout << "GPU " << j << " : " << D_S_T[i].cuda_name[j] << endl;
			cout << "-----------" << endl;
		}
	}
}
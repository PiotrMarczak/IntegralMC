#include "stdafx.h"

using namespace std;

SP::SP()
{
}

long double SP::func_case2(double x) {//funkcja Dla cache 2 dla testów wydajnoœci sprzetu [return 2*x/2]Prosta Fun dla obci¹¿enia
	return 2*x/2;
}



//struktura danych o sprzêcie
Device_Sum::Device_Sum()
{
};










//[TEST]//////////////////////////////
void SP::timetest() {
	int a = 2, b = 2, c;
	c = a + b;
	cout << c << endl;
};

void SP::time_test_All() {
	const int N = 100000;
	int zmtest = 2;
	MPIMC MPIMC;
	cudaMC cudaMC;

	clock_t ct1, ct2, ct2end;//czas c							 
	double mt1, mt2, mtend;//czas mpi
	cudaEvent_t cut1, cut2;//czas cuda
	float cutend;
	cudaEventCreate(&cut1);
	cudaEventCreate(&cut2);	
	double ot1, ot2, otend;//czas omp

	ct1 = clock();
	mt1 = MPI_Wtime();
	cudaEventRecord(cut1, 0);
	ot1 = omp_get_wtime();

	MPIMC.mpi_out_send(zmtest, 1);
	Sleep(1000);//c
	cudaMC.call_kernel();
	MPIMC.mpi_in_recv(zmtest, 1);

	int i, a[N];
#pragma omp parallel for
	for (i = 0; i < N; i++) {
		a[i] = 2 * i;
	}

	ct2 = clock();
	mt2 = MPI_Wtime();
	cudaEventRecord(cut2, 0);
	ot2 = omp_get_wtime();

	ct2end = difftime(ct2, ct1);
	mtend = mt2 - mt1;
	otend = ot2 - ot1;
	cudaEventSynchronize(cut2);
	cudaEventElapsedTime(&cutend, cut1, cut2);
	cudaEventDestroy(cut1);
	cudaEventDestroy(cut2);



	cout << fixed << setprecision(2);
	cout << "clock c++ dif " << setprecision(5) << ct2end << endl;
	cout << "clock mpi " << setprecision(5) << mtend << endl;
	cout << "clock cuda " << setprecision(5) << cutend << endl;
	cout << "clock omp " << setprecision(5) << otend << endl;
	cout << "zmtest " << zmtest << endl;

}

void SP::test_rand() {

	// Generator liczb losowych
	std::mt19937 gen{ std::random_device{}() };
	// Rozklad jednorodny na przedziale -1.0 do 1.0
	std::uniform_real_distribution<double> losuj{ -1., 1. };

	int punktow_w_kwadracie=100000;    // Liczba punktow w kwadracie
	int punktow_w_kole = 0;     // Liczba punktow w kole

								// Liczby punktow mozemy przyjac jako dyskretna forme pola powierzchni,
								// stad, im wiecej punktow zalozymy, tym lepsza dokladnosc liczby pi

	cout << "Podaj liczbe losowanych punktow: ";
	//cin >> punktow_w_kwadracie;

	double x, y;
	for (int i{ 0 }; i < punktow_w_kwadracie; ++i)
	{
		x = losuj(gen);
		y = losuj(gen);

		// Sprawdzamy czy wylosowany punkt o wspolrzednych (x, y)
		// znajduje sie w kole o wzorze x^2 + y^2 = 1
		// Wzor ten okresla kolo wpisane w kwadrat na przedziale
		// x i y = <-1, 1>

		if (x*x + y * y <= 1)
		{
			// Akceptujemy punkty w kole
			++punktow_w_kole;
		}
	}

	// Wiemy, ze pole powierzchni kola wpisanego w kwadrat o boku 1
	// wynosi dokladnie pi/4. Stosunek pola tego kola do kwadratu to
	// tez pi/4. A wiec aby uzyskac przyblizenie liczby pi wystarczy
	// policzyc stosunek punktow_w_kole do punktow_w_kwadracie razy 4

	cout << "Liczba punktow w kole = " << punktow_w_kole << endl;
	cout << "Liczba punktow w kwadracie = " << punktow_w_kwadracie << endl;
	double _PI_ = 4. * punktow_w_kole / punktow_w_kwadracie;
	cout << "Szukana liczba pi = " << _PI_ << endl<<"-------------------------------------------"<<endl;

	
}

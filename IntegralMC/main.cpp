// helloMPI.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.

/*Program s³u¿¹cy przedstawieniu programowania równoleh³ego wykorzystuj¹cego techniki MPI OpenMP CUDA
na przyk³adzie obliczania ca³ki metod¹ Monte Carlo*/

#include "stdafx.h"

//using namespace std;

//Zmienne i sta³e globalne


int main(int argc, char *argv[]) {

//Zmienne programowe
	int MPISize;//u¿ywane jako iloœæ hostów
	int MPIRank;//u¿ywane jako id hosta
	char MPIName[MPI_MAX_PROCESSOR_NAME];//zmienna przechowujaca nazwe hosta
	int MPIName_length;//dlugosc nazwy hosta
	int CORESize;//zmienna wewnêtrzna hosta podaj¹ca iloœæ rdzeni
	int CORERank;//zmienna wewnêtrzna hosta podaj¹ca id rdzenia
	int CUDASize;//zmienna wewnêtrzna hosta podaj¹ca iloœæ kart graficznych
	int CUDARank;//zmienna wewnêtrzna hosta podaj¹ca numer karty graficznej
	cudaDeviceProp  CUDAProp;//Dane o karcieGPU
	int CUDAName_length = 256;
	int i, j, k;//zmienne iteracyjne
	int MPIEnd = 1;//zmienna pêtli programu przechowuj¹ca stan wybranego menu

//zmienne obslugi/klasy
	SP SP;//klasa operacji programowych
	MPIMC MPIMC;//Klasa obs³uguj¹ca MPI
	cudaMC cudaMC;//Klasa obs³ugi CUDA
//Zmienne dla nodeRoot
	GUI GD;//obs³óga graficzna wymagana tylko w nodeZero (tekst terminala)	
	Device_Sum *D_S_T;//Device Set Table //klasa przechowuj¹ca dane sprzêtu

	//zmienne tymczasowe do usuniêcia w wersji finalnej
	MPI_Status stat;//do usuniêcia po prze¿uceniu mpi do klas

//MPI  Ogrodzenie programu w MPI
	MPI_Init(NULL, NULL);
	int VT_timesync();

	MPIMC.MPIMCSize();
	MPISize = MPIMC.MPISize;

	MPIMC.MPIMCRank();
	MPIRank = MPIMC.MPIRank;

	//nazwa hosta
	MPI_Get_processor_name(MPIName, &MPIName_length);

	//iloœæ rdzeni procesora
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);	
	int numCPU = sysinfo.dwNumberOfProcessors;

	//dane o GPU
	cudaGetDeviceCount(&CUDASize);

//Pêtla programu
	while (MPIEnd!=0) {

//MPI obsluga host zero, wprowadzanie danych, rozsy³anie i zbieranie danych
		if (MPIRank == 0) {
			cout <<"[TEST] "<< "jestem" << MPIRank << endl;///////////////////////////////////////////////////
			//panel urzytkownika
			GD.ekran_glowny();
			//zapytaj o wybor
			SP.stan_menu = GD.wprowadzanie_danych();
			//MPI Rozsy³anie wyboru manu
			MPIMC.mpi_out_bcast(SP.stan_menu, 0);
			cout << "[TEST] " << 0 << SP.stan_menu<< endl;///////////////////////////////////////////////////////
///////odpowiedzi programu nodeZero na wybór urzytkownika cahe/////////////////////////			

				long double wynik_func;
				mt19937 gen_liczb{random_device{}() };// Generator liczb losowych
				uniform_real_distribution<long double> rand_xy{ -1.0, 1.0 };// Rozklad jednorodny na przedziale -1.0 do 1.0
				int punktow_w_kwadracie; // Liczba punktow w kwadracie
				int punktow_w_func = 0;     // Liczba punktow w kole
				int i, nRet = 0, nSum = 0, nStart = 1, nEnd = 8;
				int nThreads = 0, nTmp = nStart + nEnd;
				long double x=0, y=0;
				int OMP_num_CPU = numCPU;

			switch (SP.stan_menu)
			{
			case 1:
				MPIMC.mpi_in_DST(D_S_T, numCPU);
				GD.Dane_urzadzen(D_S_T,MPISize);

				break;


			case 2://test wydajnoœci urzadzeñ dla F(x)=2*x/2 w przedziale -1<=x<=1 i -1<=y<=1 wynik d¹¿y do Zera.

				cout << fixed << setprecision(10);
				punktow_w_kwadracie = 1;
				cout << "ustaw punkty (*1 000 000): " << endl;
				cin >> punktow_w_kwadracie;
				punktow_w_kwadracie *=1000000;
				cout << "ustaw ilosc rdzeni: " << endl;
				cin >> OMP_num_CPU;
				//zaimplementowaæ czas wykonywania
				int VT_timesync();
				double t1, t2;

				t1 = MPI_Wtime();
#pragma omp parallel for private(x,y) reduction(+:punktow_w_func) num_threads(OMP_num_CPU)

				for (i = 0; i < punktow_w_kwadracie; i++)
				{
					long double sum_x = 0;


					x = rand_xy(gen_liczb);
					cout << "x: " << x << endl;
					y = rand_xy(gen_liczb);

					if ((y > 0) && (y <= SP.func_case2(x))) {	//testy z zawieraniem zera
						punktow_w_func++;
					}
					else if ((y < 0) && (y >= SP.func_case2(x))) {
						punktow_w_func--;
					}

				}
				t2 = MPI_Wtime();

				cout << "Liczba punktow w polu funkcji = " << punktow_w_func << endl;
				cout << "Liczba punktow w ca³ym polu = " << punktow_w_kwadracie << endl;
				wynik_func = ((long double)punktow_w_func / (long double)punktow_w_kwadracie);// *(2) * (2);
				cout << "Calka F(x)=2*x/2 powinna dazyc do zera: = " << wynik_func << endl << "-------------------------------------------" << endl;
				cout << "obliczenia trwa³y : " << t2 - t1 << endl;

		


				break;
			default:
				break;
			}

			//sprawdzic czy node!0 wykona³o odpowiedni switch						 
			//Sprawdzanie czy zamknac program w nodeZero
			if (SP.stan_menu == 0) {
				MPIEnd = 0;

				for (i = 0; i < MPISize; i++) {

				}
	//czyszczenie pamieci w nodeZero
			}
		}



////////////////////////////////////////////
//MPI obsluga reszty node
		if (MPIRank != 0) {
			//zmienne wewnetrzne reszty watkow
			cout << "[TEST] " << "jestem" << MPIRank << endl;/////////////////////////////////////////////////////
			//MPI Pobieranie wyboru menu
			MPIMC.mpi_in_bcast(SP.stan_menu, 0);
			cout << "[TEST] " << 1 << SP.stan_menu << endl;//////////////////////////////////////////////


			switch (SP.stan_menu)
			{
			case 1: {
				MPIMC.mpi_out_DST(numCPU,cudaMC);
				break;
			}
			case 2:
				int zmtest;

				//MPIMC.mpi_in_recv(zmtest, 0);	
				Sleep(1000);
				SP.timetest();
				cudaMC.call_kernel();
				zmtest *= zmtest;
				//MPIMC.mpi_out_send(zmtest, 0);



				break;
			default:
				break;
			}
			cout << "[TEST] " << "text case 1-4" << endl;

//Sprawdzanie czy zakonczyc program w node!0
			if (SP.stan_menu == 0) {
				MPIEnd = 0;
	//czyszczenie pamieci w node!0
			}

		}

	}


//MPI zakoñczenie
	MPI_Finalize();
//Koniec programu
	return 0;
}


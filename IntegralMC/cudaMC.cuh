//Klasy i funkcje obs³ugi CUDA
//#include "stdafx.h"
#ifndef cudaMC_cuh
#define cudaMC_cuh
using namespace std;



class cudaMC
{
private:

public:
	cudaMC();
	int CUDASize();//zmienna wewnêtrzna hosta podaj¹ca iloœæ kart graficznych
	int CUDARank;//zmienna wewnêtrzna hosta podaj¹ca numer karty graficznej

	int CUDAName_length();
	void call_kernel() ;
	void cuRand_test();

};


#endif

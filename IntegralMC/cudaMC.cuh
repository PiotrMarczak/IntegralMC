//Klasy i funkcje obs�ugi CUDA
//#include "stdafx.h"
#ifndef cudaMC_cuh
#define cudaMC_cuh
using namespace std;



class cudaMC
{
private:

public:
	cudaMC();
	int CUDASize();//zmienna wewn�trzna hosta podaj�ca ilo�� kart graficznych
	int CUDARank;//zmienna wewn�trzna hosta podaj�ca numer karty graficznej

	int CUDAName_length();
	void call_kernel() ;
	void cuRand_test();

};


#endif

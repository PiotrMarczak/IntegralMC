#include "stdafx.h"


using namespace std;

cudaMC::cudaMC()
{
}
int cudaMC::CUDASize() {
	int CUDASize;
	cudaGetDeviceCount(&CUDASize);
	return CUDASize;
}
int cudaMC::CUDAName_length() {
	return 256;
}



//[TEST]///////////////////////////////////

__global__
void my_kernel() {
	clock_t ct1, ct2, ctend;

	ct1 = clock();

	while (ctend < 1000) {
		ct2 = clock();
		ctend = ct2 - ct1;
	}

}

void cudaMC::call_kernel() {
	// prepare data for the kernel, e.g. allocating memory, copying from host to device, etc.
	//czas cuda

	// run kernel
	my_kernel << < 10,10>> >();

	// copy results from device to host, clean up, etc.
}

void cudaMC::cuRand_test() {

	curandGenerator_t genGPU;
	curandGenerator_t genCPU;

	curandCreateGenerator(&genGPU, CURAND_RNG_PSEUDO_MTGP32);
	curandSetPseudoRandomGeneratorSeed(genGPU, 1234ULL);
	curandCreateGeneratorHost(&genCPU, CURAND_RNG_PSEUDO_MTGP32);
	curandSetPseudoRandomGeneratorSeed(genCPU, 1234ULL);

	const int n = 10;
	double CPU[n];
	double GPU[n];

	double* d_GPU;
	cudaMalloc(&d_GPU, n * sizeof(double));

	curandGenerateUniformDouble(genCPU, CPU, n);
	curandGenerateUniformDouble(genGPU, d_GPU, n);
	cudaMemcpy(GPU, d_GPU, n * sizeof(double), cudaMemcpyDeviceToHost);

	for (int i = 0; i < n; ++i) {
		cout << CPU[i] << ' ' << GPU[i] << endl;
	}

	curandDestroyGenerator(genGPU);
	curandDestroyGenerator(genCPU);
	cudaFree(d_GPU);
}
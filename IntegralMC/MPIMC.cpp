#include "stdafx.h"

using namespace std;

MPIMC::MPIMC()
{
}


void MPIMC::MPIMCRank() {
	MPI_Comm_rank(MPI_COMM_WORLD, &MPIRank);
}

void MPIMC::MPIMCSize() {
	MPI_Comm_size(MPI_COMM_WORLD, &MPISize);
}

void MPIMC::mpi_out_send(int &x, int node) {
	MPI_Send(&x, 1, MPI_INT, node, 1, MPI_COMM_WORLD);
};
void MPIMC::mpi_in_recv(int &x, int node) {
	MPI_Recv(&x, 1, MPI_INT, node, 1, MPI_COMM_WORLD, &stat);
};

void MPIMC::mpi_out_bcast(int &x, int node) {
	MPI_Bcast(&x, 1, MPI_INT, node, MPI_COMM_WORLD);
};
void MPIMC::mpi_in_bcast(int &x, int node) {
	MPI_Bcast(&x, 1, MPI_INT, node, MPI_COMM_WORLD);
}

void MPIMC::mpi_in_DST(Device_Sum *&D_S_T, int numCPU) {
	cudaMC cudaMC;
	cudaDeviceProp  CUDAProp;//Dane o karcieGPU

	D_S_T = new Device_Sum[MPISize];//uzupe³nianie danych o nodeZero
	D_S_T[0].id_host = MPIRank;
	MPI_Get_processor_name(MPIName, &MPIName_length);
	D_S_T[0].host_name = MPIName;
	D_S_T[0].core_size = numCPU;
	D_S_T[0].cuda_size = cudaMC.CUDASize();
	D_S_T[0].cuda_name = new char*[D_S_T[0].cuda_size];

	for (int i = 0; i < D_S_T[0].cuda_size; i++) {//Przypisanie nazw CUDA w nodeZero
		D_S_T[0].cuda_name[i] = new char[cudaMC.CUDAName_length()];
		cudaGetDeviceProperties(&CUDAProp, i);
		strcpy(D_S_T[0].cuda_name[i], CUDAProp.name);
	}
	for (int i = 1; i < MPISize; i++) {//pobieranie danych urz¹dzeñ z node!0
		D_S_T[i].id_host = i;
		int length;
		MPI_Recv(&length, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &stat);
		D_S_T[i].host_name = new char[length];
		MPI_Recv(D_S_T[i].host_name, length + 1, MPI_CHAR, i, 1, MPI_COMM_WORLD, &stat);
		MPI_Recv(&D_S_T[i].core_size, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &stat);
		MPI_Recv(&D_S_T[i].cuda_size, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &stat);
		D_S_T[i].cuda_name = new char*[D_S_T[i].cuda_size];
		for (int j = 0; j < D_S_T[i].cuda_size; j++) {
			D_S_T[i].cuda_name[j] = new char[cudaMC.CUDAName_length()];
			MPI_Recv(D_S_T[i].cuda_name[j], cudaMC.CUDAName_length() + 1, MPI_CHAR, i, 1, MPI_COMM_WORLD, &stat);
		}
	}
};

void MPIMC::mpi_out_DST(int numCPU, cudaMC cudaMCX) {
	cudaMC cudaMC;
		cudaDeviceProp  CUDAProp;//Dane o karcieGPU
	int length;
	MPI_Get_processor_name(MPIName, &length);
	MPI_Send(&length, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	MPI_Send(MPIName, length + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);//host name
	MPI_Send(&numCPU, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);//n cpu
	int cudaSize = cudaMC.CUDASize();
	MPI_Send(&cudaSize, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	for (int j = 0; j < cudaMC.CUDASize(); j++) {
		cudaGetDeviceProperties(&CUDAProp, j);
		MPI_Send(CUDAProp.name, cudaMC.CUDAName_length() + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	}
};
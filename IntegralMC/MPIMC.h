//Klasy i funkcje obs�ugi MPI


#ifndef MPIMC_h
#define MPIMC_h


using namespace std;


class MPIMC
{
private:
	//spis zdan dla terminala
	MPI_Status stat;

	//zmienne klasy

public:
	MPIMC();

	int MPIRank;
	int MPISize;
	char MPIName[MPI_MAX_PROCESSOR_NAME];//zmienna przechowujaca nazwe hosta
	int MPIName_length;//dlugosc nazwy hosta

	
	void MPIMCRank();
	void MPIMCSize();

	void mpi_out_send(int &x, int node);//ma�o u�yteczne//////////////////////////
	void mpi_out_bcast(int &x, int node);//ma�o u�yteczne///////////////////////////
	void mpi_in_recv(int &x, int node);
	void mpi_in_bcast(int &x, int node);

	void mpi_in_DST(Device_Sum *&D_S_T, int numCPU);//uzupe�nienie klasy danych urz�dze�
	void mpi_out_DST(int numCPU, cudaMC cudaMCX);//wysy�anie danyz z node!0 do nodeZero
};







#endif#pragma once

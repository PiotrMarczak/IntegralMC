//Klasy i funkcje s�u��ce do ogulnego sterowania programem

#ifndef SP_h
#define SP_h


using namespace std;


class SP
{
private:
	//spis zdan dla terminala


	//zmienne klasy


public:
	SP();

	long double func_case2(double x);


	void time_test_All();
	void test_rand();


	int stan_menu=1;//zmienna przechowujaca stan menu glownego

 void timetest();

};
//struktura danych o sprz�cie
class Device_Sum
{
private:

public:
	Device_Sum();


	int id_host;
	char *host_name;
	int core_size=0;
	int cuda_size=0;

	char **cuda_name;



};





#endif
// stdafx.h: do³¹cz plik do standardowych systemowych plików do³¹czanych,
// lub specyficzne dla projektu pliki do³¹czane, które s¹ czêsto wykorzystywane, ale
// s¹ rzadko zmieniane
//

#pragma once

#include "targetver.h"

#include "mpi.h"
#include <omp.h>

#include "cuda.h"
#include "cuda_runtime.h"
#include <curand.h>

#include <ctime>
#include <thread>
#include <random>

#include <string>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include "stdlib.h"
#include <iomanip>  

#include <Windows.h>
#include <WinBase.h>

#include "cudaMC.cuh"
#include "OMPMC.h"
#include "SP.h"
#include "MPIMC.h"
#include "GUI.h"




// TODO: W tym miejscu odwo³aj siê do dodatkowych nag³ówków wymaganych przez program
using namespace std;
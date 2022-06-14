#include "Repair.h"
#include "RepairParallelInd.h"
#include "metrictime2.hpp"
#include <time.h>
using namespace std;

int main(int argc, char const *argv[]){
	srand(time(NULL));
	vector<int> datos; 
	
    if(argc != 3){
        cout<<" uso: "<<argv[0]<<" \"n°hebras\" \"n°datos \"" << endl;
        return 1;
    }
    int nThreads = atoi(argv[1]);
    int nDatos = atoi(argv[2]);
    if(nThreads > nDatos) nThreads = nDatos;

    cout << "Threads: "<< nThreads << ", Datos: "<< nDatos << endl; 

	for(int i = 0; i<nDatos; i++) datos.push_back(1);
	//for(auto i : datos) cout << i << " ";
	cout << endl;
	
	
	TIMERSTART(repair);	
	Repair* r = new Repair(&datos);
	r->cambiar();
	r->prints();
	TIMERSTOP(repair);
	delete(r);
	//r2->prints();	


	TIMERSTART(repairParallel);	
	RepairParallelInd(&datos, nThreads);
	TIMERSTOP(repairParallel);


	return 0;
}




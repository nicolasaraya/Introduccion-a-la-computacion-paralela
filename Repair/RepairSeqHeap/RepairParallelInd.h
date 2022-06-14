#ifndef RepairParallel_h
#define RepairParallel_h
#include <iostream>
#include <omp.h>
#include "DList.h"
#include "Repair.h"

using namespace std;

void RepairParallelInd(vector<int> datos, int nThreads);
void mergeDList(DList* a, DList* b);


void RepairParallelInd(vector<int> datos, int nThreads){
	int nDatos = datos.size();
	
	int partSize = nDatos/nThreads; 

    vector< vector<int> > subDatos(nThreads, vector<int>(0,0));

	cout << "Tamaño de cada parte: " << partSize << endl;

    int k = 0;
    for(int i = 0; i < nThreads; i++){
        for(int j = 0; j < partSize; j++){
            subDatos.at(i).push_back(datos.at(k));
            k++;
        }
    }
    cout << "k = " << k << endl;
    while(k!=datos.size()){
        subDatos.at(nThreads-1).push_back(datos.at(k));
        k++;
    }
    
    vector<DList*> res(nThreads, new DList());
    
    omp_set_num_threads(nThreads);
    //#pragma omp parallel for
    for(int i = 0; i < nThreads; i++){
        Repair* r = new Repair(subDatos.at(i));
        r->cambiar();
        cout << "Thread: " << i << endl; 
        r->prints();
        res.at(i) = r->getSeq();
    }

    cout << "*****" << endl; 
    for(int i = nThreads-1; i>0; i--){
        mergeDList(res.at(i-1), res.at(i));
        res.pop_back();
    }
   

    Repair* r = new Repair(res.at(0));
    r->cambiar();
    r->prints();




	return;
}




void mergeDList(DList* a, DList* b){
    Nodo* tailA = a->back();
    Nodo* firstB = b->first();
    a->merge(a,b);
    tailA->setNext(firstB);
    firstB->setPrev(tailA);

}



#endif
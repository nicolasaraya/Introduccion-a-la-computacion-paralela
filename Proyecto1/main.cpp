//g++ main.cpp -fopenmp -lm

#include <iostream>
#include <vector>
#include <omp.h>
#include <time.h>
#include <math.h>
#include "./metrictime2.hpp"
#define cache 64


using namespace std;

void print(vector<vector<int>> v, int nDatos, int nThreads);

void sequential(vector<vector<int>> * in, vector<vector<int>>* out){
    out->at(0).at(0) = in->at(0).at(0);
    for (int i = 1; i < in->size(); i++){
        out->at(i).at(0) = out->at(i-1).at(0) + in->at(i).at(0);
    }
}

void parallel(vector<vector<int>>* in, vector<vector<int>>* out, int nThreads){
    //int * aux = (int*)malloc(sizeof(int) * NDATOS);
    vector<vector<int>> aux(in->size(), vector<int> (cache, 0) );;

    #pragma omp parallel for
    for(int i = 0; i < in->size(); i++){
        aux.at(i).at(0)= in->at(i).at(0);
        out->at(i).at(0) = in->at(i).at(0);
    }
    
    TIMERSTART(paralelo);
    for(int i = 0; i < ceil(log2(out->size())); i++){
        #pragma omp parallel for
        for(int j = (1<<i); j < out->size(); j++){
            out->at(j).at(0) += aux.at((j-(1<<i))).at(0);
        }
        #pragma omp parallel for
        for (int j = (1<<i); j < out->size(); j++){
            aux.at(j).at(0) = out->at(j).at(0);
        }
        
    }
    TIMERSTOP(paralelo);
}

void print(vector<vector<int>> v, int nDatos, int nThreads){
    for(int i = 0; i < nDatos; i++){
        if (i % (nDatos/nThreads) == 0) cout << "  ";
        cout << v[i][0] << " ";
    }
    cout << endl;
}


int main(int argc, char const *argv[]){
    srand(time(NULL));
    int NTHREADS;
    int NDATOS;
    if(argc != 3){
        cout<<" uso: "<<argv[0]<<" \"n°hebras\" \"n°datos \"" << endl;
        return 1;
    }

    NTHREADS = atoi(argv[1]);
    NDATOS = atoi(argv[2]);
    
    vector< vector<int> > in(NDATOS, vector<int> (cache, 0) ); 
    vector< vector<int> > out(NDATOS, vector<int> (cache, 0) );

    cout << "Threads: "<< NTHREADS << ", Datos: "<< NDATOS << endl;

    omp_set_num_threads(NTHREADS);
    for (int i = 0; i < NDATOS; i++){
        in[i][0] = rand()%10;
        in[i][0] = i;
    }


    
    parallel(&in , &out, NTHREADS);
    print (in, NDATOS, NTHREADS);
    print (out, NDATOS, NTHREADS);

    TIMERSTART(secuencial);
    //sequential(&in, &out);
    TIMERSTOP(secuencial);
    cout << endl;


    //free
    in.clear();
    in.shrink_to_fit();
    out.clear();
    out.shrink_to_fit();




    return 0;
}

//g++ main.cpp -fopenmp -lm

#include <iostream>
#include <vector>
#include <omp.h>
#include <time.h>
#include <math.h>
#include "./metrictime2.hpp"


using namespace std;

void sequential(int * in, int* out, int NDATOS){
    out[0] = in[0];
    for (int i = 1; i < NDATOS; i++){
        out[i] = out[i-1] + in[i];
    }
}

void parallel(int* in, int* out, int NDATOS){
    int * aux = (int*)malloc(sizeof(int) * NDATOS);
  

    #pragma omp parallel for
    for(int i = 0; i < NDATOS; i++){
        aux[i]= in[i];
        out[i] = in[i];
    }
    
    TIMERSTART(paralelo);
    for(int i = 0; i < ceil(log2(NDATOS)); i++){
        
        #pragma omp parallel for
        for(int j = 1 << i; j < NDATOS; j++){
            int aux = out[j] +  out[j - (1 << i)];
            out[j] = aux; 
        }
                            
        #pragma omp parallel for
        for (int j = 1 << i; j < NDATOS; j++){
            aux[j] = out[j];
        }
        
    }
    TIMERSTOP(paralelo);
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
    
    vector< vector<int> > in(NDATOS+9, vector<int> (cache, 0) ); 
    vector< vector<int> > out(NDATOS+9, vector<int> (cache, 0) );

    omp_set_num_threads(NTHREADS);
    #pragma omp parallel for
    for (int i = 0; i < NDATOS; i++){
        in[i] = (rand()%NDATOS);
    }

    /*
    for (int i = 0; i < NDATOS; i++){
        cout << in[i] << " "; 
    }
    cout << endl; */

    
    parallel(in, out, NDATOS);
    

    TIMERSTART(secuencial);
    sequential(in, out, NDATOS);
    TIMERSTOP(secuencial);


    /*    
    for (int i = 0; i < NDATOS; i++){
        cout << in[i] << " "; 
    }
    cout << endl; 
    for (int i = 0; i < NDATOS; i++){
        cout << out[i] << " "; 
    }
    cout << endl; */

    return 0;
}

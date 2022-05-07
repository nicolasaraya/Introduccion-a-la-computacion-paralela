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

    out[0] = in[0];

    #pragma omp parallel for
    for(int i = 0; i < NDATOS; i++){
        aux[i]= in[i];
        out[i] = in[i];
    }

    for(int i = 0; i < ceil(log2(NDATOS)); i++){
        #pragma omp parallel for
        for(int j = pow(2, i); j < NDATOS; j++){
            out[j] +=  aux[ j - (int)pow(2,i) ];
        }
        //esta va pal nico 🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝🤝👌👌👌👌🤞🤞🖖🖖🤘👌🤙🤙🤙🤙🤙
        //holaaaaaaaaaaaaaaaaaaaaa🤙🤙🤙🤙🤙🤙👈🙏🙏🙏🙏🙏🙏🙏🙏🙏🙏
        #pragma omp parallel for
        for (int j = pow(2, i); j < NDATOS; j++){
            aux[j] = out[j];
        }
    }
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

    int * in = (int*)malloc(sizeof(int) * NDATOS);
    int * out = (int*)malloc(sizeof(int) * NDATOS);

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

    TIMERSTART(paralelo);
    parallel(in, out, NDATOS);
    TIMERSTOP(paralelo);

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

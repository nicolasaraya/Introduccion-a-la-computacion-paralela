
//g++ main.cpp -fopenmp -lm

#include <iostream>
#include <vector>
#include <omp.h>
#include <time.h>
#include <math.h>
#include "./metrictime2.hpp"


using namespace std;

void sequential(vector<vector<int>> * in, vector<vector<int>>* out){
    out->at(0).at(0) = in->at(0).at(0);
    for (int i = 1; i < in->size(); i++){
        out->at(i).at(0) = out->at(i-1).at(0) + in->at(i).at(0);
    }
}

void sequentialParalell(vector<vector<int>>* in, vector<vector<int>>* out, int l, int r, bool b){
    if( b ) out->at(l).at(0) = in->at(l).at(0);
    for (int i = l+1; i < r; i++){
        out->at(i).at(0) = out->at(i-1).at(0) + in->at(i).at(0);
    }
}


void parallel(vector<vector<int>>* in, vector<vector<int>>* out, int nThreads){
    
    int part = in->size() / nThreads; 
    int limits[nThreads][2];
    limits[0][0] = 0;
    limits[0][1] = part;
    for(int i = 1; i < nThreads; i++){
        limits[i][0] = part + limits[i-1][0];
        limits[i][1] = part + limits[i-1][1];
        if( limits[i][1] > in->size() ) limits[i][1] = in->size();
    }

    
    #pragma omp parallel for
    for(int i = 0; i < nThreads; i++){
        //cout << "l: " << l << " r: "<< r << endl;
        sequentialParalell(in, out, limits[i][0],limits[i][1], true);
    }

    for(int i = 2; i < nThreads; i++){  
        out->at( (i*part) - 1).at(0) += out->at( ((i-1)*(part))- 1).at(0);    
    }

    #pragma omp parallel for
    for(int i = 1; i < nThreads; i++){
        //cout << "l: " << l << " r: "<< r << endl;
        sequentialParalell(in, out, limits[i][0]-1,limits[i][1]-1, false);
    }
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
    int nThreads, nDatos; 
    if(argc != 3){
        cout<<" uso: "<<argv[0]<<" \"n°hebras\" \"n°datos \"" << endl;

        return 1;
    }

    nThreads = atoi(argv[1]);
    nDatos = atoi(argv[2]);
    if(nThreads > nDatos) nThreads = nDatos;
    
    vector< vector<int> > in(nDatos+9, vector<int> (32, 0) ); 
    vector< vector<int> > out(nDatos+9, vector<int> (32, 0) );

    
    for (int i = 0; i < nDatos; i++){
        in[i][0] = rand()%10;
        in[i][0] = i;
    }
    
    
    omp_set_num_threads(nThreads);
    
    TIMERSTART(paralelo);
    parallel(&in, &out, nThreads);
    TIMERSTOP(paralelo);
    
    TIMERSTART(secuencial);
    sequential(&in, &out);
    TIMERSTOP(secuencial);
    
    //print (in, nDatos, nThreads);
    //print (out, nDatos, nThreads);

    
    return 0;
}

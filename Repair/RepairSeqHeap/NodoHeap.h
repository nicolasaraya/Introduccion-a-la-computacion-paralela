#ifndef NODOHEAP_H
#define NODOHEAP_H

#include <iostream>
#include <vector>


using namespace std;

class NodoHeap{
    private:
        int frecuencia;
        pair<int, int> par;
    public:
        NodoHeap(int, int);
        ~NodoHeap();
        int getFrecuencia();
        void setFrecuencia(int);
        pair<int,int> getPar();
};

#endif
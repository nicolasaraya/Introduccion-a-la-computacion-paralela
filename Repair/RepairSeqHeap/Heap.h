#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <map>
#include "Nodo.h"
#include "NodoHeap.h"

using namespace std; 

typedef struct{
    Nodo* PrimeraOc;
    Nodo* UltimaOc;
    NodoHeap* pos;
    int posHeap;  
}Data;

class Heap{
    private:
        vector<NodoHeap*> arr;
        map<pair<int, int>,Data*>* mp; 
    public:
        Heap(map<pair<int, int>,Data*>*);
        ~Heap();
        void push(NodoHeap*);
        void pop();
        void verify(int);
        void verifyDown(int);
        void prints();
        NodoHeap* top();
        bool empty();
        int size();
        

};

#endif
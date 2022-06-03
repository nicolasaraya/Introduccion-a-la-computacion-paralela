#include "NodoHeap.h"

using namespace std;

NodoHeap::NodoHeap(int x, int y){
    par.first = x;
    par.second = y; 
    frecuencia = 1;
}
NodoHeap::~NodoHeap(){
}
int NodoHeap::getFrecuencia(){
    return frecuencia; 
}
void NodoHeap::setFrecuencia(int n){
    frecuencia = n; 
}
pair<int,int> NodoHeap::getPar(){
    return par; 
}
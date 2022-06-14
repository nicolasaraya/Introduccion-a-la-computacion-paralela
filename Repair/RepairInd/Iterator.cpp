#include "Iterator.h"

using namespace std;

Iterator::Iterator(Nodo* h, Nodo* t){
    tail=t;
    movil=h; 
}
Iterator::~Iterator(){
}
bool Iterator::hasNext(){
    if(movil == NULL){
        return false;
    }
    else return true; 
}
Nodo* Iterator::next(){
    Nodo* x = movil;
    movil = movil->getNext();
    return x; 
}


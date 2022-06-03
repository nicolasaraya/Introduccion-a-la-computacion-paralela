#include "Nodo.h"

using namespace std;

Nodo::Nodo(){
    sig = NULL;
    prev = NULL;
}
Nodo::~Nodo(){
}
Nodo* Nodo::getNext(){
    return sig;
}
void Nodo::setNext(Nodo* n){
    sig=n;
}
Nodo* Nodo::getPrev(){
    
    return prev;
}
void Nodo::setPrev(Nodo* p){
    prev=p;
}
int Nodo::getNum(){
    return numero;
}
void Nodo::setNum(int n){
    numero = n;
}
void Nodo::setOS(Nodo* n){
    OS=n;
}
void Nodo::setOP(Nodo* n){
    OP=n;
}
Nodo* Nodo::getOP(){
    return OP;
}
Nodo* Nodo::getOS(){    
    return OS;
}

#include "Repairv1.h"

using namespace std;


Repairv1::Repairv1(DList* seq){
    this->seq = seq;
    mayor = 27;
}


Repairv1::~Repairv1(){
    
}
pair <int,int> Repairv1::obtenerPrimerMayorFrec(){
    pair <int,int> num;
    Iterator it = seq->begin();
    int frec = 0;
    while(it.hasNext()){
        Nodo* n = it.next();
        if(it.hasNext()==false)break;
        int a = n->getNum();
        int b = n->getNext()->getNum();
        
        mp[{a, b}]++;
        
        if(mp[{a, b}]>frec){
            frec = mp[{a, b}];
            num.first = a;
            num.second = b;
        }
	}
    return num; // retorna el primer par encontrado (con mayor frecuencia)
}

void Repairv1::cambiar(){
    if(seq->size()<4) return;
    Iterator it = seq->begin();
    pair <int,int> dato = obtenerPrimerMayorFrec();
    if(mp[dato] <= 1){
        return;
    }
    mayor++;
    while(it.hasNext()){
        Nodo* a = it.next();
        if(!it.hasNext())break;
        if(a->getNum() == dato.first){
            Nodo* b = a->getNext();
            if(b->getNum() == dato.second){ 
                seq->deleteNodo(b);
                seq->insertBefore(a,mayor);
                seq->deleteNodo(a);
            }   
        }   
    }
    mp.clear();
    cambiar();
}

void Repairv1::prints(){
    seq->prints();
}


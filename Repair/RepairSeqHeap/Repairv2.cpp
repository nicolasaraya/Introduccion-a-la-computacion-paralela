#include "Repairv2.h"

using namespace std; 

Repairv2::Repairv2(DList* seq){
    hp = new Heap(&mp);
    mayor=27;
    this->seq=seq;
    if(seq->size()>=4) crearHeap();
    if(seq->size()<4) prints();
}

void Repairv2::crearHeap(){
    Iterator it = seq->begin();
    while(it.hasNext()){  
        Nodo* nodoA = it.next();
        int a = nodoA->getNum();
        if(!it.hasNext())break;
        Nodo* nodoB = nodoA->getNext();
        int b = nodoB->getNum();
        
        nodoA->setOP(NULL);
        if(mp.count({a, b})>0){
            nodoA->setOP(mp[{a, b}]->UltimaOc); //ocurrencia previa
            nodoA->setOS(NULL);
            mp[{a, b}]->UltimaOc->setOS(nodoA); // ocurrencia siguiente de la previa
            mp[{a, b}]->UltimaOc = nodoA;
            NodoHeap* aux = mp[{a,b}]->pos;
            aux->setFrecuencia(aux->getFrecuencia() + 1);
            hp->verify(mp[{a,b}]->posHeap);
        }
        else{
            NodoHeap* nH = new NodoHeap(a,b); 
            Data* d = new Data();
            mp.insert(make_pair(make_pair(a, b), d));
            hp->push(nH);
            d->pos=nH;
            d->posHeap = hp->size();
            d->PrimeraOc=nodoA;
            d->UltimaOc=nodoA;
        }
	}
}
void Repairv2::prints(){
    seq->prints();
}

void Repairv2::cambiar(){
    if(seq->size()<4) return;
    mayor++;
    pair <int,int> dato = hp->top()->getPar();
    while(1){
        if(hp->top()->getFrecuencia()<=1 || seq->size()<4)break;
        buscaOcurrencias(mp[dato]->PrimeraOc);    
        dato = hp->top()->getPar();
        mayor++;  
    }    
}



void Repairv2::buscaOcurrencias(Nodo* parUno){  
    Nodo* parDos = parUno->getNext(); 
    int a = parUno->getNum();
    int b = parDos->getNum();

    if(parUno->getPrev()!=NULL) actualizaHeap(parUno->getPrev(), parUno); //disminuye la frecuencia el par que se encuentra al costado izquierdo de a  
    if(parDos->getNext()!=NULL) actualizaHeap(parDos, parDos->getNext()); //disminuye la frecuencia el par que se encuentra al costado derecho de b
    
    actualizaHeap(parUno, parDos); //disminuye la frecuencia del par (a,b)
    actualizarLista(parUno, parDos); //realiza cambios a la lista doblemente enlazada

    if(mp[{a,b}]->PrimeraOc==NULL || mp[{a,b}]->UltimaOc==NULL) return;     
    buscaOcurrencias(mp[{a,b}]->PrimeraOc); //llama la siguiente ocurrencia del par (a,b)
}
void Repairv2::actualizaHeap(Nodo* parUno, Nodo* parDos){
    int a = parUno->getNum();
    int b = parDos->getNum();
    NodoHeap* aux;
    aux = mp[{a,b}]->pos; //el NodoHeap asociado al par (a,b)
    aux->setFrecuencia(aux->getFrecuencia()-1); //disminuye la frecuencia del par (a,b)
    hp->verifyDown(mp[{a,b}]->posHeap); //reordena el heap
}
void Repairv2::insertarHeap(Nodo* NodoA, Nodo* NodoB){
    int a = NodoA->getNum();
    int b = NodoB->getNum();

    if(mp.count({a, b})==0){
        NodoA->setOP(NULL);
        NodoA->setOS(NULL);
        NodoHeap* nH = new NodoHeap(a,b);
        Data* d = new Data();
        mp.insert(make_pair(make_pair(a, b), d)); 
        hp->push(nH);
        d->pos=nH;
        d->posHeap = hp->size(); 
        d->PrimeraOc=NodoA;
        d->UltimaOc=NodoA;
        hp->verify(mp[{a, b}]->posHeap);
    }
    else{
        
        NodoA->setOP(mp[{a,b}]->UltimaOc);
        NodoA->setOS(NULL);
        if(mp[{a, b}]->UltimaOc !=NULL) mp[{a, b}]->UltimaOc->setOS(NodoA); 
        if(mp[{a, b}]->PrimeraOc ==NULL)mp[{a, b}]->PrimeraOc = NodoA;
        mp[{a, b}]->UltimaOc = NodoA;
        NodoHeap* aux = mp[{a, b}]->pos;
        aux->setFrecuencia(aux->getFrecuencia() + 1);
        hp->verify(mp[{a, b}]->posHeap);
        
    }
}


void Repairv2::actualizarLista(Nodo* a, Nodo* b){
    //primero verifica si el par del nodo (a,b) se encuentra en la cabeza de la lista
    if(a->getPrev()==NULL){ 
        Nodo* siguiente = b->getNext();
        //actualiza los punteros correspondientes al nodo b (b,b->getNext())
        if(b->getOP()!=NULL) b->getOP()->setOS(NULL);
        if(b->getOS()!=NULL) {        
            if(b->getOP()!=NULL) b->getOP()->setOS(b->getOS());
            b->getOS()->setOP(NULL);
            mp[{b->getNum(), b->getNext()->getNum()}]->PrimeraOc=b->getOS();
        }
        //actualiza los punteros correspondiente al nodo a (a,b)
        if(a->getOS()!=NULL){
            a->getOS()->setOP(NULL);
            mp[{a->getNum(), b->getNum()}]->PrimeraOc=a->getOS();
        }
        if(a->getOS()==NULL && a->getOP()==NULL){
            mp[{a->getNum(), b->getNum()}]->PrimeraOc=NULL;
            mp[{a->getNum(), b->getNum()}]->UltimaOc=NULL;
        }
        //realiza cambios en la lista doblemente enlazada
        seq->deleteStart();
        seq->deleteStart();
        seq->insertStart(mayor); 
        insertarHeap(siguiente->getPrev(), siguiente); //inserta el par creado en el heap y en el mapa  
        return;
    }
    //verifica si el par del nodo (a,b) se encuentra en la cola de la lista
    if(b->getNext()==NULL){ 
        Nodo* previo = a->getPrev();
        if(a->getPrev()->getOP()!=NULL) {
            a->getPrev()->getOP()->setOS(NULL);
            mp[{a->getPrev()->getNum(), a->getNum()}]->UltimaOc=a->getOP();
        }
        if(a->getOP()==NULL)mp[{a->getNum(), b->getNum()}]->PrimeraOc=NULL;
        if(a->getOP()==NULL)mp[{a->getNum(), b->getNum()}]->UltimaOc=NULL;
        seq->deleteEnd();
        seq->deleteEnd();
        seq->insertEnd(mayor); 
        insertarHeap(previo, previo->getNext());
        return; 
    }
    //caso si el par del nodo (a,b) se encuentra en la mitad de la lista
    Nodo* siguiente = b->getNext();
    Nodo* previo = a->getPrev();
    if(previo->getOP()!=NULL){
        if(previo->getOS()!=NULL){
            previo->getOP()->setOS(previo->getOS());
            previo->getOS()->setOP(previo->getOP());
        }
        else{
            previo->getOP()->setOS(NULL);
            mp[{previo->getNum(), a->getNum()}]->UltimaOc=previo->getOP();
        }
    }
    else{ //if(previo->getOP==NULL); 
        if(previo->getOS()!=NULL){
            previo->getOS()->setOP(NULL);
            mp[{previo->getNum(), a->getNum()}]->PrimeraOc=previo->getOS();
        }
        else{
            mp[{previo->getNum(), a->getNum()}]->PrimeraOc=NULL;
            mp[{previo->getNum(), a->getNum()}]->UltimaOc=NULL;
        }
    }

    if(a->getOP()!=NULL){
        if(a->getOS()!=NULL){
            a->getOP()->setOS(a->getOS());
            a->getOS()->setOP(a->getOP());
        }
        else{ //if(getOS()==NULL)
            a->getOP()->setOS(NULL);
            mp[{a->getNum(), b->getNum()}]->UltimaOc=a->getOP();
        }
    }
    else{ //if(a->getOP()==NULL)  //siempre deberia
        if(a->getOS()!=NULL){
            a->getOS()->setOP(NULL);
            mp[{a->getNum(), b->getNum()}]->PrimeraOc=a->getOS();
        }
        else{
            mp[{a->getNum(), b->getNum()}]->PrimeraOc=NULL;
            mp[{a->getNum(), b->getNum()}]->UltimaOc=NULL;
        }
    }

    if(b->getOP()!=NULL){

        if(b->getOS()!=NULL){
            b->getOP()->setOS(b->getOS());
            b->getOS()->setOP(b->getOP());
        }
        else{ //if(getOS()==NULL)
            b->getOP()->setOS(NULL);
            mp[{b->getNum(), b->getNext()->getNum()}]->UltimaOc=b->getOP();
        }
    }
    else{ //if(b->getOP()==NULL)  //siempre deberia
        if(b->getOS()!=NULL){
            b->getOS()->setOP(NULL);
            mp[{b->getNum(), b->getNext()->getNum()}]->PrimeraOc=b->getOS();
        }
        else{
            mp[{b->getNum(), b->getNext()->getNum()}]->PrimeraOc=NULL;
            mp[{b->getNum(), b->getNext()->getNum()}]->UltimaOc=NULL;
        }
    }

    seq->deleteNodo(a);
    seq->deleteNodo(b);
    seq->insertBefore(siguiente, mayor); 
    //inserta en el map y en el heap los pares que se forman con los nodos de los costados de (a,b)
    insertarHeap(previo, previo->getNext());
    insertarHeap(siguiente->getPrev(), siguiente);

    return; 
}
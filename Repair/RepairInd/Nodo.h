#ifndef NODO_H
#define NODO_H

#include <iostream>

using namespace std;

class Nodo{
    private:
        int numero;
        Nodo* prev;
        Nodo* sig;
        Nodo*  OP;
        Nodo*  OS;
 
    public:
        Nodo();
        ~Nodo();
        Nodo* getPrev();
        Nodo* getNext();
        Nodo* getOP();
        Nodo* getOS();
        void setPrev(Nodo*);
        void setNext(Nodo*);
        void setOP(Nodo*);
        void setOS(Nodo*);
        int getNum();
        void setNum(int);
};

#endif
#ifndef ITERATOR_H
#define ITERATOR_H
#include <iostream>
#include "Nodo.h"

using namespace std;


class Iterator{
    private:
        Nodo* movil;
        Nodo* head;
        Nodo* tail;
    public:
        Iterator(Nodo*, Nodo*);
        ~Iterator();
        Nodo* next();
        bool hasNext();
};

#endif
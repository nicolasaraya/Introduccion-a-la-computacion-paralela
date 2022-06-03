#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Iterator.h"
using namespace std;


class DList{
    private:
        Nodo* head;
        Nodo* tail;
        int sz;
        Nodo* nuevoNodo(int);
        Nodo* end();
    public:
        DList();
        ~DList();
        Iterator begin();
        void prints();
        void insertStart(int);
        void deleteStart();
        void insertEnd(int);
        void insertBefore(Nodo*,int);
        void deleteEnd();
        void deleteNodo(Nodo*);
        int size();
        
};


#endif
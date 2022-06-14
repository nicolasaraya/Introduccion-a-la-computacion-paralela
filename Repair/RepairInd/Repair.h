#ifndef REPAIR_H
#define REPAIR_H
#include "RepairADT.h"
#include <map>

using namespace std; 


class Repair : public RepairADT{
    private:
        DList* seq;
        int mayor = 30;
        Heap* hp; 
        map<pair<int, int>,Data*> mp;
        void crearHeap();
        void buscaOcurrencias(Nodo*);
        void actualizaHeap(Nodo*, Nodo*);
        void insertarHeap(Nodo*, Nodo*);
        void actualizarLista(Nodo*, Nodo*);
        
        
    public:
        Repair(vector<int>* datos);
        Repair(DList*);
        ~Repair(); 
        void cambiar();
        void prints();
        void crearSeq(vector<int>* datos); 
        DList* getSeq();
};



#endif
#ifndef REPAIRV2_H
#define REPAIRV2_H
#include "RepairADT.h"
#include <map>

using namespace std; 


class Repairv2 : public RepairADT{
    private:
        DList* seq;
        int mayor;
        Heap* hp; 
        map<pair<int, int>,Data*> mp;
        void crearHeap();
        void buscaOcurrencias(Nodo*);
        void actualizaHeap(Nodo*, Nodo*);
        void insertarHeap(Nodo*, Nodo*);
        void actualizarLista(Nodo*, Nodo*);
        
        
    public:
        Repairv2(DList*);
        ~Repairv2(); 
        void cambiar();
        void prints();
};

#endif
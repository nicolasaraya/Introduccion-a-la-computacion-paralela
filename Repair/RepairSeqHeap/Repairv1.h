#ifndef REPAIRV1_H
#define REPAIRV1_H

#include "RepairADT.h"
using namespace std; 

class Repairv1 : public RepairADT{
    private:
        DList* seq;
        map<pair<int, int>, int> mp;
        int mayor;
        pair <int,int> obtenerPrimerMayorFrec();
        
    public:
        Repairv1(DList*);
        ~Repairv1();
        void cambiar();
        void prints();  
};

#endif
#ifndef RpADT
#define RpADT
#include "DList.h"
#include "Heap.h"
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

class RepairADT{
    private:
        virtual void cambiar() = 0;
        virtual void prints() = 0; 
};

#endif
#include <iostream>
#include "DList.h"
#include "Repair.h"

using namespace std;

int main(){
    DList* d = new DList();

    for(int i = 0; i < 20; i++) d->insertEnd(i);

    Repair(d);


    
}
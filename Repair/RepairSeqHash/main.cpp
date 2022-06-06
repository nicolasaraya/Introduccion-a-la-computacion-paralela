#include <iostream>
#include "DList.h"
#include "Repair.h"

using namespace std;

int main(){
    DList* d = new DList();

    vector<int> v = {2, 3, 1, 2, 3, 1, 2, 3};
    for(auto i : v) d->insertEnd(i);


    d->prints();

    Repair(d);


    
}
#ifndef REPAIR_H
#define REPAIR_H
#include "DList.h"
#include <queue>
#include <map>


struct Int{
    int x;
    
 };  
struct compare{
  public:
  bool operator()(Int* a,Int* b) // overloading both operators 
  {
      return a->x < b->x; // if you want increasing order;(i.e increasing for minPQ)
   }
};

 typedef struct{
    Nodo* PrimeraOc;
    Nodo* UltimaOc;
    Int freq; 
}Data;



int rep = -1; 
priority_queue< pair<int , pair<int,int> >, greater<int*>> pq;
map<pair<int, int>,Data*> mp;



void init(DList* d){
    Iterator it = d->begin();
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
            mp[{a, b}]->freq.x++;
        }
        else{
            Data* d = new Data();
            mp.insert(make_pair(make_pair(a, b), d));
            d->PrimeraOc=nodoA;
            d->UltimaOc=nodoA;
            mp[{a, b}]->freq.x = 1;
        }
    }

    map<pair<int, int>,Data*>::iterator i = mp.begin();
    while(i!=mp.end()){
        pq.push( make_pair(  &i->second->freq , make_pair(i->first.first, i->first.second) ) );
        i++;
    }
}

void printPQ(){
    while(!pq.empty()){
        pair<Int* , pair<int,int> > p = pq.top();
        cout << p.first->x << "  (" << p.second.first << "," << p.second.second << ")" << endl;
        pq.pop();
    }
}

void printMP(){
    int x=2; 
    map<pair<int, int>,Data*>::iterator it = mp.begin();
    while(it!=mp.end()){
        
        cout << it->first.first << "," << it->first.second << ": " << it->second->freq.x << endl ;
        it->second->freq.x += x;
        x*=2;
        it++;
    }
}

void replacePair(int a, int b){
    
}


void Repair(DList* d){
    if(d->size()<4) return;

    init(d);
    /*
    while(pq.top().first > 1 ){
        pair<int, int> p = pq.top().second; 
        pq.pop();
        replacePair(p.first, p.second);
        rep--;
    }*/

    printMP();
    printPQ();
    


    





}





#endif
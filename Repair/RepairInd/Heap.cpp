#include "Heap.h"
#include<vector>
#include <iostream>

using namespace std;

Heap::Heap(map<pair<int, int>,Data*>* mp){
    this->mp=mp;
    NodoHeap* a;
    arr.push_back(a);
}
Heap::~Heap(){

}
void Heap::push(NodoHeap* a){
    arr.push_back(a);
}
void Heap::pop(){
    if(empty()) return;
    arr[1]=arr.back(); 
    arr.pop_back();

}
NodoHeap* Heap::top(){
    if(empty()) return NULL;
    return arr.at(1);
}
int Heap::size(){
    return arr.size()-1;
}
bool Heap::empty(){
    if(arr.size()>1) return false;
    else return true; 
}

void Heap::verify(int pos){
    int posUp=(pos)/2;
    if(posUp<1) return;
    else{
        if(arr.at(posUp)->getFrecuencia() < arr.at(pos)->getFrecuencia()){
            mp->at(arr[pos]->getPar())->posHeap=posUp;
            mp->at(arr[posUp]->getPar())->posHeap=pos;
            swap(arr[pos], arr[posUp]);
            return verify(posUp);
        }
        else{
            return;
        }
    } 

}

void Heap::verifyDown(int pos){
    int l = (2*pos);
    int r = (2*pos)+1;
    if(l > size()) return;
    if(l == size()){
        if(arr.at(pos)->getFrecuencia() < arr.at(l)->getFrecuencia()){
            mp->at(arr[pos]->getPar())->posHeap=l;
            mp->at(arr[l]->getPar())->posHeap=pos;  
            swap(arr[pos], arr[l]);
        }
        return;
    }
    
    if(arr.at(pos)->getFrecuencia() < arr.at(l)->getFrecuencia() || arr.at(pos)->getFrecuencia() < arr.at(r)->getFrecuencia()   ){
        int menor;
        if(arr.at(l)->getFrecuencia() >= arr.at(r)->getFrecuencia() ) menor = l;
        else menor = r;
        mp->at(arr[pos]->getPar())->posHeap=menor;
        mp->at(arr[menor]->getPar())->posHeap=pos;
        swap(arr[pos], arr[menor]);
        return verifyDown(menor);
    } 
    return;


}

void Heap::prints(){
    for(int i = 1; i<arr.size(); i++){
        pair<int,int> a = arr.at(i)->getPar();
        int f = arr.at(i)->getFrecuencia();
        cout<<"("<<a.first<<","<<a.second<<") "<<f<<endl;
    }
    cout<<endl;
}
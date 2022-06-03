#include "DList.h"

using namespace std;

DList::DList(){
	head = NULL;
	tail = NULL;
	
}

DList::~DList(){
	while(head->getNext()!=NULL){
		deleteEnd();
	}
	delete head;
}

Nodo* DList::nuevoNodo(int n){
	Nodo* nuevo = new Nodo();
	nuevo->setNum(n);
	nuevo->setNext(NULL);
	nuevo->setPrev(NULL);
	nuevo->setOP(NULL);
	nuevo->setOS(NULL);
	return nuevo;
}


void DList::insertBefore(Nodo* n,int k){
	
	if(n == head){
		insertStart(k);
		return;
	}
	sz++;
	Nodo* aux = nuevoNodo(k);
	aux->setNext(n);
    aux->setPrev(n->getPrev());
    n->getPrev()->setNext(aux);
    n->setPrev(aux);
}
void DList::deleteStart(){
	Nodo* aux = head;
	if(head==NULL){
		return;
	}
	if(head->getNext()==NULL){
        head = NULL;
        return;
    }
	sz--;
	head = aux->getNext();
	delete aux->getPrev();
	head->setPrev(NULL);

}

void DList::deleteNodo(Nodo* n){
	if(n == tail){
		deleteEnd();
		return;
	}
	if(n == head){
		deleteStart();
		return;
	}
	sz--;
	n->getPrev()->setNext(n->getNext());
	n->getNext()->setPrev(n->getPrev());
	delete n;   
}
void DList::insertStart(int n){
	Nodo* k = nuevoNodo(n);
	sz++;
	if(head == NULL){
		head = k;
		tail = k;
		return;
	}
	else{
		head->setPrev(k);
		k->setNext(head);
		head = k;			
	}
}
void DList::insertEnd(int s){
	sz++;
	Nodo* aux = tail;
	Nodo* k = nuevoNodo(s);
	if(head==NULL){
		head = k;
		tail = k;
		return;
	}
	aux->setNext(k);
	k->setPrev(aux);
	tail = k;
}

void DList::deleteEnd(){
	Nodo* aux = tail;
	if(head==NULL){
		return;
	}
	sz--;
	tail = aux->getPrev();
	delete aux->getNext();
	tail->setNext(NULL);

}

void DList::prints(){
	Nodo* aux = head;
	while(aux!=NULL){
		cout << aux->getNum() << " ";
		aux = aux->getNext();
	}
	cout<<endl;
}

Iterator DList::begin(){
	Iterator it(head,tail);
	return it;
}

int DList::size(){
	return sz;
}

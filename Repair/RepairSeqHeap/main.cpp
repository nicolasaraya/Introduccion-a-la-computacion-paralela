#include "Repairv1.h"
#include "Repairv2.h"
#include <time.h>

using namespace std;

int main(){
	srand(time(NULL));
	DList *s = new DList();
	DList *s1 = new DList();
	/*
	int c; 
	while(cin>>c){
		s->insertEnd(c);
		s1->insertEnd(c);
	}*/
	
	int n;
	cin>>n;
	for(int i = 0; i<n; i++){
		int x = rand()%27+1;
		x=1;
		/*if(i==n/2){
			s->insertEnd(2);
			s1->insertEnd(2);
		}*/
		s->insertEnd(x);
		s1->insertEnd(x);

	}
	cout<<endl<<endl;

	clock_t start = clock(); 
	double time;
	Repairv1* r = new Repairv1(s);
	cout<<"Solucion 1: ";
	r->cambiar();
	time = double(clock()-start)/CLOCKS_PER_SEC;
	printf("%.6f\n", time);

	cout<<endl;	
	start=clock();
	Repairv2* r2 = new Repairv2(s1);
	cout<<"Solucion 2: ";
	r2->cambiar();
	time = double(clock()-start)/CLOCKS_PER_SEC;
	printf("%.6f\n", time);

	r->prints();
	r2->prints();
	
	return 0;
}
#include <set>
#include <iostream>


using namespace std;
bool masdelamitadcomunes(set<int>& c1,set<int>& c2){
	set<int>::const_iterator p,q;
	//set<int> solucion;
	int n1,n2;
	n1=0;
	n2=c1.size();


	for(p=c1.begin();p!=c1.end();++p){
		if(c2.count(*p)){	//como count devuelve el numero de apariciones, y en el set solo puede ser 0 o 1
			n1++;
		}

	}


	return (n1>n2/2);
	//return solucion;
}




int main(){

set<int> s1,s2;


for(int i =0;i<10;i++)
	s1.insert(i);

for(int i =0;i<11;i++)
	s2.insert(i);

cout<<"¿La mitad es comun? "<<masdelamitadcomunes(s1,s2)<<endl;


}

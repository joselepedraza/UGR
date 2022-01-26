#include <set>
#include <iostream>


using namespace std;

set<int> num_no_comunes(set<int> c1,set<int> c2){
	set<int>::iterator p,q;
	set<int> solucion;

	for(p=c1.begin();p!=c1.end();++p ){
		if(!c2.count(*p)){
			solucion.insert(*p);
			
		}
	}

	for(q=c2.begin();q!=c2.end();++q ){
		if(!c1.count(*q)){
			solucion.insert(*q);
			
		}
	}	

	return solucion;
}




int main(){

set<int> s1,s2;


for(int i =0;i<10;i++)
	s1.insert(i);

for(int i =0;i<11;i++)
	s2.insert(i);

set<int>res=num_no_comunes(s1,s2);

//mostramos

for(auto it=res.begin();it!=res.end();++it){
	cout<<*it<<endl;	
}




}

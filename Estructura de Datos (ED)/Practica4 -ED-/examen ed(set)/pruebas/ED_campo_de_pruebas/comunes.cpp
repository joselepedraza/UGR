#include <set>
#include <iostream>


using namespace std;
void comunes(set<int>& c1,set<int>& c2,set<int>& solucion){
	set<int>::iterator p,q;
	//set<int> solucion;

	for(p=c1.begin();p!=c1.end();++p ){
		if(c2.count(*p)){
			solucion.insert(*p);
		}
	}
	//return solucion;
}




int main(){

set<int> s1,s2;


for(int i =0;i<10;i++)
	s1.insert(i);

for(int i =0;i<11;i++)
	s2.insert(i);

set<int>res;
comunes(s1,s2,res);

//mostramos

for(auto it=res.begin();it!=res.end();++it){
	cout<<*it<<endl;
}




}

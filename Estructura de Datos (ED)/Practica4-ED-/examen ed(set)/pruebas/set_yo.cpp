//YO PRACTICANDO

#include<iostream>
#include<set>

using namespace std;

typedef set<int> IntSet;

void interseccion(const set<int>& c1, const set<int>& c2, set<int>& res){
	set<int>::const_iterator pos;
	//recorremos el primer conjunto
	for (pos = c1.begin(); pos!=c1.end(); ++pos){
		if (c2.count(*pos)==1)
			res.insert(*pos);
	}
}


int main(){

	set<int>  c1;
	set<int> c2;
	set<int> res;
	int a=0;
	cout <<"CONJUNTO C1"<<endl;
	cout<<"Introduzca un valor "<<endl;
	cin >>a;
	while (a!=-1){
		c1.insert(a);
		cout<<"Introduzca un valor o -1 para terminar"<<endl;
		cin >>a;
	}
	
	cout <<"CONJUNTO C2"<<endl;
	cout<<"Introduzca un valor "<<endl;
	cin >>a;
	while (a!=-1){
		c2.insert(a);
		cout<<"Introduzca un valor o -1 para terminar"<<endl;
		cin >>a;
	}
	
	interseccion(c1,c2,res);
	
	cout<<"IMPRIMO EL CONJUNTO INTERSECCIÓN"<<endl;
	set<int>::const_iterator it;
	for (it=res.begin(); it!=res.end(); ++it){
		cout <<*it<<endl;
	}
	
}

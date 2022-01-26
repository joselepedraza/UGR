#include <set>
#include <iostream>
using namespace std;

bool inclusionpares(const set<int>&c1,const set<int>&c2){
	for(auto p=c1.begin();p!=c1.end();++p ){
		if(*p %2 ==0){
			if(c2.find(*p) == c2.end()){	//si no está
				return false;
			}else{
				++p;
			}
		}
	}
	return true;
}




int main(){

set<int> s1,s2;


for(int i =0;i<10;i++)
	s1.insert(i);

for(int i =0;i<10;i++)
	s2.insert(i);

cout<<"Inclusion pares "<<inclusionpares(s1,s2)<<endl;


}

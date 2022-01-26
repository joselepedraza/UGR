#include <set>
#include <iostream>


using namespace std;

bool mas_pares_que_impares(set<int>&c, set<int>& cpar,set<int>& cimpar){

	for(auto p=c.begin();p!=c.end();++p ){
		if(*p %2 ==0){
			cpar.insert(*p);

		}else{
			cimpar.insert(*p);
		}
	}

	return (cpar.size() > cimpar.size());

}


int main(){

set<int> s1,s2,s3;


for(int i =0;i<20;i++)
	s1.insert(i);



cout<<mas_pares_que_impares(s1,s2,s3)<<endl;

}

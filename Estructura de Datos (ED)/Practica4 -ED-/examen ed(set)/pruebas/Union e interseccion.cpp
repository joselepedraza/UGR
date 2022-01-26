 #include <iostream>
 #include <set>
 
 using namespace std;
 
template <class T>
 ostream& operator<<(ostream& s, const set<T>& c)
 {
   typename set<T>::const_iterator i;

   s << "{ ";
   for (i = c.begin(); i != c.end(); ++i)
     s << *i << " ";
   s << "}";

   return s;
 }
 int main(){
 	set<int> s1,s2,s3;
	typedef set<int>::iterator it;
	
	for(int i = 1; i <= 5; i++){
		s1.insert(i);
		s2.insert(i+1);
		s3.insert(i+2);
	}
	
	s2.erase(4);
	
	cout << "S1 es: " << s1 << endl;
	cout << "S2 es: " << s2 << endl;
	cout << "S3 es: " << s3 << endl;
 
	//union
	
	set<int> union1;
	
	for(it p = s1.begin(); p!= s1.end(); ++p)
		union1.insert(*p);
		
	for(it p = s2.begin(); p!= s2.end(); ++p)
		union1.insert(*p);
		
	for(it p = s3.begin(); p!= s3.end(); ++p)
		union1.insert(*p);
	
	cout << "La union es:" << union1 << endl;
	
	set<int> interseccion;

	
	for(it p = s1.begin(); p!=s1.end(); ++p){
		if(s2.count(*p) == 1 && s3.count(*p) == 1)
			interseccion.insert(*p);
	}
	
	cout << "La intersección de los tres conjuntos es:" << interseccion << endl;
	
	set<int> union2(union1);
	
	for(it p = interseccion.begin(); p != interseccion.end(); ++p)
		union2.erase(*p);
		
	cout << "La union quitando interseccion es: " << union2;
	
	
 }

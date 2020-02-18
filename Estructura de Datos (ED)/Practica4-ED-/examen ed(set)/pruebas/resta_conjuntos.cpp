#include <iostream>
#include <set>

using namespace std;

template <class T>
 ostream& operator<<(ostream& s, const set<T>& c){
   typename set<T>::const_iterator i;

   s << "{ ";
   for (i = c.begin(); i != c.end(); ++i)
     s << *i << " ";
   s << "}";

   return s;
 }

template <class T>

set <T> operator-(const set<T>& A, const set<T>& B){
  set <T> C;
  typename set<T>::iterator i;

  for (i = A.begin(); i != A.end(); ++i){
    if (B.count(*i) == 0)
      C.insert(*i);
  }

  return C;

}


int main(){

set<int> s1, s2;
typedef set<int>::iterator it;

for (int i = 1; i <= 100; ++i){
  s1.insert(2*i);
  s2.insert(2*i+1);
}

set <int> s3= (s1-s2), s4= (s2-s1);

cout << "S1 es: "<<endl<<s1<<endl;
cout << "S2 es: "<<endl<<s2<<endl;
cout << "S3 es: "<<endl<<s3<<endl;
cout << "S4 es: "<<endl<<s4<<endl;

}

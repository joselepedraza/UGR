//Víctor Castro Serrano

#include <iostream>
#include <set>
using namespace std;


typedef set<int>::iterator iterator;
typedef set<int>::const_iterator const_iterator;
typedef set<int>::const_reverse_iterator const_reverse_iterator;

//Si tienen el misno tamaño, al primero le quita los del segundo
set<int> operator-(const set<int>& c1, const set<int>& c2) {
  set<int> aux;
  const_reverse_iterator inicio ;
  const_reverse_iterator fin;
  if(c1.size() >= c2.size()) {
    aux = c1;
    inicio = c2.rbegin();
    fin = c2.rend();
  } else {
    aux = c2;
    inicio = c1.rbegin();
    fin = c1.rend();
  }

  for(const_reverse_iterator p = inicio; p != fin; ++p)
    aux.erase(*p);

    return aux;
}



ostream& operator<<(ostream& flujo, const set<int>& c1) {
  const_reverse_iterator inicio = c1.rbegin();
  const_reverse_iterator fin = c1.rend();

  flujo << "{";
  int n = c1.size();
  int i = 1;
  for(const_reverse_iterator p = inicio; p != fin; ++p,++i) {
    if(n == i)
      flujo << (*p);
    else
      flujo << (*p) << ",";
  }

  flujo << "}";
  return flujo;

}



int main() {
  set<int> c1, c2, res;

  for(int i = 0; i <= 5; ++i) {
    c1.insert(i);
    c2.insert(3+i);
  }

  cout << "El primer conjunto es " << c1 << endl;
  cout << "El segundo conjunto es " << c2 << endl;

  res = c1 - c2;
  cout << "La resta de ambos es " << res << endl;
}

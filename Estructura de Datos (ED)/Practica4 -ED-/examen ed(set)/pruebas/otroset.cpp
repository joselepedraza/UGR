//Víctor Castro Serrano

#include <iostream>
#include <set>
#include <cmath>

using namespace std;


typedef set<int>::iterator iterator;
typedef set<int>::const_iterator const_iterator;


ostream& operator<<(ostream& flujo, const set<int>& c1) {
  const_iterator inicio = c1.begin();
  const_iterator fin = c1.end();

  flujo << "{";
  int i = 1;
  int n = c1.size();
  for(const_iterator p = inicio; p != fin; ++p) {
    if(i == n)
      flujo << (*p) << "}";
    else
      flujo << (*p) << ",";
    i++;
  }
    return flujo;
}


void UnirSet(const set<int>& c1, const set<int>& c2, set<int>& res) {
  res.clear();
  const_iterator inicio = c1.begin();
  const_iterator fin = c1.end();
  for(const_iterator p = inicio; p != fin; ++p)
    res.insert(*p);

  inicio = c2.begin();
  fin = c2.end();
  for(const_iterator p = inicio; p != fin; ++p)
    res.insert(*p);
}

void TripleUnion(const set<int>& c1, const set<int>& c2, const set<int>& c3, set<int>& res) {
  set<int> aux;
  UnirSet(c1,c2,aux);
  UnirSet(aux,c3,res);
}

void Interseccion(const set<int>& c1, const set<int>& c2, set<int>& res) {
  const_iterator inicio = c1.begin();
  const_iterator fin = c1.end();
  res.clear();
  for(const_iterator p = inicio; p != fin; ++p) {
    if(c2.count(*p) == 1)
      res.insert(*p);
  }
}

//Voy a hacerlo explícitamente, suponiendo que hay que el erase necesita que los elementos estén en el conjunto
//Creo que bastaría con iterar sobre el mayor borrando los del menos, lo hago así para practicar
void RestaConjuntos(const set<int>& c1, const set<int>& c2, set<int>& res) {
  int m = max(c1.size(),c2.size());
  set<int> inter;
  Interseccion(c1,c2,inter);

  const_iterator inicio = inter.begin();
  const_iterator fin = inter.end();
  //Caso c1 es el mayor conjunto
  if(m == c1.size()) {
    res.clear();
    res = c1;
    for(const_iterator p = inicio; p != fin; ++p)
      res.erase(res.find(*p));
  } else {
    res.clear();
    res = c2;
    for(const_iterator p = inicio; p != fin; ++p)
      res.erase(res.find(*p));
  }
}


//Mira si el conjunto 1 está incluido en el 2
bool EstaIncluido(const set<int>& c1, const set<int>& c2) {
  if(c1.size() > c2.size())
    return false;

  bool incluido = true;

  const_iterator p = c1.begin();
  const_iterator fin = c1.end();
  while(p != fin) {
    if(c2.count(*p) == 0)
      return false;
    ++p;
  }

  return incluido;
}



int main() {
  set<int> c1,c2,c3,res;

  for(int i = 0; i <= 5; i++) {
    c1.insert(i);
    c2.insert(3+i);
  }

  UnirSet(c1,c2,res);

  cout << "El valor del primer conjunto es " << c1 << endl;
  cout << "El valor del segundo conjunto es " << c2 << endl;
  cout << "El valor de la unión de ambos es " << res << endl;

  Interseccion(c1,c2,res);

  cout << "Su intersección es " << res << endl;

  c1.insert(12);
  c1.insert(13);

  cout << "Ahora el conjunto 1 es " << c1 << endl;

  RestaConjuntos(c1,c2,res);
  cout << "La resta de ambos es" << res << endl;

  c1.clear();
  c2.clear();

  for(int i = 0; i <= 5; i++) {
    c1.insert(i);
    c2.insert(i);
  }

  for(int i = 6; i <= 10; i++)
    c2. insert(i);

  cout << "Ahora el primer conjunto es " << c1 << endl;
  cout << "Ahora el segundo conjunto es " << c2 << endl;

  bool incluido = EstaIncluido(c1,c2);

  cout << "¿El conjunto 1 está incluido en el 2? (0=no, 1=si) " << incluido <<  endl;

}

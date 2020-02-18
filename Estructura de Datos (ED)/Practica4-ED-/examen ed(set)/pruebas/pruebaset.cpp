#include <iostream>
#include <set>
using namespace std;

ostream& operator<<(ostream& flujo, const set<int>& s1) {
  set<int>::const_iterator p;
  flujo << "{";

  int n = s1.size();
  int i = 1;

  for(p = s1.begin(); p != s1.end(); ++p) {
    if(i == n)
      flujo << *p << "}";
    else
      flujo << *p << ",";
    i++;
  }
  return flujo;
}

/**
  *@brief Unir dos set<int> en set<int> resultado
  *@param s1 Primer conjunto
  *@param s2 Segundo conjunto
  *@param res Conjunto que contendrá el resultado
  */
void UnirSet(const set<int>& s1, const set<int>& s2, set<int>& res) {
  res.clear();
  set<int>::iterator p;
  for(p = s1.begin(); p != s1.end(); ++p)
    res.insert(*p);

  for(p = s2.begin(); p != s2.end(); ++p)
    res.insert(*p);
}

/**
  @brief Calcula los elementos de tres conjuntos que solo están en dos de ellos
  * @param s1 Primer conjunto
  * @param s2 Segundo conjunto
  * @param s3 Tercer conjunto
  * @param res Conjunto unión. Parámetro de salida
  */

void Union(const set<int>& s1, const set<int>& s2, const set<int>& s3, set<int>& res) {
  res.clear();
  set<int>::iterator p;

  //Elementos de A que: están en B y no en C; están en C y no en B
  for(p = s1.begin(); p != s1.end(); ++p) {
    if(s2.count(*p) == 1 && s3.count(*p) == 0)
      res.insert(*p);
    else
      if(s2.count(*p) == 0 && s3.count(*p) == 1)
        res.insert(*p);
  }

  //Elementos de B que: están en C y no en A
  for(p = s2.begin(); p != s2.end(); ++p)
    if(s1.count(*p) == 0 && s3.count(*p) == 1)
      res.insert(*p);
}

/**
  @brief Intersección entre dos conjuntos
  */
void Interseccion(const set<int>& c1, const set<int>& c2, set<int>& res){
  set<int>::iterator p;
  res.clear();
  for(p = c1.begin(); p != c1.end(); ++p) {
    if(c2.count(*p) == 1)
      res.insert(*p);
    }
}

void InterseccionTres(const set<int>& c1, const set<int>& c2, const set<int>& c3, set<int>& res) {
  Interseccion(c1,c2,res);
  set<int> aux;
  aux = res;
  Interseccion(aux,c3,res);
}

void BorrarInterseccion(set<int>& c1, set<int>& c2, const set<int>& inter) {
  set<int>::const_iterator p;
  for(p = inter.begin(); p != inter.end(); ++p) {
    set<int>::iterator t;
    t = c1.find(*p);
    c1.erase(t);
    c2.erase(c2.find(*p));
  }
}



int main() {
  set<int> c1,c2,res;

  //Metemos datos en el primer set
  for(int i = 0; i <= 5; i++)
    c1.insert(i);

  //Metemos datos en el segundo set
  for(int i = 10; i <= 18; i++)
    c2.insert(i);

  //Unimos c1 y c2 en el resultado
  UnirSet(c1,c2,res);

  cout << "El conjunto 1 tiene los siguientes elementos: " << c1 << endl;
  cout << "El conjunto 2 tiene los siguientes elementos: " << c2 << endl;
  cout << "El conjunto con la unión de ambos es: " << res << endl;

  set<int> c3;
  c2.clear();

  for(int i = 3; i <= 10; i++)
    c2.insert(i);

  for(int i = 1; i <= 7; i++)
    c3.insert(i);


  //Calculamos qué elementos están solo en dos de ellos
  Union(c1,c2,c3,res);
  cout << "El conjunto 1 tiene los siguientes elementos: " << c1 << endl;
  cout << "El conjunto 2 tiene los siguientes elementos: " << c2 << endl;
  cout << "El conjunto 3 tiene los siguientes elementos: " << c3 << endl;
  cout << "Los elementos presentes en solo dos de ellos son: " << res << endl;

  InterseccionTres(c1,c2,c3,res);
  cout << "La intersección de los tres conjuntos(usando la funcion triple intersección) es: " << res << endl;

  Interseccion(c1,c2,res);
  BorrarInterseccion(c1,c2,res);

  cout << "Borrando los elementos comunes, nos quedan los conjuntos así : " << endl;
  cout << "El conjunto 1 tiene los siguientes elementos: " << c1 << endl;
  cout << "El conjunto 2 tiene los siguientes elementos: " << c2 << endl;

  }

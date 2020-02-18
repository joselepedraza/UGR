#include<cstdlib>
#include<iostream>
#include<set>

using namespace std;

int main(){
  set<int> s, m, n, i;
  set<int>::iterator pos, pos1;
  pair<set<int>::iterator,bool> status;
  int a;
  cout << "Entero a insertar:\n ";
  cin >> a;
  while(a!=-1){
    status = s.insert(a);
    if(status.second)
      cout << "Insertado\n";
    else
      cout << a << "Ya existe.\n";
    cout << "Entero a insertar:\n ";
    cin >> a;
  }

  a = s.size();

  cout << "Has realizado una inserción de " << a << " enteros.\n";

  cin >> a;
  while(a!=-1){
    status = m.insert(a);
    if(status.second)
      cout << "Insertado\n";
    else
      cout << a << "Ya existe.\n";
    cout << "Entero a insertar:\n ";
    cin >> a;
  }

  a = m.size();

  cout << "Has realizado una inserción de " << a << " enteros.\n";

  pos=s.begin();


  for(;pos!=s.end();++pos){     //Unión.
    for(pos1=m.begin();pos1!=m.end();++pos1){
      if((*pos)==(*pos1)){
        cout << "inserción en la unión\n";
        n.insert(*pos);

      }
    }
  }

  for(pos=s.begin();pos!=s.end();++pos)  //Aquí empieza la intersección.
    i.insert(*pos);

  for(pos1=m.begin();pos1!=m.end();++pos1)
    i.insert(*pos1);

  cout << "Los enteros de la unión son: ";
  for(pos=n.begin();pos!=n.end();++pos){
    cout << *pos << " ";
  }

  cout << "Los enteros de la intersección son:\n ";
  for(pos=i.begin();pos!=i.end();++pos){
    cout << *pos << " ";
  }

}

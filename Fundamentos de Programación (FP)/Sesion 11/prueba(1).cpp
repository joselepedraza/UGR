#include <iostream>
using namespace std;
int main(){
  const int TAM = 6;
  int v[TAM];
  v[0] = 1;
  v[1] = 2;
  v[2] = 5;
  v[3] = 4;
  v[4] = 6;
  v[5] = 7;
  for(int i = 0 ; i < TAM ; i++)
    cout << v[i] << ",";
  int k;
  cout << "\nIntroduce un tamaño para alamacenar elementos: ";
  cin >> k;
  int nuevo[k];
  int ref;
  cout << "Introduce un valor de referencia: ";
  cin >> ref;

  int cont = 0;
  for(int i = 0 ; i < TAM ; i++){
    //si el valor del vector es mayor o igual al de ref añadimos
    if(v[i] >= ref){

      //Si la posicion es menor al tamaño del vector podemos añadir
      if(cont < k){


        //BIEN

        //si el nuevo elemento es menor al que tengo en la primera posicion del vector
        bool nosal = true;
        int pos;
        //recorremos el vector hasta encontrar la posicion donde va el nuevo elemento
        for(pos = 0 ; (pos < cont)&&nosal ; pos++){
          if(nuevo[pos] >= v[i]){
            nosal = false;
          }
        }
        //movemos a derecha
        for(int s = cont ; s >= pos ; s--)
          nuevo[s+1] = nuevo[s];
        nuevo[pos] = v[i];
        cont++;
      }
    }



  }

for(int i = 0 ; i < cont ; i++)
  cout << nuevo[i] << ",";
cout << endl;
}

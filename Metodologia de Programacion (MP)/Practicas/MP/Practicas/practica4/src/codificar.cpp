#include <iostream>
#include <cstring>
#include "byte.h"
#include "imagen.h"
#include "codificar.h"

using namespace std;

bool ocultar(Imagen& img,char mensaje[]){
	bool ok;
	int total=(strlen(mensaje)+1);
	if(total*8 <= img.filas()*img.columnas()){
		byte letra, b_img;
		int contador=0;
		for(int i=0;i<=total;i++){	
			letra = mensaje[i];
			for(int j=7; j>=0; j--){		
				b_img=img.getPos(contador);
				if(get(letra,j)==1){
					on(b_img,0);
				}else{
					off(b_img,0);
				}
				img.setPos(contador, b_img);
				contador++;
			}
		}
		ok=true;
	}else{
		ok=false;
	}
	return ok;
}
bool revelar(Imagen& img,char mensaje[], const int MAXTAM){
    bool ok=true;
    byte letra=255;
    int contador_letra = 7;
    int contador_mensaje = 0;
    int maxtam = 0;
    for (int i=0; (i<img.filas()*img.columnas()) || letra == 0 || ok ==false ;i++) {
        if (get(img.getPos(i),0)==0) {
            off(letra, contador_letra);
        }else{
            on(letra,contador_letra);
        }
        contador_letra--;
        if (contador_letra==-1) {
            if(maxtam == MAXTAM){
            	ok = false;
            }else{
	            contador_letra=7;
    	        mensaje[contador_mensaje]=letra;
    	        contador_mensaje++;
        	}
        }
    }
    return ok;
}

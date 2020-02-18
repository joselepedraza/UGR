#include<iostream>
#include<cmath>
#include<stdio>

using namespace std;

#define MAXIMO = 500;

int multiplicar(int num1, int num2){
	int res;
	res= num1 * num2;
	return res;
}

bool multiplicado(num3, num1, num2){
	bool multi = false;
	if(num3 == num1*num2)
		multi = true;
	return multi;
}

int main(){
	string vectors[4];
	int vector[100];
	double vector2[50];
	float vector3[10];
	char vector4[200];
	unsigned vector5[7];
	bool vector8[8];

	double var2;
	float var3;
	char var4;
	unsigned var6;
	unsigned var7;
	double var8;
	int num1;
	int num2;
	int num3;
	int num4;
	string var9;

	num1 = num2 = 5;
	num3 = multiplicar(num1, num2);

	if(multiplicado(num3, num1, num2)){
		for(int i = 0; i < 5; i++){
			num3++;
			num4 += (num3 - 1);
		}
	}
	else{
		num4 = 4;
		while(num4 <= 25){
			numero4++;
			if(numero3>0){
				numero3--;
				numero3*=1;
				numero3/=1;
			}
		}
	}
}


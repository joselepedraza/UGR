/*---------------*/
%{
	#include<stdio.h>
	#include<string.h>
	#include<string>
	#include<iostream>
	#include<utility>
	#include<set>

	int flaga=0,flags=0,flagm=0,flagd=0,op=0,cl=0, contadorlibrerias=0, flagmas = 0, flagmenos = 0,opc=0,clc=0,clv=0,crv=0,contfunciones=0;
	
	std::string losincludes[1000];

	std::set<std::pair<std::pair<std::string,std::string>,int> > variables; //aqui meteremos las funciones que hemos pillado tras el procesado 
	
	std::set<std::pair<std::string,std::string> > funciones;  //aqui meteremos las funciones que hemos pillado tras el procesado
	
	std::set<std::pair<std::pair<std::string,std::string>,std::string> > vectores;	//estructura donde se guardara la informacion referente al vector después del procesado	(debido al 3er puntero p3 no he podido definir el second como un int,
// por lo que solo mostraré los bloques reservados por el vector)


	void procesarVariable(char* nombreVariable);
	void procesarFuncion(char* nombreFuncion);
	void procesarVector(char* nombreVector);

	void procesartexto(char* texto);
	void imprimirVariables();
	void imprimirFunciones();
	void imprimirVectores();
	void imprimirlibreria();
%}

id [a-zA-Z]+
caracter [0-9]+
cadena [a-zA-ZñÑ0-9]+
variable [a-zA-ZñÑ0-9_]+
funcion [a-zA-ZñÑ0-9_]+[(]
libreria [a-zA-Z0-9.-><]+

vector [a-zA-ZñÑ0-9_]+[[]

/*-------------------*/
%%
{id}    {}
[+]     {flaga++;}
[-]     {flags++;}
[*]     {flagm++;}
[/]     {flagd++;}
[(]     {op++;}
[)]     {cl++;}
[{]	{opc++;}
[}]	{clc++;}
[[]	{clv++;}
[]]	{crv++;}
("++")	{flagmas++;}
("--")	{flagmenos++;}
(#include){libreria}		{losincludes[contadorlibrerias]=yytext;contadorlibrerias++;printf("Libreria localizada: %s \n",yytext);}
(#include)(" "){libreria}	{losincludes[contadorlibrerias]=yytext;contadorlibrerias++;printf("Libreria localizada: %s \n",yytext);}
(int)(" "){funcion}		{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(int)(" "){variable}		{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}


(double)(" "){funcion}		{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(double)(" "){variable}		{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}
(float)(" "){funcion}		{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(float)(" "){variable}		{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}
(char)(" "){funcion}		{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(char)(" "){variable}		{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}
(string)(" "){funcion}		{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(string)(" "){variable}		{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}
(bool)(" "){funcion}		{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(bool)(" "){variable}		{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}
(unsigned)(" "){funcion}	{printf("Funcion localizada: %s \n",yytext);procesarFuncion(yytext);contfunciones++;}
(unsigned)(" "){variable}	{printf("Variable localizada: %s \n",yytext);procesarVariable(yytext);}

(int)(" "){vector}{caracter}"]"		{printf("Vector localizado: %s \n",yytext);procesarVector(yytext);}
(char)(" "){vector}{caracter}"]"		{printf("Vector localizado: %s \n",yytext);procesarVector(yytext);}
(double)(" "){vector}{caracter}"]"		{printf("Vector localizado: %s \n",yytext);procesarVector(yytext);}
(float)(" "){vector}{caracter}"]"		{printf("Vector localizado: %s \n",yytext);procesarVector(yytext);}
(unsigned)(" "){vector}{caracter}"]"		{printf("Vector localizado: %s \n",yytext);procesarVector(yytext);}
(bool)(" "){vector}{caracter}"]"		{printf("Vector localizado: %s \n",yytext);procesarVector(yytext);}

%%

int main (int argc, char *argv[]) {
 if(argc == 2) {
 	yyin = fopen (argv[1],"rt");
 	if (yyin == NULL) {
 	printf ("El fichero %s no se puede abrir\n", argv[1]);
 	exit (-1);
 	}
 }
else yyin = stdin;
yylex ();
printf("*****************ANALISIS DEL CODIGO*****************\n");
	if((contfunciones+op)-cl==0 && opc-clc==0)
	{
		printf("La expresion es correcta\n");
	}
	else
	{
		printf("La expresion NO es correcta\n");
	}
	printf("\n");
	printf("Los operadores son:\n");
	if(flaga>=1) printf("+ ha aparecido %i veces\n", flaga);
	if(flags>=1) printf("- ha aparecido %i veces\n", flags);
	if(flagm>=1) printf("* ha aparecido %i veces\n", flagm);
	if(flagd>=1) printf("/ ha aparecido %i veces\n", flagd);
	if(flagmas>=1) printf("++ ha aparecido %i veces\n", flagmas);
	if(flagmenos>=1) printf("-- ha aparecido %i veces\n", flagmenos);
	printf("\n");
	printf("Se han usado las bibliotecas:\n");
	imprimirlibreria();
	printf("\n");
	imprimirVariables();
	printf("\n");
	imprimirVectores();
	printf("\n");
	imprimirFunciones();
	
	return 0;
}

void procesarVariable(char* nombreVariable){
    
    char * pNombre;
    char *tipo=(char *)malloc(200);
    char *nombre=(char *)malloc(200);  
	std::pair<std::pair<std::string,std::string>,int> variable;


	pNombre=strchr(nombreVariable,' ');							//puntero al espacio ' '
    strncpy(tipo,nombreVariable,pNombre-nombreVariable);
	variable.first.first=tipo;								        //copia el tipo

    strncpy(nombre,pNombre+1,strlen(nombreVariable));
	variable.first.second=nombre;			                            //copia el nombre

	//dependiendo del tipo de variable, guardaremos en .second su tamaño reservado en memoria
	if(variable.first.first == "bool"){
		variable.second=sizeof(bool);
	}
	else if(variable.first.first == "char"){
		variable.second=sizeof(char);
	}
	else if(variable.first.first == "int"){
		variable.second=sizeof(int);
	}
	else if(variable.first.first == "double"){
		variable.second=sizeof(double);
	}
	else if(variable.first.first == "float"){
		variable.second=sizeof(float);
	}
	else if(variable.first.first == "string"){
		variable.second=sizeof(std::string);
	}
	else if(variable.first.first == "unsigned"){
		variable.second=sizeof(unsigned);
	}
	else{
		variable.second=sizeof(variable.first.first);
	}

	variables.insert(variable);

}

void imprimirVariables(){

	std::set<std::pair<std::pair<std::string,std::string>,int> >::iterator it;
	
	std::pair<std::pair<std::string,std::string>,int> variable;
	int memoriareservada=0;
	std::cout<<"Existen "<<variables.size()<<" variables."<<std::endl;
	for(it=variables.begin(); it!=variables.end(); it++){
		std::cout<<"Tipo: "<<(*it).first.first<<"\tNombre: "<<(*it).first.second<<"\tTamaño reservado: "<<(*it).second << " Bytes" <<std::endl;
		memoriareservada+=(*it).second;
	}
	std::cout<<"Total de memoria reservada por las variables: " << memoriareservada << " Bytes" <<std::endl;
}

void procesarVector(char* nombreVector){
    
    char * p1;
	char * p2;
	char * p3;
    char *tipo=(char *)malloc(200);
    char *nombre=(char *)malloc(200);  
	char *tam=(char *)malloc(500);
	std::pair<std::pair<std::string,std::string>,std::string> vector;


	p1=strchr(nombreVector,' ');							//puntero al espacio ' '
    strncpy(tipo,nombreVector,p1-nombreVector);
	vector.first.first=tipo;								        //copia el tipo
	p2=strchr(nombreVector,'[');							//puntero al corchete '['
    strncpy(nombre,p1+1,p2-p1-1);
	vector.first.second=nombre;			            //copia el nombre

	p3=strchr(nombreVector,']');
	strncpy(tam,p2+1,p3-p2-1);
	vector.second=tam;

	//dependiendo del tipo de variable, guardaremos en .second su tamaño reservado en memoria
	//multiplicado por el tamaño del vector (el casteo en C me ha dado comederos de cabeza, deberiamos redefinir el operador * y hacerlo de otra manera)
/*	unsigned long int tama=(unsigned long int)tam*sizeof(vector.first.first);
	vector.second=(char*)tama;
	if(vector.first.first == "bool"){
		unsigned long int tama=(unsigned long int)tam*sizeof(bool);
		vector.second=(char*)tama;
	}
	else if(vector.first.first == "char"){
		unsigned long int tama=(unsigned long int)tam*sizeof(char);
		vector.second=(char*)tama;
	}
	else if(vector.first.first == "int"){
		unsigned long int tama=(unsigned long int)tam*sizeof(int);
		vector.second=tama;
	}
	else if(vector.first.first == "double"){
		unsigned long int tama=(unsigned long int)tam*sizeof(double);
		vector.second=(char*)tama;
	}
   else if(vector.first.first == "float"){
		unsigned long int tama=(unsigned long int)tam*sizeof(float);
		vector.second=(char*)tama;
	}
	else if(vector.first.first == "string"){
		unsigned long int tama=(unsigned long int)tam*sizeof(std::string);
		vector.second=(char*)tama;
	}
	else if(vector.first.first == "unsigned"){
		unsigned long int tama=(unsigned long int)tam*sizeof(unsigned);
		vector.second=(char*)tama;
	}
	else{
		unsigned long int tama=(unsigned long int)tam*sizeof(vector.first.first);
		vector.second=(char*)tama;
	}*/

	vectores.insert(vector);
}

void imprimirVectores(){

	std::set<std::pair<std::pair<std::string,std::string>,std::string> >::iterator it;
	
	std::pair<std::pair<std::string,std::string>,std::string> vector;

	std::cout<<"Existen "<<vectores.size()<<" vectores:"<<std::endl;
	for(it=vectores.begin(); it!=vectores.end(); it++){
		std::cout<<"Tipo: "<<(*it).first.first<<"\tNombre: "<<(*it).first.second<<"\tTamaño del vector: "<< (*it).second <<std::endl;
	}
}

void procesarFuncion(char* nombreFuncion){
    
    char * p1;
	char * p2;
    char *tipo=(char *)malloc(200);
    char *nombre=(char *)malloc(200);  
	std::pair<std::string,std::string> funcion;


	p1=strchr(nombreFuncion,' ');							//puntero al espacio ' '
    strncpy(tipo,nombreFuncion,p1-nombreFuncion);
	funcion.first=tipo;								        //copia el tipo
	p2=strchr(nombreFuncion,'(');							//puntero al parentesis '('
    strncpy(nombre,p1+1,p2-p1-1);
	funcion.second=nombre;			                            //copia el nombre

	funciones.insert(funcion);

}

void imprimirFunciones(){

	std::set<std::pair<std::string,std::string> >::iterator it;
	
	std::pair<std::string,std::string> funcion;

	std::cout<<"Existen "<<funciones.size()<<" funciones."<<std::endl;
	for(it=funciones.begin(); it!=funciones.end(); it++){
		std::cout<<"Tipo: "<<(*it).first<<"\tNombre: "<<(*it).second<<std::endl;
	}
}

void imprimirlibreria(){
	for(int i=0; i < contadorlibrerias; i++)
		std::cout<< losincludes[i] << std::endl;
}

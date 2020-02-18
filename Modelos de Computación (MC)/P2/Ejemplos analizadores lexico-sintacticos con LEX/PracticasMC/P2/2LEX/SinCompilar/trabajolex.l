/*---------------*/
%{
	#include<stdio.h>
	#include<string.h>
	#include<string>
	#include<iostream>
	#include<utility>
	#include<set>

	int flaga=0,flags=0,flagm=0,flagd=0,op=0,cl=0, contadorlibrerias=0, flagmas = 0, flagmenos = 0,opc=0,clc=0,contfunciones=0;
	
	std::string losincludes[1000];

	std::set<std::pair<std::string,std::string> > variables; //aqui meteremos las funciones que hemos pillado tras el procesado 
	std::set<std::pair<std::string,std::string> > funciones;  //aqui meteremos las funciones que hemos pillado tras el procesado

	void procesarVariable(char* nombreVariable);
	void procesarFuncion(char* nombreFuncion);
	void procesartexto(char* texto);
	void imprimirVariables();
	void imprimirFunciones();
	void imprimirlibreria();
%}

id [a-zA-Z]+
caracter [0-9]
cadena [a-zA-ZñÑ0-9]+
variable [a-zA-ZñÑ0-9_]+
funcion [a-zA-ZñÑ0-9_]+[(]
libreria [a-zA-Z0-9.-><]+

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
	imprimirFunciones();
	
	return 0;
}

void procesarVariable(char* nombreVariable){
    
    char * pNombre;
    char *tipo=(char *)malloc(200);
    char *nombre=(char *)malloc(200);  
	std::pair<std::string,std::string> variable;


	pNombre=strchr(nombreVariable,' ');							//puntero al espacio ' '
    strncpy(tipo,nombreVariable,pNombre-nombreVariable);
	variable.first=tipo;								        //copia el tipo

    strncpy(nombre,pNombre+1,strlen(nombreVariable));
	variable.second=nombre;			                            //copia el nombre

	variables.insert(variable);

}

void imprimirVariables(){

	std::set<std::pair<std::string,std::string> >::iterator it;
	
	std::pair<std::string,std::string> variable;

	std::cout<<"Existen "<<variables.size()<<" variables."<<std::endl;
	for(it=variables.begin(); it!=variables.end(); it++){
		std::cout<<"Tipo: "<<(*it).first<<"\tNombre: "<<(*it).second<<std::endl;
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

/*Seccion de Declaraciones*/
/*subseccion donde indicamos al preprocesador lo que queremos que aparezca tal cual*/
%{
	#include<stdio.h>
	#include<string.h>
	#include<string>
	#include<iostream>
	#include<utility>
	#include<set>

	//declaramos todos los contadores que utilizaremos
	int cadd=0,csub=0,cmul=0,cdiv=0,op=0,cl=0,clib=0,ccmas=0,ccmenos=0,
			opc=0,clc=0,clv=0,crv=0,cfun=0,memvectores=0;
	
	//vector donde guardaremos la informacion referente a los include durante el procesado
	std::string losincludes[2000];
	//estructura donde se guardara la informacion referente a las variables durante el procesado 
	std::set<std::pair<std::pair<std::string,std::string>,int> > variables;	//(tipo, nombre, memoria reservada)
	//estructura donde se guardara la informacion referente al vector durante el procesado
	std::set<std::pair<std::pair<std::string,std::string>,std::string> > vectores;	
	//estructura donde se guardara la informacion referente a las funciones durante el procesado
	std::set<std::pair<std::string,std::string> > funciones;  


	void analizarVariable(char* nombreVariable);
	void analizarFuncion(char* nombreFuncion);
	void analizarVector(char* nombreVector);
	void mostrarVariables();
	void mostrarFunciones();
	void mostrarVectores();		
	void mostrarLibreria();
/*subseccion de definicion de alias*/
%}

id [a-zA-Z]+
caracter [0-9]+
cadena [a-zA-ZñÑ0-9]+
variable [a-zA-ZñÑ0-9_]+
vector [a-zA-ZñÑ0-9_]+[[]
funcion [a-zA-ZñÑ0-9_]+[(]
libreria [a-zA-Z0-9.-><]+

/*Seccion de Reglas*/
%%

{id}	{}
[+]	{cadd++;}
[-]	{csub++;}
[*]	{cmul++;}
[/]	{cdiv++;}
[(]	{op++;}
[)]	{cl++;}
[{]	{opc++;}
[}]	{clc++;}
("++")	{ccmas++;}
("--")	{ccmenos++;}

(#include){libreria}		{losincludes[clib]=yytext;clib++;printf("Libreria: %s \n",yytext);}
(#include)(" "){libreria}	{losincludes[clib]=yytext;clib++;printf("Libreria: %s \n",yytext);}

(int)(" "){funcion}		{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}
(double)(" "){funcion}		{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}
(float)(" "){funcion}		{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}
(char)(" "){funcion}		{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}
(string)(" "){funcion}		{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}
(bool)(" "){funcion}		{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}
(unsigned)(" "){funcion}	{printf("Funcion: %s \n",yytext);analizarFuncion(yytext);cfun++;}

(int)(" "){variable}		{printf("Variable: %s \n",yytext);analizarVariable(yytext);}
(double)(" "){variable}		{printf("Variable: %s \n",yytext);analizarVariable(yytext);}
(float)(" "){variable}		{printf("Variable: %s \n",yytext);analizarVariable(yytext);}
(char)(" "){variable}		{printf("Variable: %s \n",yytext);analizarVariable(yytext);}
(string)(" "){variable}		{printf("Variable: %s \n",yytext);analizarVariable(yytext);}
(bool)(" "){variable}		{printf("Variable: %s \n",yytext);analizarVariable(yytext);}
(unsigned)(" "){variable}	{printf("Variable: %s \n",yytext);analizarVariable(yytext);}

(int)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}
(char)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}
(double)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}
(float)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}
(unsigned)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}
(bool)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}
(string)(" "){vector}{caracter}"]"		{printf("Vector: %s \n",yytext);analizarVector(yytext);}

%%
/*Seccion de Procedimientos de Usuario*/
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
printf("\t\t\t*****PARSER C++*****\n");
	if((cfun+op)-cl==0 && opc-clc==0)
	{
		printf("La expresion es correcta\n");
	}
	else
	{
		printf("La expresion NO es correcta\n");
	}

	printf("\n");
	printf("El operador:\n");
	if(cadd>=1) printf(" + \taparece\t %i veces\n", cadd);
	if(csub>=1) printf(" - \taparece\t %i veces\n", csub);
	if(cmul>=1) printf(" * \taparece\t %i veces\n", cmul);
	if(cdiv>=1) printf(" / \taparece\t %i veces\n", cdiv);
	if(ccmas>=1) printf(" ++ \taparece\t %i veces\n", ccmas);
	if(ccmenos>=1) printf(" -- \taparece\t %i veces\n", ccmenos);
	printf("\n");
	printf("Usa las librerias:\n");
	mostrarLibreria();
	printf("\n");
	mostrarVariables();
	printf("\n");
	mostrarVectores();
	printf("\n");
	mostrarFunciones();
	
	return 0;
}

void analizarVariable(char* nombreVariable){
    
	char * pNombre;
	char *tipo=(char *)malloc(400);
	char *nombre=(char *)malloc(400);
	std::pair<std::pair<std::string,std::string>,int> variable;


	pNombre=strchr(nombreVariable,' ');							//puntero al espacio ' '
	strncpy(tipo,nombreVariable,pNombre-nombreVariable);
	variable.first.first=tipo;										//guarda el tipo

	strncpy(nombre,pNombre+1,strlen(nombreVariable));
	variable.first.second=nombre;									//guarda el nombre

	//dependiendo del tipo de variable, guardamos en .second su tamaño reservado en memoria
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

	variables.insert(variable);

}

void mostrarVariables(){

	std::set<std::pair<std::pair<std::string,std::string>,int> >::iterator it;
	
	std::pair<std::pair<std::string,std::string>,int> variable;
	int memoriareservada=0;
	std::cout<<"Existen "<<variables.size()<<" variables:"<<std::endl;
	for(it=variables.begin(); it!=variables.end(); it++){
		std::cout<<"Tipo: "<<(*it).first.first<<"\t\tNombre: "<<(*it).first.second<<"\t\tTamaño reservado: "<<(*it).second << " Bytes" <<std::endl;
		memoriareservada+=(*it).second;
	}
	std::cout<<"Total de memoria reservada por las variables: " << memoriareservada << " Bytes" <<std::endl;
}

void analizarVector(char* nombreVector){
    
   char * p1;
	char * p2;
	char * p3;
   char *tipo=(char *)malloc(200);
   char *nombre=(char *)malloc(200);  
	char *tam=(char *)malloc(500);
	std::pair<std::pair<std::string,std::string>,std::string> vector;


	p1=strchr(nombreVector,' ');						//puntero al espacio ' '
   strncpy(tipo,nombreVector,p1-nombreVector);
	vector.first.first=tipo;							//copia el tipo
	p2=strchr(nombreVector,'[');						//puntero al corchete '['
   strncpy(nombre,p1+1,p2-p1-1);
	vector.first.second=nombre;						//copia el nombre
	p3=strchr(nombreVector,']');						//puntero al ultimo corchete ']'
	strncpy(tam,p2+1,p3-p2-1);

	//dependiendo del tipo de variable, guardaremos en .second su tamaño reservado en memoria
	//multiplicado por el tamaño del vector
	int tamint = strtol(tam,&p3-1,10);		//devuelve el entero 
	char tama[5];

	if(vector.first.first == "bool"){
		tamint = tamint*sizeof(bool);
		sprintf(tama, "%d", tamint);
		vector.second=tama;							//copia el tamaño del vector
	}
	else if(vector.first.first == "char"){
		tamint = tamint*sizeof(char);
		sprintf(tama, "%d", tamint);
		vector.second=tama;	
	}
	else if(vector.first.first == "int"){
		tamint = tamint*sizeof(int);
		sprintf(tama, "%d", tamint);
		vector.second=tama;	
	}
	else if(vector.first.first == "double"){
		tamint = tamint*sizeof(double);
		sprintf(tama, "%d", tamint);
		vector.second=tama;	
	}
	else if(vector.first.first == "float"){
		tamint = tamint*sizeof(float);
		sprintf(tama, "%d", tamint);
		vector.second=tama;	
	}
	else if(vector.first.first == "string"){
		tamint = tamint*sizeof(std::string);
		sprintf(tama, "%d", tamint);
		vector.second=tama;	
	}
	else if(vector.first.first == "unsigned"){
		tamint = tamint*sizeof(unsigned);
		sprintf(tama, "%d", tamint);
		vector.second=tama;	
	}
	memvectores+=tamint;
	vectores.insert(vector);

}

void mostrarVectores(){

	std::set<std::pair<std::pair<std::string,std::string>,std::string> >::iterator it;
	
	std::pair<std::pair<std::string,std::string>,std::string> vector;
	std::cout<<"Existen "<<vectores.size()<<" vectores:"<<std::endl;
	for(it=vectores.begin(); it!=vectores.end(); it++){
		std::cout<<"Tipo: "<<(*it).first.first<<"\t\tNombre: "<<(*it).first.second<<"\t\tTamaño reservado: "<< (*it).second <<" Bytes" <<std::endl;
	}

	std::cout<<"Total de memoria reservada por los vectores: " << memvectores << " Bytes" <<std::endl;

}

void analizarFuncion(char* nombreFuncion){
    
   char * p1;
	char * p2;
   char *tipo=(char *)malloc(400);
   char *nombre=(char *)malloc(400);  
	std::pair<std::string,std::string> funcion;


	p1=strchr(nombreFuncion,' ');							//puntero al espacio ' '
   strncpy(tipo,nombreFuncion,p1-nombreFuncion);
	funcion.first=tipo;								      //copia el tipo
	p2=strchr(nombreFuncion,'(');							//puntero al parentesis '('
   strncpy(nombre,p1+1,p2-p1-1);
	funcion.second=nombre;									//copia el nombre

	funciones.insert(funcion);

}

void mostrarFunciones(){

	std::set<std::pair<std::string,std::string> >::iterator it;
	
	std::pair<std::string,std::string> funcion;

	std::cout<<"Existen "<<funciones.size()<<" funciones:"<<std::endl;
	for(it=funciones.begin(); it!=funciones.end(); it++){
		std::cout<<"Tipo: "<<(*it).first<<"\t\tNombre: "<<(*it).second<<std::endl;
	}
}

void mostrarLibreria(){
	for(int i=0; i < clib; i++)
		std::cout<< losincludes[i] << std::endl;
}

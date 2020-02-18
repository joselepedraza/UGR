                 /*----- Sección de Declaraciones --------------*/ 
%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int fin;
char opcion1;
char opcion2;
char opcion3;
char palabra[20];

int bpolitica;
int bcultura;
int bgastronomia;
int beconomia;
int bdeporte;
int bnacional;
int binternacional;
int bciencia;

FILE *fichero1;
FILE *fichero2;
FILE *fichero3;
FILE *fichero4;
FILE *fichero5;
FILE *fichero6;
FILE *fichero7;
FILE *fichero8;


%}

politica	(politica)
cultura		(cultura|social|opinion|television|radio)
gastronomia	(gastronomia|comida|obesidad)
economia	(economia)
deporte		(deportes|futbol|natacion|baloncesto|motor)
nacional	(madrid|espana|andalucia|baleares)
internacional	(internacional)
ciencia		(ciencia|tecnologia)


%%
                 /*----- Sección de Reglas ----------------*/ 

.|\n         {}

"<a href=".*cultura.*"a>"		{if(bcultura==1){printf("\nCUlTURA: %s \n",yytext);fputs(yytext,fichero1);fputs("\n",fichero1);}}
"<a href=".*politica.*"a>"		{if(bpolitica==1){printf("\nPOLITICA: %s \n",yytext);fputs(yytext,fichero2);fputs("\n",fichero2);}}
"<a href=".*gastronomia.*"a>"		{if(bgastronomia==1){printf("\nGASTRONOMIA: %s \n",yytext);fputs(yytext,fichero3);fputs("\n",fichero3);}}
"<a href=".*economia.*"a>"		{if(beconomia==1){printf("\nECONOMIA: %s \n",yytext);fputs(yytext,fichero4);fputs("\n",fichero4);}}
"<a href=".*deporte.*"a>"		{if(bdeporte==1){printf("\nDEPORTE: %s \n",yytext);fputs(yytext,fichero5);fputs("\n",fichero5);}}
"<a href=".*nacional.*"a>"		{if(bnacional==1){printf("\nNACIONAL: %s \n",yytext);fputs(yytext,fichero6);fputs("\n",fichero6);}}
"<a href=".*internacional.*"a>"		{if(binternacional==1){printf("\nINTERNACIONAL: %s \n",yytext);fputs(yytext,fichero7);fputs("\n",fichero7);}}
"<a href=".*ciencia.*"a>"		{if(bciencia==1){printf("\nCIENCIA: %s \n",yytext);fputs(yytext,fichero8);fputs("\n",fichero8);}}



%%   
                /*----- Sección de Procedimientos --------*/ 

int main (int argc, char *argv[])
{   
  if (argc == 2)   
  {     
    yyin = fopen (argv[1], "rt");     

    if (yyin == NULL)     
    {       
      printf ("El fichero %s no se puede abrir\n", argv[1]);       
      exit (-1);     
    }   
  }   
  else yyin = stdin; 

	fin=1;

	  do{
		printf("\nElija una opcion:\n \t1.- Parsear el diario ELMUNDO\n \t2.- Ir al la pagina del diario ELMUNDO\n \tq.- Salir\n");
		scanf("%c",&opcion1);
		switch(opcion1){		  
			case '2': system(" firefox www.elmundo.es ");break;
			case 'q': fin=0; remove("cultura.txt"); remove("politica.txt"); remove("gastronomia.txt"); remove("economia.txt"); remove("deportes.txt");remove("nacional.txt");remove("internacional.txt");remove("ciencia.txt");break;

			case '1': scanf("%c",&opcion2);	
				  printf("Elija que tipo de noticia quiere consultar:\n \t1.- Cultura\n \t2.- Politica\n \t3.- Gastronomia\n \t4.- Economia\n \t5.- Deportes\n \t6.- Nacional\n \t7.- Internacional\n \t8.- Ciencia\n \t9.- Todas\n");
				  scanf("%c",&opcion2);

				  switch(opcion2){
					case '1': bcultura=1;bpolitica=0;bgastronomia=0;beconomia=0;bdeporte=0;bnacional=0;binternacional=0;bciencia=0;fichero1=fopen("cultura.txt","w+");yylex();fclose(fichero1);break;

					case '2': bcultura=0;bpolitica=1;bgastronomia=0;beconomia=0;bdeporte=0;bnacional=0;binternacional=0;bciencia=0;fichero2=fopen("politica.txt","w+");yylex();fclose(fichero2);break;

					case '3': bcultura=0;bpolitica=0;bgastronomia=1;beconomia=0;bdeporte=0;bnacional=0;binternacional=0;bciencia=0;fichero3=fopen("gastronomia.txt","w+");yylex();fclose(fichero3);break;

					case '4': bcultura=0;bpolitica=0;bgastronomia=0;beconomia=1;bdeporte=0;bnacional=0;binternacional=0;bciencia=0;fichero4=fopen("economia.txt","w+");yylex();fclose(fichero4);break;

					case '5': bcultura=0;bpolitica=0;bgastronomia=0;beconomia=0;bdeporte=1;bnacional=0;binternacional=0;bciencia=0;fichero5=fopen("deportes.txt","w+");yylex();fclose(fichero5);break;
					
					case '6': bcultura=0;bpolitica=0;bgastronomia=0;beconomia=0;bdeporte=0;bnacional=1;binternacional=0;bciencia=0;fichero6=fopen("nacional.txt","w+");yylex();fclose(fichero6);break;

					case '7': bcultura=0;bpolitica=0;bgastronomia=0;beconomia=0;bdeporte=0;bnacional=0;binternacional=1;bciencia=0;fichero7=fopen("internacional.txt","w+");yylex();fclose(fichero7);break;

					case '8': bcultura=0;bpolitica=0;bgastronomia=0;beconomia=0;bdeporte=1;bnacional=0;binternacional=0;bciencia=1;fichero8=fopen("ciencia.txt","w+");yylex();fclose(fichero8);break;

					case '9': bcultura=1;bpolitica=1;bgastronomia=1;beconomia=1;bdeporte=1;bnacional=1;binternacional=1;bciencia=1;fichero1=fopen("cultura.txt","w+");fichero2=fopen("politica.txt","w+");fichero3=fopen("gastronomia.txt","w+");fichero4=fopen("economia.txt","w+");fichero5=fopen("deportes.txt","w+");fichero6=fopen("nacional.txt","w+");fichero7=fopen("internacional.txt","w+");fichero8=fopen("ciencia.txt","w+");yylex();fclose(fichero1);fclose(fichero2);fclose(fichero3);fclose(fichero4);fclose(fichero5);fclose(fichero6);fclose(fichero7);fclose(fichero8);break;
				  }

				  yyin = fopen (argv[1], "rt");
				
		}
	   scanf("%c",&opcion1);
	  }while(fin==1); 
}

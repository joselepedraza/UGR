#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		perror("\nError , parametro = un numero a comprobar");
		exit(-1);
	}

	pid_t pid;
	pid = fork();
	
	if (pid < 0){
		perror("\nError en el fork");
		exit(-1);
	}
	else if (pid == 0){	//proceso hijo
				
		printf("Proceso hijo y mi pid es: %d y el de mi padre es %d. Voy a comprobar si el numero introducido es par o impar \n ", getpid(), getppid());

		int numero = atoi(argv[1]);

		if ((numero % 2) == 1)
			printf("El numero %d es impar \n" , numero);
		else 
			printf("El numero %d es par \n" , numero);
	}
	else if (pid){	//proceso padre
		printf("Proceso padre y mi pid es: %d y el de mi hijo es %d, y voy a comprobar si el numero introducido es divisible por 4 \n",getpid()
, pid);
		int numero = atoi(argv[1]);
		if (numero % 4 == 0)
			printf("El numero %d es divisible por 4 \n" , numero);
		else 
			printf("El numero %d no es divisible por 4 \n" , numero);
	}
return(0);
}

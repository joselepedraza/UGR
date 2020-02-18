#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/wait.h>

int main(){
int i, estado;
pid_t PID;
//CREAMOS HIJOS
for(i=0; i<5; i++){
	if((PID = fork())<0){
		perror("Error en fork\n");
		exit(-1);
	}
	if(PID==0){//Hijo imprime y muere
		printf("Soy el hijo PID = %i\n", getpid());
		exit(0);
	}
}
//ESPERAMOS HIJOS
for(i=4; i>=0; i--){
	PID = wait(&estado);
	printf("Ha finalizado mi hijo con PID = %i\n", PID);
	printf("Solo me quedan %i hijos vivos\n", i);
}
}

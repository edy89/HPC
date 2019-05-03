#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

pid_t pid;
key_t clave,clave2;	//Clave de acceso a la zona de memoria
long int id,id2;	//Identificador de la zona de memoria
int *pmem=NULL;	//Puntero a la zona de memoria

typedef struct {
	int **m,i;
}pack;

int main(int argc, char *argv[]) {

	//Creamos un área de memoria compartida
	clave=ftok("/bin/ls",33); //Cualquier fichero existente y cualquier int
	//clave2=ftok("/bin/ls",34); 
	id=shmget(clave,sizeof(pack)*100,0777|IPC_CREAT);
	printf("%ld\n",id);
	//id2=shmget(clave2,sizeof(int)*100,0777|IPC_CREAT);
	pmem=(int *)shmat(id,(pack *)0,0);
	//printf("%ld\n",pmem);
	pack *p;
	p->i = 10;
	printf("%d\n",p->i);
	
	pid = fork();
	if (pid == 0){
		//Soy el proceso hijo
		pmem[0] = 17; //Escribo en la memoria
		//p->i[0] = 15;
	}
	else{
		//Soy el proceso padre
		usleep(100);
		printf("Leído: %d\n", pmem[0]);
		shmdt((pack*)id); //Desconecta el segmento de memoria compartida
		shmctl(id,IPC_RMID,0); //Elimina el segmento de memoria compartida
	}
}
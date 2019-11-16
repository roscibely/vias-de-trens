#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include <sys/shm.h>
#include <stdio.h>

#define N 20

sem_t  S1, S2, S3, S4, mutex; //Semaforos. 

int Trem1[N], Trem2[N], Trem3[N], Trem[N];

Trem1[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17.18,19,20};
Trem2[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17.18,19,20};
Trem3[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17.18,19,20};
Trem4[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17.18,19,20};

//Funcao para thread Trens
void    *threadTrem1(void *arg){
	int n =0;
	while(1){
		sem_wait(&mutex); //Down em mutex
		printf("Trem 1: posicao %d", Trem1[n]);
		n++;
		if(n==4)
			sem_wait(&S1); //Down em S1
		if(n==9){
			sem_wait(&S2); //Down em S2
			sem_post(&S1); //Up em S1
		}
		if(n==15){
			sem_post(&S2); //Up em S2
			sem_post(&mutex); //Up em mutex
		}
		if(n==19){
			n=0;
		}
	} 
 
}

void    *threadTrem2(void *arg){
	int n =0;	
	while(1){
		sem_wait(&mutex); //Down em mutex
		printf("Trem 2: posicao %d", Trem2[n]);
		n++;
		if(n==4)
			sem_wait(&S3); //Down em S1
		if(n==9){
			sem_wait(&S1); //Down em S2
			sem_post(&S3); //Up em S1
		}
		if(n==15){
			sem_post(&S1); //Up em S2
			sem_post(&mutex); //Up em mutex
		}
		if(n==19){
			n=0;
		}
	}  	
}

void    *threadTrem3(void *arg){
	int n =0;
	while(1){
		sem_wait(&mutex); //Down em mutex
		printf("Trem 3: posicao %d", Trem3[n]);
		n++;
		if(n==4)
			sem_wait(&S2); //Down em S1
		if(n==9){
			sem_wait(&S4); //Down em S2
			sem_post(&S2); //Up em S1
		}
		if(n==15){
			sem_post(&S4); //Up em S2
			sem_post(&mutex); //Up em mutex
		}
		if(n==19){
			n=0;
		}
	} 
}

void    *threadTrem4(void *arg){
	int n =0;
	while(1){
		sem_wait(&mutex); //Down em mutex
		printf("Trem 4: posicao %d", Trem4[n]);
		n++;
		if(n==4)
			sem_wait(&S4); //Down em S1
		if(n==9){
			sem_wait(&S3); //Down em S2
			sem_post(&S4); //Up em S1
		}
		if(n==15){
			sem_post(&S3); //Up em S2
			sem_post(&mutex); //Up em mutex
		}
		if(n==19){
			n=0;
		}
	}  
}


int main(void){
	int s1, s2, s3, s4, mutex; 
	pthread_t   endereco_thread_trem1, endereco_thread_trem2, endereco_thread_trem3, endereco_thread_trem4;
	int res;
	int i;
	
	//Preenche os vetores que representa os trens
	for(i=0; i<N; i++){
		Trem1[i] =i;
		Trem2[i]=i; 
		Trem3[i]=i; 
		Trem[i]=i;
	}
	
	//Semaforos
	mutex = sem_init(&mutex, 0, 3);   //Inicializacao do semaforo.
    if (s1 != 0) {
        perror("\tFalha na Inicializacao do semaforo.");
        exit(EXIT_FAILURE);
    }
    
	s1 = sem_init(&S1, 0, 1);   //Inicializacao do semaforo.
    if (s1 != 0) {
        perror("\tFalha na Inicializacao do semaforo.");
        exit(EXIT_FAILURE);
    }
    s2 = sem_init(&S2, 0, 1);  //Inicializacao do semaforo.
    if (s2 != 0) {
        perror("\tFalha na Inicializacao do semaforo.");
        exit(EXIT_FAILURE);
    }
    s3 = sem_init(&S3, 0, 1);  //Inicializacao do semaforo.
    if (s3 != 0) {
        perror("\tFalha na Inicializacao do semaforo.");
        exit(EXIT_FAILURE);
    }
	s4 = sem_init(&S4, 0, 1);  //Inicializacao do semaforo.
    if (s4 != 0) {
        perror("\tFalha na Inicializacao do semaforo.");
        exit(EXIT_FAILURE);
    }	
    
	//Threads
	res = pthread_create(&endereco_thread_trem1, NULL, threadTrem1, NULL);
    if (res != 0) {
        perror("\tFalha na criacao da thread.\n");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&endereco_thread_trem2, NULL, threadTrem2, NULL);
    if (res != 0) {
        perror("\tFalha na criacao da thread.\n");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&endereco_thread_trem3, NULL, threadTrem3, NULL);
    if (res != 0) {
        perror("\tFalha na criacao da thread.\n");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&endereco_thread_trem4, NULL, threadTrem4, NULL);
    if (res != 0) {
        perror("\tFalha na criacao da thread.\n");
        exit(EXIT_FAILURE);
    }
    
	
	
	return 0;
}

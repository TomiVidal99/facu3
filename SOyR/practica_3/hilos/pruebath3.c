#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NTHREADSMAX 10
/*declaro la función para cumplir con el prototipo void *     (*start_routine)        ( void * )            
                                                   ^^^^^^      ^^^^^^^^^^^^^^           ^^^^^^      
                                                 devuelve    puntero a funcion        Argumento    
                                              puntero a void (nombre de la funcion)   de la funcion  
                                                                                      puntero a void*/  

void * do_algo(int *z) 
{

printf("soy el hilo numero %d\n",*z);
sleep (*z);
*z=*z+1;
pthread_exit((void *)z);
}                      

int main(int argc, char *argv[]) {

int rc, i, j, h[NTHREADSMAX], NTHREADS;
pthread_t tid[NTHREADSMAX];
int resultado[NTHREADSMAX];
if (argc!=2){
  printf("uso: tt nro_de_threads\n");
  exit(1);
  }
sscanf(argv[1],"%d",&NTHREADS);
for (j=0; j<NTHREADS; j++) {
    printf("creando hilo numero %d\n",j);
    h[j]=j;
    rc = pthread_create(&tid[j],NULL,(void*) do_algo, (void*) &h[j]);
    if (rc) {              
      printf("ERROR: Codigo devuelto por pthread_create()  %d\n", rc);
      exit(-1);
    }
}


int *res[NTHREADSMAX];
for (j=0; j<NTHREADS; j++) {
  rc = pthread_join(tid[j], (void*) &res[j]);
  if (rc) {
    printf("ERROR; return code from pthread_join() is %d\n", rc);
    exit(-1);
    }
    resultado[j]=*res[j];
}
for (j=0; j<NTHREADS; j++) {
  printf("el resultado del hilo %d es %d\n",j, resultado[j]);
  }
pthread_exit(NULL);
}

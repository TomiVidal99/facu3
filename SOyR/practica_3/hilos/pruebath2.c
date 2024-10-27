#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*Se utiliza esta función para cada hilo. devuelve un puntero a void y toa como entrada un puntero a entero.*/

void *do_algo(int *j) {

printf("soy el hilo numero %d\n",(int) *j);
sleep (1);
pthread_exit(NULL);
}                      

int main(int argc, char *argv[]) {

int rc, i, j, NTHREADS;
pthread_t tid;

if (argc!=2)
{
printf("uso: tt nro_de_threads\n");
exit(1);
}
sscanf(argv[1],"%d",&NTHREADS);
for (j=0; j<NTHREADS; j++) {
  /*Creo un hilo por vez  */
  rc = pthread_create(&tid,NULL,(void*) do_algo, (void*) &j);
  /*manejo de posible error*/
  if (rc) {              
    printf("ERROR: Codigo devuelto por pthread_create()  %d\n", rc);
    exit(-1);
    }

  /*Espero que termine el hilo que cree antes*/
  rc = pthread_join(tid, NULL);
  /*Manejo de errores*/
  if (rc) {
    printf("ERROR; return code from pthread_join() is %d\n", rc);
    exit(-1);
    }
  /*Si el hilo termino sin errores, voy a crear el siguiente*/
  }
pthread_exit(NULL);
}

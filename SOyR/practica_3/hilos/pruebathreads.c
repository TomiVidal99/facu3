#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *do_nothing(void *null) {
int i;
i=0;
pthread_exit(NULL);
}                      

int main(int argc, char *argv[]) {

int rc, i, j, NTHREADS;
pthread_t tid;

if (argc!=2)
{
printf("uso: pt nro_de_threads\n");
exit(1);
}
sscanf(argv[1],"%d",&NTHREADS);
for (j=0; j<NTHREADS; j++) {
  rc = pthread_create(&tid,NULL, do_nothing, NULL);
  if (rc) {              
    printf("ERROR; Codigo devuelto por pthread_create()  %d\n", rc);
    exit(-1);
    }

  /* Wait for the thread */
  rc = pthread_join(tid, NULL);
  if (rc) {
    printf("ERROR; Codigo devuelto por pthread_join()  %d\n", rc);
    exit(-1);
    }
  }
pthread_exit(NULL);
}

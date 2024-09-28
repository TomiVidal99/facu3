#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/***************************************************************************
Variables Globales*/

int activar = 0;
/*Fin de variables globales+++++++++++++++++++++++++++++++++++++++++++++++*/

void trapper(int);

int main(int argc, char *argv[]) {
  int i;
  do {
    printf("ingrese numero de señal a manejar\n");
    scanf("%d", &i);
    signal(i, trapper);
    printf(
        "Identificativo de proceso: %d\n espero una señal para continuar...\n",
        getpid());
    pause();
    printf("Continuando...variable activar= %d\n", activar);
  } while (1);
  return 0;
}

void trapper(int sig) {
  printf("Recibida la señal: %d\n", sig);
  activar = sig;
}

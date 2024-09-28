#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int descrip;
  pid_t var;
  int status;
  int salir = 0;
  FILE *pf;
  char nombre[100];
  printf("soy el padre y mi PID es %d \n", getpid());
  strncpy(nombre, "Mi nombre es juancito", 100);
  pf = fopen("datos.txt", "w+");
  if (pf == NULL) {
    printf("error de apertura de archivo datos.txt ");
    return 1;
  }
  do {

    if ((var = fork()) == 0) {
      int x;
      printf("\tSoy el hijo y fork me devolvio %d\n", var);
      printf("\tMi PID es %d \n", getpid());
      printf("\tEl PID de mi Padre es %d \n", getppid());
      printf("\tIntroduzca un numero:");
      scanf("%d", &x);
      fprintf(pf, "soy el hijo %d y el numero introducido es  %d\n", getpid(),
              x);
      return x;
    } else {
      printf("Soy el padre y fork me devolvio el pid de mi hijo %d \n", var);
      printf("Espero un tiempo a ver que sucede\n\n\n");
      printf("Mientras tanto imprimo mi mensaje: %s\n", nombre);
      printf("Si no termino el hijo, espero que termine \n\n");
      waitpid(var, &status, 0);
      fprintf(pf, " Mensaje impreso por el padre\n");
      if (WIFEXITED(status)) {
        printf("El hijo termino con status %d\n\n", WEXITSTATUS(status));
      }
      printf("el hijo cambio el mensaje? \n"),

          printf("%s\n Parece que no...\n", nombre);
      printf("Ahora lo cambio yo:\n");
      strncpy(nombre, "Mi nombre es Maria", 100);
      printf("El nuevo mensaje es: %s\n", nombre);

      printf("Para terminar ingrese 1, para seguir cualquier otro número\n");
      scanf("%d", &salir);
      if (salir != 1) {
        salir = 0;
      }
    }

  } while (salir == 0);
  fclose(pf);
  return 0;
}

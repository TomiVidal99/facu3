#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid1, pid2, pid3;
  int status1, status2, status3;
  int numero;
  if ((pid1 = fork()) == 0) { /* hijo */
    printf("\t1 Soy el primer hijo (%d, hijo de %d)\n", getpid(), getppid());
    printf("\t1 Ingresa cualquier entero para terminarme\n");
    scanf("%d", &numero);
    return numero;
  } else {                      /* padre */
    if ((pid2 = fork()) == 0) { /* segundo hijo */
      printf("\t2 Soy el segundo hijo (%d, hijo de %d)\n", getpid(), getppid());
      if ((pid3 = fork()) == 0) { /* nieto, hijo de hijo2 */
        printf("\t\tSoy el nieto %d hijo de %d\n", getpid(), getppid());
        printf("\t\tIngresa cualquier entero para terminarme\n");
        scanf("%d", &numero);
        return numero;
      } else { /*segundo hijo*/

        printf("\t2 Soy el segundo hijo %d, y recien cree un nieto %d\n",
               getpid(), pid3);
        printf("\t2 Ahora espero que termine el nieto\n");
        waitpid(pid3, &status3, 0);
        printf("\t2 Ya termino el proceso nieto %d con status %d\n", pid3,
               status3);
        return 0;
      }

    } else { /* padre */
      printf("1 Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
      printf("1 Soy el padre de %d y de %d\n", pid1, pid2);
      /* Esperamos al primer hijo */
      printf("1 Espero que termine mi primer hijo %d\n", pid1);
      waitpid(pid1, &status1, 0);
      /* Esperamos al segundo hijo */
      printf("1 Ya termino mi primer hijo %d con status %d. Espero que termine "
             "mi segundo hijo %d\n",
             pid1, status1, pid2);
      waitpid(pid2, &status2, 0);
      printf("1 Ya termino mi segundo hijo %d con status %d\n", pid2, status2);
    }
  }
  return 0;
}

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/definitions.h"

PIDStack childrenStack = {
    .PIDs = {},
    .count = 0,
};

int hasFinished = 0;
int main(void) {

  signal(SIGUSR1, handle_create_child_1); // registro la señal del usuario
  signal(SIGUSR2, handle_create_child_2); // registro la señal del usuario
  signal(
      SIGTERM,
      handle_terminate_child); // registro la señal de para terminar los hijos

  while (hasFinished == 0) {
  }

  printf("\n\nPrograma finalizado...\n");
  return 0;
}

void handle_create_child_1() {
  int forkPID = fork();
  if (forkPID != 0) {    // si no es 0, es el padre, y forkPID=childPID
    push_child(forkPID); // actualizo la pila con los hijos creados
    printf("Nuevo hijo!\n(hay %d hijos)\n", childrenStack.count);
    return;
  }
  // solo ejecutar este codigo si es el hijo

  int parentPID;
  int childPID = getpid();

  // porque cuando el padre no existe el PID se vuelve 1
  // es una medida de control
  while (parentPID != 1) {
    parentPID = getppid();
    printf("\t\tPID padre: %d \n\t\tPID hijo: %d\n", parentPID, childPID);
    sleep(CHILD_REPEAT_MSG_DELAY_SEC);
  }
}

void handle_create_child_2() {
  int forkPID = fork();
  if (forkPID != 0)
    return; // solo ejecutar este codigo si es el hijo

  int childPID = getpid();
  printf("Fui creado con SIGUSER2 y mi PID es %d", childPID);
  char* args[] = {"/usr/bin/ls", "--color", NULL};
  char* program = "/usr/bin/ls";
  execv(program, args);

}

void push_child(int pid) {
  childrenStack.count = childrenStack.count + 1;
  childrenStack.PIDs[childrenStack.count - 1] = pid;
  printf("pushing child (%d)\n", childrenStack.count);
}

int pop_child() {
  int pid = childrenStack.PIDs[childrenStack.count - 1];
  childrenStack.count = childrenStack.count - 1;
  printf("popping child (%d, %d)\n", childrenStack.count, pid);
  return pid;
}

/**
 * termina los procesos hijos uno por uno,
 * a una razón de uno por segundo
 */
void handle_terminate_child() {
  while (childrenStack.count > 0) {
    sleep(CHILDREN_WAIT_RATE_SEC);
    int pid = pop_child();
    printf("killing: %d\n", pid);
    kill(pid, SIGKILL);
  }
  hasFinished = 1;
}

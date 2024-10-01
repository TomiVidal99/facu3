#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
// #include <sys/wait.h>

#define CHILD_REPEAT_MSG_DELAY_SEC 5

typedef struct {
  int PIDs[100];
  int index;
} PIDStack;

PIDStack childrenStack = {
  .PIDs = {},
  .index = 0,
};

void handle_create_child(); // handler que crea el hijo cuando llega SIGUSR1
void handle_terminate_child();
void push_child(int);
int pop_child();

int main(void) {
  signal(SIGUSR1, handle_create_child); // registro la señal

  while (1) {
  }

  return 0;
}

void handle_create_child() {
  int temp, parentPID;
  int childPID = getpid();
  if ((temp = fork()) != 0)
    return; // si es el padre se vuelve
  printf("Nuevo hijo!\n");

  push_child(childPID);

  // repetir esto cada 5 segundos
  while (1) {
    parentPID = getppid();
    if (parentPID == 1) // porque cuando el padre no existe el PID se vuelve 1
      break;
    printf("PID padre: %d \nPID hijo: %d\n", parentPID, childPID);
    sleep(CHILD_REPEAT_MSG_DELAY_SEC);
  }
}

void push_child(int pid) {
  childrenStack.PIDs[childrenStack.index] = pid;
  childrenStack.index++;
}

int pop_child() {
  int pid = childrenStack.PIDs[childrenStack.index-1];
  childrenStack.index--;
  kill(pid, SIGTERM);
  return pid;
}

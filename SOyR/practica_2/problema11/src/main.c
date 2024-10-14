#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/definitions.h"

#define IPC_RESULT_ERROR (-1)

#define DEBUG

// esta es la información que voy a cifrar y luego decifrar
// const char MY_DATA[10] = {'h', 'o', 'l', 'a', 'm', 'u', 'n', 'd', 'o', 'o'};
const int MY_DATA_A[10] = {7, 14, 11, 0, 12, 20, 13, 3, 14, 14};
const int MY_DATA_B[10] = {7, 14, 11, 0, 0, 12, 20, 13, 3, 14};
// IMPORTANTE: como se piensan que estos números (del 0 al 26) son letras, hay
// que hacer un offset the 97 para que coincidan con los ASCII

int *MY_ARRAY;

int main(int argc, char *args[]) {
  assert(argc == 2);

  if (strcmp(args[1], PROGRAM_A) == 0) {
    // printf("Programa A\n");

    // se registran las señales
    signal(SIGTERM, handle_termination);
    signal(SIGUSR1, handle_write_read_a);

    setup_shared_memory();

    save_pid_to_shared_mem(PROGRAM_A_PID_OFFSET);

    sleep(2);
#ifdef DEBUG
    printf("autoenvío señal\n");
#endif /* ifdef DEBUG */
    kill(getpid(), SIGUSR1);

    while (1) {
    }

  } else if (strcmp(args[1], PROGRAM_B) == 0) {
    // printf("Programa B\n");

    // se registran las señales
    signal(SIGUSR1, handle_write_read_b);

    setup_shared_memory();

    save_pid_to_shared_mem(PROGRAM_B_PID_OFFSET);

    while (1) {
    }

  } else {
    fprintf(stderr, "ERROR: Argumento erróneo\n");
    exit(1);
  }

  return 0;
}

void handle_termination() {
  kill(get_pid_from_shared_mem(PROGRAM_B_PID_OFFSET), SIGTERM);
  printf("Se terminará el proceso A\n");

  detach_memory_block(MY_ARRAY);
  destroy_memory_block(SHARED_MEMORY_PATH);

  exit(0);
}

void setup_shared_memory() {
  MY_ARRAY =
      attach_memory_block(SHARED_MEMORY_PATH, sizeof(int) * (ARRAY_LENGTH + 2));
  if (MY_ARRAY == NULL) {
    printf("ERROR: no se pudo crear el bloque de memoria\n");
    exit(1);
  }
}

void handle_write_read_a() {
  int i;

#ifdef DEBUG
  printf("PID '%i' (proceso A) está por escribir y leer el bloque de memoria\n",
         getpid());
  printf("Escribiendo bloque...\n");
#endif /* ifdef DEBUG */
  for (i = 0; i < ARRAY_LENGTH / 2; i++) {
    sleep(1);
    MY_ARRAY[i] = cypher(MY_DATA_A[i]);
  }

  printf("El proceso A (PID: %i) está por leer...\n", getpid());
  for (i = ARRAY_LENGTH / 2; i < ARRAY_LENGTH - 1; i++) {
    printf("%i, ", decypher(MY_ARRAY[i]));
  }
  printf("%i \n", decypher(MY_ARRAY[ARRAY_LENGTH - 1]));

#ifdef DEBUG
  printf("Leyendo como caracteres...\n");
  for (i = ARRAY_LENGTH / 2; i < ARRAY_LENGTH - 1; i++) {
    printf("%c, ", decypher(MY_ARRAY[i])+97);
  }
  printf("%c \n", decypher(MY_ARRAY[ARRAY_LENGTH - 1])+97);
#endif /* ifdef DEBUG */

  kill(get_pid_from_shared_mem(PROGRAM_B_PID_OFFSET), SIGUSR1);
}

void handle_write_read_b() {
  int i;

#ifdef DEBUG
  printf("PID '%i' (proceso B) está por escribir y leer el bloque de memoria\n",
         getpid());
  printf("Escribiendo bloque: \n");
#endif /* ifdef DEBUG */
  for (i = ARRAY_LENGTH / 2; i < ARRAY_LENGTH; i++) {
    sleep(1);
    MY_ARRAY[i] = cypher(MY_DATA_B[i - 10]);
  }

  printf("El proceso B (PID: %i) está por leer...\n", getpid());
  for (i = 0; i < ARRAY_LENGTH / 2 - 1; i++) {
    printf("%i, ", decypher(MY_ARRAY[i]));
  }
  printf("%i \n", decypher(MY_ARRAY[(ARRAY_LENGTH / 2) - 1]));

#ifdef DEBUG
  printf("Leyendo como caracteres...\n");
  for (i = 0; i < ARRAY_LENGTH / 2 - 1; i++) {
    printf("%c, ", decypher(MY_ARRAY[i])+97);
  }
  printf("%c \n", decypher(MY_ARRAY[(ARRAY_LENGTH / 2) - 1])+97);
#endif /* ifdef DEBUG */

  kill(get_pid_from_shared_mem(PROGRAM_A_PID_OFFSET), SIGUSR1);
}

int get_shared_block(char *filename, int size) {
  key_t key;

  // pido una llave para el bloque de memoria
  // se asocia a un nombre en común para que el
  // otro proceso pueda acceder también
  key = ftok(filename, 0);
  if (key == IPC_RESULT_ERROR) {
    return IPC_RESULT_ERROR;
  }

  // si el bloque de memoria no existe, se crea
  return shmget(key, size, 0666 | IPC_CREAT);
}

int *attach_memory_block(char *filename, int size) {
  int shared_block_id = get_shared_block(filename, size);
  int *result;

  if (shared_block_id == IPC_RESULT_ERROR) {
    return NULL;
  }

  // se hace el mapeo de memoria y se obtiene un
  // puntero a este bloque de memoria
  result = shmat(shared_block_id, NULL, 0);
  if (result == (int *)IPC_RESULT_ERROR) {
    return NULL;
  }

  return result;
}

bool detach_memory_block(int *block) {
  return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char *filename) {
  int shared_block_id = get_shared_block(filename, 0);

  if (shared_block_id == IPC_RESULT_ERROR) {
    return NULL;
  }

  return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}

void save_pid_to_shared_mem(char offset) {
  MY_ARRAY[ARRAY_LENGTH + offset] = getpid();
}

int get_pid_from_shared_mem(char offset) {
  return MY_ARRAY[ARRAY_LENGTH + offset];
}

int cypher(int x) { return (4 * x + 5) % 27; }

int decypher(int x) { return (7 * x + 19) % 27; }

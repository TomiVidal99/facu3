#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include "../include/definitions.h"

// esta es la información que voy a cifrar y luego decifrar
// const char MY_DATA[10] = {'h', 'o', 'l', 'a', 'm', 'u', 'n', 'd', 'o', 'o'};
const int MY_DATA_A[10] = {7, 14, 11, 0, 12, 20, 13, 3, 14, 14};
const int MY_DATA_B[10] = {7, 14, 11, 0, 0, 12, 20, 13, 3, 14};
// IMPORTANTE: como se piensan que estos números (del 0 al 26) son letras, hay
// que hacer un offset the 97 para que coincidan con los ASCII

pthread_t thread_a, thread_b;
int myArray[MY_ARRAY_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
pthread_mutex_t mutexLock;
pthread_cond_t cond_a, cond_b;
bool is_terminated = false;

int main(void)
{

  // IMPORTANTE:
  // leer notas de por qué no incluí la parte de 'programa a' | 'programa b'

  // inicializo el mutex
  if (pthread_mutex_init(&mutexLock, NULL) != 0)
  {
    fprintf(stderr, "No se pudo inicializar el mutex\n");
    return 1;
  }

  // registro el manjedor de SIGTERM
  signal(SIGTERM, handle_termination);

  pthread_cond_init(&cond_a, NULL);
  pthread_cond_init(&cond_b, NULL);

  // creo los hilos A y B
  pthread_create(&thread_a, NULL, (void *)&handle_thread_a, NULL);
  pthread_create(&thread_b, NULL, (void *)&handle_thread_b, NULL);

  pthread_join(thread_a, NULL);
  pthread_join(thread_b, NULL);

  pthread_mutex_destroy(&mutexLock);
  pthread_cond_destroy(&cond_a);
  pthread_cond_destroy(&cond_b);

  printf("\n\nPrograma terminado correctamente...\n");
  return 0;
}

void handle_thread_a()
{

  while (!is_terminated)
  {
    pthread_mutex_lock(&mutexLock);

    printf("Hilo A trabajando...\n");

    write_first_segment();
    read_last_segment();
    pthread_cond_signal(&cond_b);
    pthread_cond_wait(&cond_a, &mutexLock);

    pthread_mutex_unlock(&mutexLock);
  }
}

void handle_thread_b()
{
  while (!is_terminated)
  {
    pthread_mutex_lock(&mutexLock);

    printf("Hilo B trabajando...\n");

    write_last_segment();
    read_first_segment();
    pthread_cond_signal(&cond_a);
    pthread_cond_wait(&cond_b, &mutexLock);

    pthread_mutex_unlock(&mutexLock);
  }
}

void handle_termination()
{
  is_terminated = true;
  pthread_cond_signal(&cond_a);
  pthread_cond_signal(&cond_b);
}

void write_first_segment(void)
{
  int i;
  for (i = 0; i < MY_ARRAY_LENGTH / 2; i++)
  {
    sleep(1);
    myArray[i] = cypher(MY_DATA_A[i]);
  }
}

void read_last_segment(void)
{
  int i;
  // printf("Hilo A está por leer...\n");
  for (i = MY_ARRAY_LENGTH / 2; i < MY_ARRAY_LENGTH - 1; i++)
  {
    printf("%i, ", decypher(myArray[i]));
  }
  printf("%i \n", decypher(myArray[MY_ARRAY_LENGTH - 1]));
}

void read_first_segment(void)
{
  int i;
  // printf("Hilo B está por leer...\n");
  for (i = 0; i < MY_ARRAY_LENGTH / 2 - 1; i++)
  {
    printf("%i, ", decypher(myArray[i]));
  }
  printf("%i \n", decypher(myArray[(MY_ARRAY_LENGTH / 2) - 1]));
}

void write_last_segment(void)
{
  int i;
  for (i = MY_ARRAY_LENGTH / 2; i < MY_ARRAY_LENGTH; i++)
  {
    sleep(1);
    myArray[i] = cypher(MY_DATA_B[i - 10]);
  }
}

int cypher(int x) { return (4 * x + 5) % 27; }

int decypher(int x) { return (7 * x + 19) % 27; }
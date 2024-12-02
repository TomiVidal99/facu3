#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "definitions_client.h"

#define TOTAL_NUMS 26    // Total numbers to receive
#define BUFFER_SIZE 1024 // Size for the buffer to store the "FIN" word

int main(int argc, char *argv[])
{
  int i, client_socket, bytes_received, encrypted_num, rec_nums[TOTAL_NUMS];
  uint16_t server_port;
  const char *server_ip;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];
  char byte;

  // Inicializar los números recibidos y el buffer
  memset(rec_nums, 0, sizeof(rec_nums));
  memset(buffer, 0, sizeof(buffer));

  // Validar argumentos
  if (argc != 3)
  {
    fprintf(stderr, "Uso: %s <IP del servidor> <puerto>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = (uint16_t)atoi(argv[2]);

  // Crear socket
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0)
  {
    perror("Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  // Configurar dirección del servidor
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0)
  {
    perror("Dirección IP no válida");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  // Conectar al servidor
  if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("Error al conectar con el servidor");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  printf("Conectado al servidor %s:%d\n", server_ip, server_port);

  // Recibir los 26 números descifrados del servidor
  for (i = 0; i < TOTAL_NUMS; i++)
  {
    encrypted_num = 0;
    bytes_received = recv(client_socket, &encrypted_num, sizeof(encrypted_num), 0);
    if (bytes_received <= 0)
    {
      perror("Error al recibir un número o conexión cerrada");
      close(client_socket);
      exit(EXIT_FAILURE);
    }
    rec_nums[i] = encrypted_num;
  }

  // Ahora recibir la palabra "FIN"
  i = 0;
  while (1)
  {
    byte = '\0';
    bytes_received = recv(client_socket, &byte, sizeof(byte), 0);
    if (bytes_received <= 0)
    {
      perror("Error al recibir FIN o conexión cerrada");
      close(client_socket);
      exit(EXIT_FAILURE);
    }

    // Debug: Mostrar byte recibido
    printf("Byte recibido: '%c' (ASCII: %d)\n", byte, byte);

    if (byte == '\0')
    {
      break;
    }
    if (i < BUFFER_SIZE - 1)
    {
      buffer[i++] = byte;
    }
  }
  buffer[i] = '\0'; // Asegurar terminador nulo

  printf("Números recibidos:\n");
  for (i = 0; i < TOTAL_NUMS; i++)
  {
    printf("%d%c", rec_nums[i], (i < TOTAL_NUMS - 1) ? ',' : '\n');
  }

  printf("Números descifrados recibidos:\n");
  for (i = 0; i < TOTAL_NUMS; i++)
  {
    rec_nums[i] = decipher(rec_nums[i]);
    printf("%d%c", rec_nums[i], (i < TOTAL_NUMS - 1) ? ',' : '\n');
  }

  printf("Mensaje recibido: '%s'\n", buffer);

  // Verificar si el mensaje es "FIN"
  if (strcmp(buffer, END_WORD) == 0)
  {
    printf("El programa se terminó correctamente! :)\n");
    if (send(client_socket, END_WORD, strlen(END_WORD) + 1, 0) < 0)
    {
      fprintf(stderr, "Error enviar eco de FIN");
      close(client_socket);
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    fprintf(stderr, "Se esperaba recibir el mensaje 'FIN'. Pero no se obtuvo\n");
  }

  close(client_socket);
  exit(EXIT_SUCCESS);
}

int decipher(int x) { return (7 * x + 19) % 27; }
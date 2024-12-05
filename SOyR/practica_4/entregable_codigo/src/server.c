#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#include "definitions_server.h"

// #define DEBUG

int server_socket, client_socket;

int main()
{
    int i, pub_key_a, pub_key_b;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int num_to_send, num_encrypted;

    signal(SIGTERM, handle_termination);

    // Crear socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        fprintf(stderr, "No se pudo crear el socket\n");
        exit(EXIT_FAILURE);
    }

    // Configurar direccion del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
#ifdef DEFAULT_ADDR
    server_addr.sin_addr.s_addr = inet_addr(DEFAULT_ADDR);
#else
    server_addr.sin_addr.s_addr = INADDR_ANY;
#endif

    // Bindear el socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        fprintf(stderr, "No se pudo juntar el socket\n");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(server_socket, 5) < 0)
    {
        fprintf(stderr, "Escuchar conexiones falló\n");
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    printf("Esperando conexión del cliente (%d)...\n", PORT);
#endif

    // Aceptar al cliente
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0)
    {
        fprintf(stderr, "Falló la conexión con el cliente\n");
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    printf("Cliente conectado.\n");
    printf("Esperando clave pública...\n");
#endif

    // Recibir clave pública A
    if (recv(client_socket, &pub_key_a, sizeof(pub_key_a), 0) <= 0)
    {
        fprintf(stderr, "Error al recibir la clave pública A\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    pub_key_a = ntohl(pub_key_a);

    // Recibir clave pública B
    if (recv(client_socket, &pub_key_b, sizeof(pub_key_b), 0) <= 0)
    {
        fprintf(stderr, "Error al recibir la clave pública B\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    pub_key_b = ntohl(pub_key_b);

#ifdef DEBUG
    printf("Claves públicas: (A: %d, B: %d)\n", pub_key_a, pub_key_b);
#endif

#ifdef DEBUG
    for (i = 0; i < TOTAL_NUMS; i++)
    {
        if (i < TOTAL_NUMS - 1)
        {
            printf("%d, ", i + 1);
        }
        else
        {
            printf("%d\n", i + 1);
        }
    }
#endif

#ifdef DEBUG
    printf("Enviando encriptados\n");
#endif

    // Enviar numeros encriptados
    for (i = 0; i < TOTAL_NUMS; i++)
    {
        num_to_send = i + 1;

        num_encrypted = encrypt(num_to_send, pub_key_a, pub_key_b);

#ifdef DEBUG
        if (i < TOTAL_NUMS - 1)
        {
            printf("%d, ", num_encrypted);
        }
        else
        {
            printf("%d\n", num_encrypted);
        }
#endif

        if (send(client_socket, &num_encrypted, sizeof(num_encrypted), 0) < 0)
        {
            fprintf(stderr, "Enviar falló\n");
            close(client_socket);
            close(server_socket);
            exit(EXIT_FAILURE);
        }
    }

    handle_termination();
    return 0;
}

int encrypt(int x, int key_a, int key_b) { return (key_a * x + key_b) % 27; }

void handle_termination()
{
    close(client_socket);
    close(server_socket);
}
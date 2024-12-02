#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "definitions_server.h"

#define DEBUG

int main()
{
    int i, server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int num_to_send, num_encrypted;

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
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Juntar el socket
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

    printf("Esperando conexión del cliente (%d)...\n", PORT);

    // Aceptar al cliente
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0)
    {
        fprintf(stderr, "Falló la conexión con el cliente\n");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado.\n");

    // Enviar clave pública??

#ifdef DEBUG
    for (i = 0; i <= TOTAL_NUMS; i++)
    {
        if (i < TOTAL_NUMS)
        {
            printf("%d, ", i);
        }
        else
        {
            printf("%d\n", i);
        }
    }
#endif

    printf("Enviando encriptados\n\n");

    // Enviar numeros encriptados
    for (i = 0; i < TOTAL_NUMS; i++)
    {
        num_to_send = i + 1;

        num_encrypted = encrypt(num_to_send);

#ifdef DEBUG
        if (i < TOTAL_NUMS)
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

    if (send(client_socket, END_WORD, strlen(END_WORD) + 1, 0) < 0)
    {
        fprintf(stderr, "Error al enviar FIN");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Cerrar conexiones y limpiar memoria
    close(client_socket);
    close(server_socket);
    return 0;
}

int encrypt(int x) { return (4 * x + 5) % 27; }
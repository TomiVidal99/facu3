// #define DEFAULT_ADDR "127.0.0.0"
#define PORT 8080

#define TOTAL_NUMS 26

// se encarga de terminar correctamente el servidor
// si el usuario termina el programa cuando corre
void handle_termination();

// se encarga de encriptar la info
int encrypt(int x, int key_a, int key_b);
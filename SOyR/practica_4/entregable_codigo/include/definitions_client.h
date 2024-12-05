#define PUB_KEY_A ((int)4)
#define PUB_KEY_B ((int)5)
#define PRIV_KEY_A ((int)7)
#define PRIV_KEY_B ((int)19)

// se encarga de terminar correctamente el servidor
// si el usuario termina el programa cuando corre
void handle_termination();

// Se encargar de la decriptación de los datos
int decipher(int x);
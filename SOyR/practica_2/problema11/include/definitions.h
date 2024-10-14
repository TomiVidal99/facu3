#define SHARED_MEMORY_NUMER 0
#define SHARED_MEMORY_PATH "/tmp"
#define PROGRAM_A "programa a"
#define PROGRAM_B "programa b"
#define ARRAY_LENGTH 20

#define PROGRAM_A_PID_OFFSET 1
#define PROGRAM_B_PID_OFFSET 2

/**
 * Se encarga de terminar el proceso A y B
 */
void handle_termination();

/**
 * Escribe y lee los segmentos correspondientes
 * al proceso A
 */
void handle_write_read_a();

/**
 * Escribe y lee los segmentos correspondientes
 * al proceso B
 */
void handle_write_read_b();

int cypher(int x);
int decypher(int x);

void save_pid_to_shared_mem(char offset);
int get_pid_from_shared_mem(char offset);
void setup_shared_memory();

int get_shared_block(char *filename, int size);
int *attach_memory_block(char *filename, int size);
bool destroy_memory_block(char *filename);
bool detach_memory_block(int *block);

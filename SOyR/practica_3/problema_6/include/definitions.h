#define CHILD_REPEAT_MSG_DELAY_SEC 5
#define MAX_CHILDREN_STACK 100 // TODO: tendría que hacer un array dinámico
#define CHILDREN_WAIT_RATE_SEC 1

void handle_create_child_1(); // handler que crea el hijo cuando llega SIGUSR1
void handle_create_child_2(); // handler que crea el hijo cuando llega SIGUSR2
void handle_terminate_child();
void push_child(int);
int pop_child();

typedef struct {
  int PIDs[MAX_CHILDREN_STACK];
  int count;
} PIDStack;

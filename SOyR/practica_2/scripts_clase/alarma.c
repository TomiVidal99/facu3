#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void trapper (int i)
{
	printf("recibi señal %d\n", i);
	return;
}

int main(void)
{
unsigned int tiempo;
signal (SIGALRM,trapper);
printf("mi PID es %d",getpid());
printf("cuantos segundos queres esperar?\n");
scanf("%u",&tiempo);
printf("A partir de ahora voy a esperar %u segundos\n",tiempo);
alarm(tiempo);
pause();
printf("ya pasaron  %u segundos\n",tiempo);
printf("Ahora voy a usar sleep(%u) \n",tiempo);
sleep(tiempo);
printf("ya pasaron  %u segundos medidos con sleep() \n",tiempo);


return 0;
}

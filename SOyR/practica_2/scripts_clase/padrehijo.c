#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
	{
	pid_t var;
	int status;
	int salir=0;
	printf("soy el padre y mi PID es %d \n",getpid());
	do
		{

		if ((var=fork())==0)
			{
			int x;
			printf( "\tsoy el hijo y fork me devolvio %d\n", var);
			printf("\tMi PID es %d \n",getpid());
			printf("\tEl PID de mi Padre es %d \n",getppid());
			printf("\tintroduzca un numero:");
			scanf("%d",&x);
			return x;
			}
		else
			{
			printf("soy el padre y fork me devolvio el pid de mi hijo %d \n",var);
			printf("Espero un tiempo a ver que sucede\n\n\n");
			printf( "Si no termino el hijo, espero que termine \n\n");
			waitpid(var,&status,0);
			printf("El hijo termino con status %d\n\n", status);
			printf("Para terminar ingrese 1, para seguir cualquier otro número\n");
			scanf("%d",&salir);
			if (salir!=1)
			  {salir=0;}
      }

		}while (salir==0);
	return 0;
	}


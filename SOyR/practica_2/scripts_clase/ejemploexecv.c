#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Comandos tipo Exec*/

//       extern char **environ;

//       int execl(const char *path, const char *arg, ... (char  *) NULL );
//       int execlp(const char *file, const char *arg, ... (char  *) NULL );
//       int execle(const char *path, const char *arg, ..., (char *) NULL, char * const envp[] );
//       int execv(const char *path, char *const argv[]);
//       int execvp(const char *file, char *const argv[]);
//       int execvpe(const char *file, char *const argv[],char *const envp[]);



int main(int argc, char *argv[])
	{
	pid_t var;
	int status;
	int salir=1;
    char programa[]="/bin/ls";
    char *args[]={"/bin/ls","-l", "--color",NULL};
 	printf("soy el padre y mi PID es %d \n",getpid());
	do
		{
		
		if ((var=fork())==0)
			{
			printf( "soy el hijo y fork me devolvio %d\n", var);
			printf("Mi PID es %d \n",getpid());
			printf( "ahora voy a ejecutar el comando '%s %s %s %s'\n", programa,args[0], args[1], args[2]);
			execv( programa,args);
			}
		else
			{
			printf("soy el padre y fork me devolvio el pid de mi hijo %d \n",var);
				printf( "Si no termino el hijo, espero que termine \n\n");
			waitpid(var,&status,0);
			printf("El hijo termino con status %d\n Comienzo de nuevo\n\n\n", status);
			printf("ingrese 0 para salir: ");
			scanf("%d",&salir);
			}
		}while (salir!=0);
	return 0;
	}




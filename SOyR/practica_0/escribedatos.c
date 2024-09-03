#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
  struct _datos {
  		 char nyap[60];
  		 unsigned id;
  		 char email[40];
  		 } dummy;
  char nomarch[255];
  char linea [200];
  unsigned cant_reg=0;
  int salir=0;

  FILE *pf;
  
  if (argc!=2)
   {
   printf( "modo de uso: escribedatos nombre_de_archivo\n");
   return 0;
   }
  strcpy(nomarch,argv[1]);
  pf=fopen(nomarch,"wb");

  if (pf==NULL)
   {
   printf( "error en la apertura de archivo %s\n",nomarch);
   return 0;
   }
  cant_reg=0; 
  salir=0;
  do 
  	 {
	 	 printf("Ingrese Nombre y apellido, para terminar ingrese una linea vacía\n");
	 	 fgets(linea,59,stdin);
	 	 linea[strlen(linea)-1]=0;
	 	 if (strlen(linea)!=0)
	 	    {
	 	    strncpy (dummy.nyap,linea,59);
	 	    printf("Ingrese e-mail\n");
	 	    fgets(linea,39,stdin);
        linea[strlen(linea)-1]=0;
	 	    strncpy (dummy.email,linea,39);
	 	    cant_reg++;
        dummy.id=cant_reg;
        fwrite(&dummy, sizeof(dummy), 1,pf);
	 	    }
 	    else
	 	    {  
	 	    salir =1;
	 	    }
    
	 }while(!salir);
					
  fclose(pf);
  return 0;
}

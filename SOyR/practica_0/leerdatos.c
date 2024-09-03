#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
  struct _datos
  {
    char nyap[60];
    unsigned id;
    char email[40];
  } dummy;
  char nomarch[255];
  unsigned cant_reg = 0;
  size_t it = 0;
  FILE *pf;

  if (argc != 2)
  {
    printf("modo de uso: leerdato nombre_de_archivo\n");
    return 0;
  }
  strncpy(nomarch, argv[1], 255);
  pf = fopen(nomarch, "rb");

  if (pf == NULL)
  {
    printf("error en la apertura de archivo %s\n", nomarch);
    return 0;
  }
  cant_reg = 0;
  do
  {
    it = fread(&dummy, sizeof(struct _datos), 1, pf);
    if (it == 1)
    {
      cant_reg++;
      printf("%s,%u,%s\n", dummy.nyap, dummy.id, dummy.email);
    }
  } while (!feof(pf));
  if (cant_reg == 0)
  {
    printf("El archivo %s  no contiene datos\n", nomarch);
  }
  fclose(pf);
  return 0;
}

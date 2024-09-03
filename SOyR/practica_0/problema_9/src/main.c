#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_FILEPATH "datos.bin"
#define CSV_FILEPATH "datos.csv"

// FUNCIONES
void load_data_to_mem(void);
void print_data(void);
struct tm *get_formatted_date(uint32_t);
void free_data(void);
void create_csv(void);

// VARIABLES GLOBALES
uint32_t *id;
uint16_t *pressure;
int16_t *temp;
uint16_t *precep;
uint8_t *humidity;
uint32_t *date;

typedef struct {
  uint32_t id;
  uint16_t pressure;
  int16_t temp;
  uint16_t precep;
  uint8_t humidity;
  uint32_t date;
} Data;

size_t dataLength;

int main(void) {

  load_data_to_mem();
  // print_data();
  create_csv();
  free_data();

  printf("\n\nPrograma finalizado exitosamente...\n");

  return 0;
}

/*
    Cargo los datos del archivo binario
    a arrays en memoria para cada campo
*/
void load_data_to_mem(void) {
  FILE *file = fopen(DATA_FILEPATH, "rb");
  if (!file) {
    printf("ERROR: no se pudo abrir el archivo '%s' \n", DATA_FILEPATH);
    exit(1);
  }
  if (fseek(file, 0L, SEEK_END) != 0) {
    printf("ERROR: no se puedo encontrar el final del archivo '%s' \n",
           DATA_FILEPATH);
    fclose(file);
    exit(1);
  }

  long filesize = ftell(file);
  if (filesize == -1) {
    printf("ERROR: no se pudo determinar el tamaño del archivo '%s'\n",
           DATA_FILEPATH);
    fclose(file);
    exit(1);
  }

  rewind(file);

  // printf("Size of '%s': %ld bytes \n", DATA_FILEPATH, filesize);

  dataLength = filesize / sizeof(Data);
  // printf("dataLength: %zu\n", dataLength);

  // alojar memoria para los arrays
  id = (uint32_t *)malloc(dataLength * sizeof(uint32_t));
  pressure = (uint16_t *)malloc(dataLength * sizeof(uint16_t));
  temp = (int16_t *)malloc(dataLength * sizeof(uint16_t));
  precep = (uint16_t *)malloc(dataLength * sizeof(uint16_t));
  humidity = (uint8_t *)malloc(dataLength * sizeof(uint8_t));
  date = (uint32_t *)malloc(dataLength * sizeof(uint32_t));

  if (!id || !pressure || !temp || !precep || !humidity || !date) {
    printf("ERROR: no se pudo asignar memoria para los datos.\n");
    fclose(file);
    exit(1);
  }

  // llenar el buffer temporal
  Data *buffer = (Data *)malloc(dataLength * sizeof(Data));
  if (!buffer) {
    printf("ERROR: no se pudo asignar memoria temporal.\n");
    fclose(file);
    exit(1);
  }

  size_t itemsRead = fread(buffer, sizeof(Data), dataLength, file);
  if (itemsRead != dataLength) {
    printf("ERROR: no se pudieron leer los datos correctamente desde el "
           "archivo '%s'.\n",
           DATA_FILEPATH);
    free(buffer);
    fclose(file);
    exit(1);
  }
  fclose(file);

  // lleno los arrays con la data del archivo binario
  for (size_t i = 0; i < dataLength; i++) {
    id[i] = buffer[i].id;
    pressure[i] = buffer[i].pressure;
    temp[i] = buffer[i].temp;
    precep[i] = buffer[i].precep;
    humidity[i] = buffer[i].humidity;
    date[i] = buffer[i].date;
  }

  free(buffer); // liberar el buffer temporal
}

/*
 * Imprime en pantalla con buen formato
 * la información cargada en memoria de los
 * datos binarios dados
 */
void print_data(void) {
  struct tm *actual_tm = {0};
  char formatted_date[100] = ""; // deberia setear el tamaño dinamicamente??
  for (size_t i = 0; i < dataLength; i++) {
    actual_tm = get_formatted_date(date[i]);
    if (!actual_tm) {
      continue;
    }

    sprintf(formatted_date, "%04d-%02d-%02d %02d:%02d:%02d UTC",
            actual_tm->tm_year + 1900, actual_tm->tm_mon + 1,
            actual_tm->tm_mday, actual_tm->tm_hour, actual_tm->tm_min,
            actual_tm->tm_sec);

    printf("i:%zu \t id:%d \t date:%s \t temp:%d \t precep:%d \t humidity:%d "
           "\t pressure:%d\n\n",
           i + 1, id[i], formatted_date, temp[i], precep[i], humidity[i],
           pressure[i]);
  }
}

/**
 * Retorno la fecha formateada corrrectamente,
 * correspondiente a la fecha leida en los datos
 */
struct tm *get_formatted_date(uint32_t elapsed_seconds) {
  // Definicion de la referencia
  struct tm epoch = {0};
  struct tm *actual_tm = {0};
  epoch.tm_year = 2000 - 1900; // desde el año 1900
  epoch.tm_mon = 0;            // Enero
  epoch.tm_mday = 1;           // dia 1

  time_t epoch_time = mktime(&epoch);
  if (epoch_time == -1) {
    printf("ERROR: No se pudo calcular la hora de referencia.\n");
    return actual_tm;
  }

  // Calcular el tiempo transcurrido
  time_t actual_time = epoch_time + elapsed_seconds;
  actual_tm = gmtime(&actual_time);

  return actual_tm;
}

void free_data(void) {
  free(id);
  free(pressure);
  free(temp);
  free(precep);
  free(humidity);
  free(date);
}

/**
 * Se crea un archivo CSV a partir de 'data'
 */
void create_csv(void) {
  char str[300];
  size_t i;
  FILE *csv_file = fopen(CSV_FILEPATH, "w");
  struct tm *fmtd_date = {0};
  if (!csv_file) {
    printf("ERROR: no se pudo abrir el archivo '%s' \n", CSV_FILEPATH);
    exit(1);
  }

  for (i = 0; i < dataLength; i++) {
    fmtd_date = get_formatted_date(date[i]);
    sprintf(str, "%d,%02d/%02d/%d,%d:%d:%d,%.1f,%.1f,%.1f,%d\n", id[i],
            fmtd_date->tm_mday, fmtd_date->tm_mon, fmtd_date->tm_year % 100,
            fmtd_date->tm_hour, fmtd_date->tm_min, fmtd_date->tm_sec,
            (float)temp[i] / 10.0, (float)pressure[i] / 10.0, (float)precep[i] / 10.0,
            humidity[i]);
    fwrite(str, sizeof(char), strlen(str), csv_file);
  }

  fclose(csv_file);
}

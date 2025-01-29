#include <stdint.h>

// - - - - - - - - - - -  FUNCIONES - - - - - - - - - - 
void init_adcs(); // se inicializan todos los ADCs
void init_timer1();
void read_adcs(); // se leen los 5 ADCs de las entradas 1 hasta la 5 (analog pins)
void set_pwm_duty_cycle(uint8_t);
void init_btn();
uint8_t read_btn();
void init_button_interrupt();
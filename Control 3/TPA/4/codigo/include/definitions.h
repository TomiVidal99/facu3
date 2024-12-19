#include <stdint.h>

// - - - - - - - - - - -  FUNCIONES - - - - - - - - - - 
void init_adc5(); // se inicializan todos los ADCs
void init_timer0();
void init_timer1();
void read_adc5(); // se leen los 5 ADCs de las entradas 1 hasta la 5 (analog pins)
void set_pwm_duty_cycle(uint8_t);
void init_btn();
uint8_t read_btn();

// Controlador MPC
void controller();
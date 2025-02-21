/*
 * main.c
 * TPA3
 *
 * Se implementa un controlador por PID
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdio.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "definitions.h"
#include "uart.h"
#include "PID.h"

// las y[0] y u[0] son las actuales
volatile float y[3] = {0};
volatile float u[3] = {0};
volatile float reference = 2.0f;
char *debug_output = "test\n\r";

int main(void)
{
  init_adc5();
  init_timer1();
  init_button_interrupt();
  USART_init();
  sei();

  set_pwm_duty_cycle(0);

  _delay_ms(100);

  while (1)
  {
  }
  return 0;
}

ISR(TIMER1_OVF_vect)
{
  float temp_ca = 0.0f;
  float current_output = 0.0f;

  // Lectura de la salida
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
  {
  };
  current_output = (float)(ADC * 5.0f / 1023.0f);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // CONTROL PID
  // temp_ca = gains_e[0] * (reference - current_output) + gains_e[1] * (reference - y[1]) + gains_e[2] * (reference - y[2]) - gains_u[0] * u[1] - gains_u[1] * u[2];
  temp_ca = 0.0f;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // limito la accion de control
  if (temp_ca > 5.0f)
  {
    temp_ca = 5.0f;
  }
  else if (temp_ca < 0.0f)
  {
    temp_ca = 0.0f;
  }

  uint8_t ca = (uint8_t)((temp_ca * 100.0f) / 5.0f);
  set_pwm_duty_cycle(ca);

  sprintf(debug_output, "y[0]=%d, temp_ca=%d, u=%d\n\r", (uint8_t)(current_output * 1000.0f), (uint8_t)(1000.0f * temp_ca), ca);
  USART_putstring(debug_output);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // actualizo las muestras pasadas
  y[2] = y[1];
  y[1] = current_output;
  y[0] = current_output;
  u[2] = u[1];
  u[1] = u[0];
  u[0] = temp_ca;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// Dispara una interrupción cada 10ms
void init_timer1()
{
  DDRB |= (1 << PB1);
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
  ICR1 = 2499;
  TIMSK1 = (1 << TOIE1);
}

void set_pwm_duty_cycle(uint8_t duty_cycle)
{
  if (duty_cycle > 100)
  {
    duty_cycle = 100;
  }

  OCR1A = (uint16_t)(((uint32_t)duty_cycle * (ICR1 + 1)) / 100);
}

void init_adc5()
{
  ADMUX = (1 << REFS0);
  ADMUX |= (1 << MUX2) | (1 << MUX0);
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);

  // se hace una lectura para finalizar el seteo del registro
  ADCSRA |= (1 << ADSC);
  while ((ADCSRA & (1 << ADSC)) != 0)
    ;
}

// habilita la interrupción de PD1 (boton en la placa)
void init_button_interrupt()
{
  DDRD &= ~(1 << PD3);
  PORTD |= (1 << PD3);
  EICRA |= (1 << ISC11);
  EICRA &= ~(1 << ISC10);
  EIMSK |= (1 << INT1);
}

// Cuando se presiona el botton
ISR(INT1_vect)
{
  _delay_ms(100);
  // if (!(PIND & (1 << PD3)))
  // {
  //   switch (reference)
  //   {
  //   case 1.0:
  //     reference = 2.0;
  //     break;
  //   default:
  //     reference = 1.0;
  //     break;
  //   }
  //   sprintf(debug_output, "button pressed\n\r");
  //   USART_putstring(debug_output);
  // }
}
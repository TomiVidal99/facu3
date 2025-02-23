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
// #include "uart.h"
#include "PID.h"

#define VREF_ADC 5.0f // tensión de referencia del ADC

// las y[0] y u[0] son las actuales
volatile float e[2] = {0};
volatile float u[2] = {0};
volatile float ref_prev = 0.0f;
volatile float ref_filtered_prev = 0.0f;
volatile float reference = 2.0f;
char *debug_output = "test\n\r";

int main(void)
{
  init_adc5();
  init_timer1();
  init_button_interrupt();
  // USART_init();
  sei();

  DDRB |= (1 << PB4);

  set_pwm_duty_cycle(0);

  _delay_ms(5);

  while (1)
  {
  }
  return 0;
}

// Dispara una interrupción cada 10ms
ISR(TIMER1_OVF_vect)
{
  float temp_ca = 0.0f;
  float current_output = 0.0f;
  float ref_filtered = 0.0f;

  // Lectura de la salida
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
  {
  };
  current_output = (ADC * VREF_ADC) / 1024.0f;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // calculo la referencia filtrada
  ref_filtered = gains_re[1] * ref_prev + gains_re[0] * reference - gains_rs * ref_filtered_prev;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // CONTROL PID
  temp_ca = gains_e[0] * (ref_filtered - current_output) + gains_e[1] * e[0] + gains_e[2] * e[1] - gains_u[0] * u[0] - gains_u[1] * u[1];
  // temp_ca = 0.0f;
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

  // sprintf(debug_output, "y[0]=%d, temp_ca=%d, u=%d\n\r", (uint16_t)(current_output * 1000.0f), (uint8_t)(1000.0f * temp_ca), ca);
  // USART_putstring(debug_output);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // actualizo las muestras pasadas
  e[1] = e[0];
  e[0] = reference - current_output;
  u[1] = u[0];
  u[0] = temp_ca;

  ref_prev = reference;
  ref_filtered_prev = ref_filtered;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  PORTB ^= (1 << PB4);
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
  ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // ADMUX = (1 << REFS0);
  // ADMUX |= (1 << MUX2) | (1 << MUX0);
  // ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);

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
  if (!(PIND & (1 << PD3)))
  {
    if (reference == 0.0f)
    {
      reference = 1.0f;
    }
    else if (reference == 2.0f)
    {
      reference = 3.5f;
    }
    else if (reference == 3.5f)
    {
      reference = 4.0f;
    }
    else
    {
      reference = 0.0f;
    }
  }
}
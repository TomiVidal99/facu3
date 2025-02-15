/*
 * main.c
 * TPA3
 *
 * Se implementa un controlador por MPC
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define ADC_INTERNAL_REFERENCE 1100

#include <stdio.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "definitions.h"
#include "uart.h"

// matrices de los datos
#include "weights.h"

#define STATES_NUM 7
#define ADC_NUMBERS 6

// volatile uint16_t timer0_counter = 0;
volatile uint32_t states[STATES_NUM] = {0};
volatile uint16_t control_action = 0;
char *debug_output = "test\n\r";
volatile uint16_t reference = 2500;

int main(void)
{
  init_adcs();
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
  int32_t temp_ca = 0;
  uint8_t u = 0;
  uint8_t temp_counter = 0;

  // Lectura de los estados
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  for (temp_counter = 0; temp_counter < ADC_NUMBERS; temp_counter++)
  {
    ADMUX = (ADMUX & 0xF0) | (temp_counter & 0x0F); // selecciono el ADC
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
    };
    if (temp_counter == 0)
    {
      states[1] = (uint16_t)(((4.88 * ADC) + 1));
    }
    else if (temp_counter == 1)
    {
      states[0] = (uint16_t)(((4.88 * ADC) + 1));
    }
    else
    {
      states[temp_counter] = (uint16_t)(((4.88 * ADC) + 1));
    }
  }
  states[6] = control_action;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // CONTROL MPC
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  temp_ca = control_action + (int32_t)(((double)Ky * (double)(reference)) - (int32_t)((Kmpc[0] * (double)states[0]) + (Kmpc[1] * (double)states[1]) + (Kmpc[2] * (double)states[2]) + (Kmpc[3] * (double)states[3]) + (Kmpc[4] * (double)states[4]) + (Kmpc[5] * (double)states[5]) + (Kmpc[6] * (double)states[6]))); // dU

  // limito la accion de control
  if (temp_ca > 5000)
  {
    temp_ca = 5000;
  }
  else if (temp_ca < 0)
  {
    temp_ca = 0;
  }

  u = (uint8_t)(((uint32_t)temp_ca * (uint32_t)100) / (uint32_t)5000);

  set_pwm_duty_cycle(u);

  // sprintf(debug_output, "U: %d%% \r\n\tStates->(%ld,%ld,%ld,%ld,%ld,%ld,%ld)\r\n\r\n",
  //         u,
  //         states[0],
  //         states[1],
  //         states[2],
  //         states[3],
  //         states[4],
  //         states[5],
  //         states[6]);
  // USART_putstring(debug_output);

  control_action = temp_ca;
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

void init_adcs()
{
  ADMUX = (1 << REFS0);
  // ADMUX |= (1 << MUX2) | (1 << MUX0);
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
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
  _delay_ms(50);
  if (!(PIND & (1 << PD3)))
  {
    switch (reference)
    {
    case 1000:
      reference = 2000;
      break;
    case 2000:
      reference = 3000;
      break;
    case 3000:
      reference = 4000;
      break;
    case 4000:
      reference = 5000;
      break;
    case 5000:
      reference = 1000;
      break;
    default:
      reference = 1000;
      break;
    }
    sprintf(debug_output, "-> Referencia (%d) \n\r", reference);
    USART_putstring(debug_output);
  }
}
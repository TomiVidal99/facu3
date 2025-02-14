/*
 * main.c
 * TPA3
 *
 * Se implementa un controlador por MPC
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

#define SCALE_TO_MILLI_VOLTS 4.88

volatile uint16_t system_output_mv = 0;
volatile uint16_t control_action_mv = 0;
volatile uint16_t reference_mv = 2000;
char *debug_output = "test\n\r";

int main(void)
{
  init_adc();
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
  uint16_t temp_ca = 0;

  // Lectura de la salida
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  ADMUX = (ADMUX & 0xF0) | (0 & 0x0F); // selecciono el ADC
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
  {
  };
  system_output_mv = (uint16_t)(((SCALE_TO_MILLI_VOLTS * ADC) + 1));
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // CONTROL PID
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  temp_ca = 0;

  // limito la accion de control
  if (temp_ca > 5000)
  {
    temp_ca = 5000;
  }
  else if (temp_ca < 0)
  {
    temp_ca = 0;
  }

  set_pwm_duty_cycle((uint8_t)(((uint32_t)temp_ca * (uint32_t)100) / (uint32_t)5000));

  control_action_mv = temp_ca;
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
    switch (reference_mv)
    {
    case 1000:
      reference_mv = 2000;
      break;
    case 2000:
      reference_mv = 3000;
      break;
    case 3000:
      reference_mv = 4000;
      break;
    case 4000:
      reference_mv = 5000;
      break;
    case 5000:
      reference_mv = 1000;
      break;
    default:
      reference_mv = 1000;
      break;
    }
    sprintf(debug_output, "button pressed\n\r");
    USART_putstring(debug_output);
  }
}
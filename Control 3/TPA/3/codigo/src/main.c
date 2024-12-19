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
#include "Kmpc.h"
#include "Ky.h"

#define STATES_NUM 7
#define ADC_NUMBERS 6

char *debug_output = "TEST\n";

volatile uint8_t timer0_counter = 0;
volatile uint8_t temp_counter = 0;

volatile uint16_t states[STATES_NUM] = {0, 0, 0, 0, 0, 0, 0};
volatile uint16_t reference = 1000;
volatile uint16_t control_action = 0;
volatile int32_t control_action_diff = 0;
volatile uint8_t btn_timeout = 0;

volatile uint32_t a = 0;

volatile uint16_t u = 0;

int main(void)
{
  init_adcs();
  init_timer1();
  init_timer0();
  init_btn();
  USART_init();
  sei();

  DDRB |= (1 << PB4);
  DDRB |= (1 << PB6);

  // set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Modo de bajo consumo: power-down

  set_pwm_duty_cycle(0);

  while (1)
  {
  }
  return 0;
}

void init_timer0()
{
  TCCR0A = (1 << WGM01); // CTC mode
  TCCR0B = (1 << CS01) | (1 << CS00);
  OCR0A = 249;
  TIMSK0 = (1 << OCIE0A);
}

void init_timer1()
{
  DDRB |= (1 << PB1);
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  ICR1 = 15999;

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

ISR(TIMER1_OVF_vect)
{
  if (btn_timeout > 0)
    btn_timeout--;

  // leo el boton para cambiar la referencia
  if (read_btn() == 1 && btn_timeout == 0)
  {
    if (reference == 1)
    {
      reference = 3;
    }
    else
    {
      reference = 1;
    }

    // sprintf(debug_output, "referencia: %ld\n\r", reference);
    // USART_putstring(debug_output);

    btn_timeout = 2;
  }

  read_adcs();
  control_MPC();

  // esta es una señal de referencia para saber cuando
  // se hace la interrupcion cada 1ms
  PORTB ^= (1 << PB6);

  // sprintf(debug_output, "MPC: %d\n\r", system_output_mv);
  // USART_putstring(debug_output);
}

void init_adcs()
{
  ADMUX = (1 << REFS0);
  // ADMUX |= (1 << MUX2) | (1 << MUX0);
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

void init_btn()
{
  DDRD &= ~(1 << DDD3);
  PORTD |= (1 << PORTD3);
}

// Return 1 a GND
// Return 0 a HIGH
uint8_t read_btn()
{
  return !(PIND & (1 << PIND3));
}

void read_adcs()
{

  for (temp_counter = 0; temp_counter < ADC_NUMBERS; temp_counter++)
  {
    ADMUX = (ADMUX & 0xF0) | (temp_counter & 0x0F); // selecciono el ADC
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
    };
    if (temp_counter == 0)
    {
      states[1] = (uint16_t)((4.88 * ADC) + 1);
    }
    else if (temp_counter == 1)
    {
      states[0] = (uint16_t)((4.88 * ADC) + 1);
    }
    else
    {
      if (temp_counter == 6)
      {
        USART_putstring("se lee el adc 6!!!\r\n");
      }
      else
      {
        states[temp_counter] = (uint16_t)((4.88 * ADC) + 1);
      }
    }
  }

  // TODO: esto debería ser así????
  // states[6] = control_action;
  states[6] = 0;
}

ISR(TIMER0_COMPA_vect)
{
  timer0_counter++;
  if (timer0_counter < 200)
  {
    return;
  }
  timer0_counter = 0;

  // sprintf(debug_output, "lectura: %d\n\r", system_output_mv);
  // USART_putstring(debug_output);
  PORTB ^= (1 << PB4);
}

void control_MPC()
{
  // for (temp_counter = 0; temp_counter < STATES_NUM; temp_counter++)
  // {
  //   control_action_diff += (Kmpc[0][temp_counter] * states[temp_counter]);
  // }
  // control_action_diff = Ky[0][0] * reference - control_action_diff;
  // control_action = control_action + control_action_diff;

  // u = (uint32_t)((control_action/50000));
  // set_pwm_duty_cycle(u);

  sprintf(debug_output, "estados: %d, %d, %d, %d, %d, %d, %d. CA: %ld\n\r", states[0], states[1], states[2], states[3], states[4], states[5], states[6], a);
  USART_putstring(debug_output);
}
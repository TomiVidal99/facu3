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

// volatile uint16_t timer0_counter = 0;
volatile float states[STATES_NUM] = {
    1690 / 1000.0,
    484 / 1000.0,
    98 / 1000.0,
    20 / 1000.0,
    5 / 1000.0,
    5 / 1000.0,
    3817 / 1000.0};
volatile float control_action = 0.0;
char *debug_output = "test\n\r";
volatile uint8_t reference = 1;

int main(void)
{

  init_adcs();
  init_timer1();
  // init_timer0();
  USART_init();
  sei();

  // uint8_t temp_counter = 0;
  // float temp_acc = 0.0;
  // float control_action_diff = 0.0;
  // float temp_ca = 0.0;

  // for (temp_counter = 0; temp_counter < STATES_NUM; temp_counter++)
  // {
  //   temp_acc += ((float)Kmpc[temp_counter] * (float)states[temp_counter]);
  // }
  // control_action_diff = (((float)Ky * (float)reference) - temp_acc); // dU
  // temp_ca += control_action_diff;                                    // U

  // temp_acc += 0.0766301 * (float)1690 / 1000.0;
  // temp_acc += -0.338912 * (float)484 / 1000.0;
  // temp_acc += 0.599917 * (float)98 / 1000.0;
  // temp_acc += -0.531259 * (float)20 / 1000.0;
  // temp_acc += 0.235353 * (float)5 / 1000.0;
  // temp_acc += -0.041726 * (float)5 / 1000.0;
  // temp_acc += 0.41106 * (float)3817 / 1000.0;

  // sprintf(debug_output, "acc: %d, diff: %d, temp_ca: %d\n\r",
  //         (uint16_t)(temp_acc * 1000.0),
  //         (uint16_t)(control_action_diff * 1000.0),
  //         (uint16_t)(temp_ca * 1000.0));
  // sprintf(debug_output, "a: %d, dU: %d, U: %d, acc: %d, DC: %d%% \r\n\tStates->(%d,%d,%d,%d,%d,%d,%d)\r\n\r\n",
  //         a,
  //         (uint16_t)(control_action_diff * 1000.0),
  //         (uint16_t)(temp_ca * 1000.0),
  //         (uint8_t)(temp_acc * 1000.0),
  //         (uint8_t)((temp_ca * 100.0) / (5.0)),
  //         (uint16_t)(1000.0 * states[0]),
  //         (uint16_t)(1000.0 * states[1]),
  //         (uint16_t)(1000.0 * states[2]),
  //         (uint16_t)(1000.0 * states[3]),
  //         (uint16_t)(1000.0 * states[4]),
  //         (uint16_t)(1000.0 * states[5]),
  //         (uint16_t)(1000.0 * states[6]));
  // USART_putstring(debug_output);

  set_pwm_duty_cycle(0);

  _delay_ms(100);

  while (1)
  {
  }
  return 0;
}

ISR(TIMER1_OVF_vect)
{
  float control_action_diff = 0.0;
  uint8_t temp_counter1 = 0;
  uint8_t temp_counter2 = 0;
  float temp_ca = 0.0;
  float temp_acc = 0.0;

  // Lectura de los estados
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  for (temp_counter1 = 0; temp_counter1 < ADC_NUMBERS; temp_counter1++)
  {
    ADMUX = (ADMUX & 0xF0) | (temp_counter1 & 0x0F); // selecciono el ADC
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
    };
    if (temp_counter1 == 0)
    {
      states[1] = (uint16_t)((5.0 * ADC) + 1) / 1024.0;
    }
    else if (temp_counter1 == 1)
    {
      states[0] = (uint16_t)((5.0 * ADC) + 1) / 1024.0;
    }
    else
    {
      states[temp_counter1] = (uint16_t)((5.0 * ADC) + 1) / 1024.0;
    }
  }
  states[6] = control_action;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // CONTROL MPC
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  for (temp_counter2 = 0; temp_counter2 < STATES_NUM; temp_counter2++)
  {
    sprintf(debug_output, "tc2: %d\n\r\tkmpc: %d\n\r\tstates: %d\n\r",
            temp_counter2,
            (uint16_t)(Kmpc[temp_counter2] * 1000.0),
            (uint16_t)(states[temp_counter2] * 1000.0));
    USART_putstring(debug_output);
    temp_acc = (float)((float)temp_acc + ((float)Kmpc[temp_counter2] * (float)states[temp_counter2]));
  }
  control_action_diff = (((float)Ky * (float)reference) - temp_acc); // dU
  temp_ca += control_action_diff;                                    // U

  // limito la accion de control
  if (temp_ca > 5.0)
  {
    temp_ca = 5.0;
  }
  else if (temp_ca < 0.0)
  {
    temp_ca = 0.0;
  }

  set_pwm_duty_cycle((temp_ca * 100.0) / 5.0);

  sprintf(debug_output, "dU: %d, U: %d, acc: %d, DC: %d%% \r\n\tStates->(%d,%d,%d,%d,%d,%d,%d)\r\n\r\n",
          (uint16_t)(control_action_diff * 1000.0),
          (uint16_t)(temp_ca * 1000.0),
          (uint8_t)(temp_acc * 1000.0),
          (uint8_t)((temp_ca * 100.0) / (5.0)),
          (uint16_t)(1000.0 * states[0]),
          (uint16_t)(1000.0 * states[1]),
          (uint16_t)(1000.0 * states[2]),
          (uint16_t)(1000.0 * states[3]),
          (uint16_t)(1000.0 * states[4]),
          (uint16_t)(1000.0 * states[5]),
          (uint16_t)(1000.0 * states[6]));
  USART_putstring(debug_output);

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

// ISR(TIMER0_COMPA_vect)
// {
//   // timer0_counter++;
//   // if (timer0_counter < 3000)
//   // {
//   //   return;
//   // }
//   // timer0_counter = 0;

//   // if (reference == 1)
//   // {
//   //   reference = 3;
//   // }
//   // else
//   // {
//   //   reference = 1;
//   // }

//   // sprintf(debug_output, "reference: %d\n\r", reference);
//   // USART_putstring(debug_output);

//   // PORTB ^= (1 << PB4);
// }

// void init_timer0()
// {
//   TCCR0A = (1 << WGM01); // CTC mode
//   TCCR0B = (1 << CS01) | (1 << CS00);
//   OCR0A = 249;
//   TIMSK0 = (1 << OCIE0A);
// }

// 1ms
// void init_timer1()
// {
//   DDRB |= (1 << PB1);
//   TCCR1A = (1 << COM1A1) | (1 << WGM11);
//   TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
//   ICR1 = 15999;

//   TIMSK1 = (1 << TOIE1);
// }

// 100ms
// void init_timer1()
// {
//   DDRB |= (1 << PB1);
//   TCCR1A = (1 << COM1A1) | (1 << WGM11);                            // Clear OC1A on compare match, Fast PWM
//   TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10); // Fast PWM, prescaler = 64
//   ICR1 = 24999;
//   TIMSK1 = (1 << TOIE1);
// }
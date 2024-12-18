#include <stdint.h>

#define NC 3  
#define NUM_STATES 7

float states[NUM_STATES] = {0};
int dU[NC] = {0};
float y = 0;

float reference = 1.0;

extern const float K_Phi_R[NC];
extern const float K_Phi_F[NUM_STATES];

// - - - - - - - - - - -  FUNCIONES - - - - - - - - - - 
void init_adc5();
void init_timer0();
void init_timer1();
void read_adc5();
void set_pwm_duty_cycle(uint8_t);

// Controlador MPC
void mpc_control_step(float reference, float *states);

// Multiplicación matricial
void mat_vec_mult(const float matrix[][NUM_STATES], const float vector[], float result[], int rows, int cols);

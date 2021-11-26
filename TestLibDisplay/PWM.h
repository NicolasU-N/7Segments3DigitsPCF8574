/*
 	PWM.h
 	PWM for timer 2 7812Hz 8 Bit and timer 1 7812Hz 16 Bit
 	Created: 09/04/2021 14:15:27
 	Author: Nicolas
*/
#ifndef PWM_H_
#define PWM_H_


#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif
void PWMInit();
void PWMOn();
void PWMOff();

void setDutyPWMPB1(int duty);
void setDutyPWMPB2(int duty);
void setDutyPWMPB3(int duty);
void setDutyPWMPD3(int duty);
#ifdef __cplusplus
}
#endif

#endif /* PWM_H_ */

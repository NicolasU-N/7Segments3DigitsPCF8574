/*
 	PWM.c
 	PWM for timer 2 7812Hz 8 Bit
 	PWM for timer 1 7812Hz 16 Bit
 	Created: 01/07/2021 11:45:37
 	Author: Nicolas
*/

#include "PWM.h"

void PWMInit()
{
  //Configuracion de pines salida
  DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
  DDRD |= (1 << DDD3);

  //Configuando timer 2
  //Operation Mode = Fast PWM
  TCCR2A |= (1 << WGM20); //1
  TCCR2A |= (1 << WGM21); //1

  //Configuando timer 1
  //Operation Mode = Fast PWM 8 Bit
  TCCR1A |= (1 << WGM10);	 //1
  TCCR1A &= ~(1 << WGM11); //0
  TCCR1B |= (1 << WGM12);	 //1
  TCCR1B &= ~(1 << WGM13); //0
}

void PWMOn()
{
  // Se inicializa contador timer 2 en 0
  TCNT2 = 0x0000;
  //N = 8  Prescaler Timer 2 7812.5FHz
  TCCR2B &= ~(1 << CS20); //0
  TCCR2B |= (1 << CS21);	//1
  TCCR2B &= ~(1 << CS22); //0

  // Se inicializa contador timer 1 en 0
  TCNT1H = 0x0000;
  TCNT1L = 0x0000;
  //N = 8  Prescaler Timer 1 7812.5FHz
  TCCR1B &= ~(1 << CS10); //0
  TCCR1B |= (1 << CS11);	//1
  TCCR1B &= ~(1 << CS12); //0
}

void PWMOff()
{
  //Clock setting T2 clock = 0 Hz
  TCCR2B &= ~(1 << CS20); //0
  TCCR2B &= ~(1 << CS21); //0
  TCCR2B &= ~(1 << CS22); //0

  //Clock setting T1 clock = 0 Hz
  TCCR1B &= ~(1 << CS10); //0
  TCCR1B |= (1 << CS11);	//1
  TCCR1B &= ~(1 << CS12); //0

}

/*
  @brief Función para generar PWM en el pin D9 0C1A
  @param duty
*/
void setDutyPWMPB1(int duty)
{

  TCCR1A &= ~(1 << COM1A0); //0 // Modo no invertido
  TCCR1A |= (1 << COM1A1);  //1

  OCR1A = duty;
}

/*
  @brief Función para generar PWM en el pin D10 OC1B
  @param tiempo
*/
void setDutyPWMPB2(int duty)
{
  TCCR1A &= ~(1 << COM1B0); //0
  TCCR1A |= (1 << COM1B1);  //1

  OCR1B = duty;
}

/*
  @brief Función para generar PWM en el pin D11 OC2A
  @param tiempo
*/
void setDutyPWMPB3(int duty)
{
  TCCR2A &= ~(1 << COM2A0); //0
  TCCR2A |= (1 << COM2A1);  //1

  OCR2A = duty;
}

/*
  @brief Función para generar PWM en el pin D3 0C2B
  @param duty
*/
void setDutyPWMPD3(int duty)
{

  TCCR2A &= ~(1 << COM2B0); //0 // Modo no invertido
  TCCR2A |= (1 << COM2B1);  //1

  OCR2B = duty;
}

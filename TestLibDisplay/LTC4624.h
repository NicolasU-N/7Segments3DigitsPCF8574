/** @file     LTC4624.h
    @brief    Dynamic lighting for the 3-digit 7-segment common anode LED display using pcf8574 multiplexer
    @Author   Nicolas
    Forked:   https://github.com/project37cat/7segment-library-PIC
    Created:  23/11/2021 12:32:10
*/

#ifndef LTC4624_h
#define LTC4624_h

#include "PCF8574.h"  // https://github.com/xreef/PCF8574_library
#include "PWM.h"

#define ADDR_PCF        0x20

#define SEG_H_PIN       P7
#define SEG_A_PIN       P0
#define SEG_B_PIN       P1
#define SEG_C_PIN       P2
#define SEG_D_PIN       P3
#define SEG_E_PIN       P4
#define SEG_F_PIN       P5
#define SEG_G_PIN       P6

#define BIT_IS_SET(reg, bit) ((reg>>bit)&1)
#define SET_BIT(reg, bit) (reg |= (1<<bit))
#define CLR_BIT(reg, bit) (reg &= (~(1<<bit)))

class LTC4624 {

  private:
    uint8_t dutyCycleLcd;

  public:
    void lcdInit();
    void setDutyCycleLcd(uint8_t val);
    uint8_t getDutyCycleLcd();
    //LTC4624();
    void lcdScan();
    void lcdChar(uint8_t pos, uint8_t sign);
    void lcdPrint(uint8_t pos, const char *str);
    void lcdDot(uint8_t pos, uint8_t dot);
    void lcdOff();
    void lcdClear();
};
#endif
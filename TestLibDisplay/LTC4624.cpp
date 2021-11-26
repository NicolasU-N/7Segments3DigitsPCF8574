#include "LTC4624.h"

// Set i2c address
PCF8574 pcf8574(ADDR_PCF); //&Wire,

typedef unsigned char uint8_t;

const uint8_t scode[] = //codes of symbols //segments: g-f-e-d-c-b-a-h(dot)
{
  0b01111110, //0     //0
  0b00001100, //1     //1
  0b10110110, //2     //2
  0b10011110, //3     //3
  0b11001100, //4     //4
  0b11011010, //5     //5
  0b11111010, //6     //6
  0b00001110, //7     //7
  0b11111110, //8     //8
  0b11011110, //9     //9
  0b00000000, //10    //space
  0b10000000, //11    //-
  0b11101110, //12    //A
  0b11111000, //13    //B
  0b01110010, //13    //C
  0b10111100, //15    //D
  0b11110010, //12    //E
  0b11100010, //17    //F
};

uint8_t sbuff[] =
{
  0x00,
  0x00,
  0x00
};


void LTC4624::lcdInit() {
  pcf8574.pinMode(SEG_A_PIN, OUTPUT);
  pcf8574.pinMode(SEG_B_PIN, OUTPUT);
  pcf8574.pinMode(SEG_C_PIN, OUTPUT);
  pcf8574.pinMode(SEG_D_PIN, OUTPUT);
  pcf8574.pinMode(SEG_E_PIN, OUTPUT);
  pcf8574.pinMode(SEG_F_PIN, OUTPUT);
  pcf8574.pinMode(SEG_G_PIN, OUTPUT);
  pcf8574.pinMode(SEG_H_PIN, OUTPUT);

  if (!pcf8574.begin()) {
    Serial.println("ERROR PCF8574");
  }
}

void LTC4624::lcdScan() //dynamic lighting (run 200-250 times per second)
{
  static uint8_t digit = 0;

  setDutyPWMPB1(0);
  setDutyPWMPB2(0);
  setDutyPWMPB3(0); //turn off all digits

  if (BIT_IS_SET(sbuff[digit], 0)) pcf8574.digitalWrite(SEG_H_PIN, 0); // On
  else pcf8574.digitalWrite(SEG_H_PIN, 1); //Off

  if (BIT_IS_SET(sbuff[digit], 1)) pcf8574.digitalWrite(SEG_A_PIN, 0);
  else pcf8574.digitalWrite(SEG_A_PIN, 1);

  if (BIT_IS_SET(sbuff[digit], 2)) pcf8574.digitalWrite(SEG_B_PIN, 0);
  else pcf8574.digitalWrite(SEG_B_PIN, 1);

  if (BIT_IS_SET(sbuff[digit], 3)) pcf8574.digitalWrite(SEG_C_PIN, 0);
  else pcf8574.digitalWrite(SEG_C_PIN, 1);

  if (BIT_IS_SET(sbuff[digit], 4)) pcf8574.digitalWrite(SEG_D_PIN, 0);
  else pcf8574.digitalWrite(SEG_D_PIN, 1);

  if (BIT_IS_SET(sbuff[digit], 5)) pcf8574.digitalWrite(SEG_E_PIN, 0);
  else pcf8574.digitalWrite(SEG_E_PIN, 1);

  if (BIT_IS_SET(sbuff[digit], 6)) pcf8574.digitalWrite(SEG_F_PIN, 0);
  else pcf8574.digitalWrite(SEG_F_PIN, 1);

  if (BIT_IS_SET(sbuff[digit], 7)) pcf8574.digitalWrite(SEG_G_PIN, 0);
  else pcf8574.digitalWrite(SEG_G_PIN, 1);

  switch (digit) {
    case 0:
      setDutyPWMPB3(dutyCycleLcd);
      break;
    case 1:
      setDutyPWMPB1(dutyCycleLcd);
      break;
    case 2:
      setDutyPWMPB2(dutyCycleLcd);
      break;
  }

  if (++digit > 2) digit = 0;
}

void LTC4624::lcdChar(uint8_t pos, uint8_t sign) //print a character
{
  uint8_t tmp = 0;

  switch (sign) //select the code of symbol
  {
    case 32: tmp = scode[10]; break;  //space
    case 45: tmp = scode[11]; break;  //"-"
    case 48: tmp = scode[0]; break;   //"0"
    case 49: tmp = scode[1]; break;   //"1"
    case 50: tmp = scode[2]; break;   //"2"
    case 51: tmp = scode[3]; break;   //"3"
    case 52: tmp = scode[4]; break;   //"4"
    case 53: tmp = scode[5]; break;   //"5"
    case 54: tmp = scode[6]; break;   //"6"
    case 55: tmp = scode[7]; break;   //"7"
    case 56: tmp = scode[8]; break;   //"8"
    case 57: tmp = scode[9]; break;   //"9"
    case 65: tmp = scode[12]; break;  //"A"
    case 66: tmp = scode[13]; break;  //"B"
    case 67: tmp = scode[14]; break;  //"C"
    case 68: tmp = scode[15]; break;  //"D"
    case 69: tmp = scode[16]; break;  //"E"
    case 70: tmp = scode[17]; break;  //"F"
    case 79: tmp = scode[0]; break;   //"O"
  }

  if (pos <= 2) sbuff[pos] = (tmp | (sbuff[pos] & 0b00000001));
}

void LTC4624::lcdPrint(uint8_t pos, const char *str) //print a string  //pos - 0..3 //str - text
{

  for (; *str;) {
    lcdChar(pos++, *str++);
  }
}

void LTC4624::lcdDot(uint8_t pos, uint8_t dot) //position 0..2 //dot 0-off 1-on
{
  if (pos <= 2)
  {
    if (dot) SET_BIT(sbuff[pos], 0);
    else CLR_BIT(sbuff[pos], 0);
  }
}

void LTC4624::lcdOff(void)
{
  setDutyPWMPB1(0);
  setDutyPWMPB2(0);
  setDutyPWMPB3(0); //turn off all digits

  pcf8574.digitalWrite(SEG_A_PIN, 1);
  pcf8574.digitalWrite(SEG_B_PIN, 1);
  pcf8574.digitalWrite(SEG_C_PIN, 1);
  pcf8574.digitalWrite(SEG_D_PIN, 1);
  pcf8574.digitalWrite(SEG_E_PIN, 1);
  pcf8574.digitalWrite(SEG_F_PIN, 1);
  pcf8574.digitalWrite(SEG_G_PIN, 1);
  pcf8574.digitalWrite(SEG_H_PIN, 1);
}

void LTC4624::lcdClear(void)
{
  sbuff[0] = 0x00;
  sbuff[1] = 0x00;
  sbuff[2] = 0x00;
}

void LTC4624::setDutyCycleLcd(uint8_t val)
{
  this->dutyCycleLcd = val;
}

uint8_t LTC4624::getDutyCycleLcd()
{
  return dutyCycleLcd;
}
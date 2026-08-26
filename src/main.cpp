#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // setting the I2C address(0x2 or 0x3F)
const uint8_t LED_PINS[4] = {2, 3, 4, 5};

void clearLcdSecondRow(uint8_t iteration);
void initialDisplay();
void initialLcdDisplay();

void setup()
{
  lcd.init();      // Initialize the 12C display
  lcd.backlight(); // Turn on the backlight

  lcd.setCursor(0, 0); // column 0 row 0
  lcd.print("4 bit Counter");

  lcd.setCursor(0, 1); // column 0 row 1
  lcd.print("decimal:Binary");
  for (uint8_t i = 0; i < 4; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }

  initialDisplay();
}

void loop()
{
  lcd.setCursor(0, 1);
  lcd.print("               ");

  for (uint8_t count = 0; count < 16; count++)
  {
    lcd.setCursor(0, 1);
    lcd.print("DEC:");
    lcd.print(count);

    lcd.setCursor(8, 1);
    lcd.print("BIN:");
    lcd.print(count, BIN);

    for (uint8_t bitPosition = 0; bitPosition < 4; bitPosition++)
    {
      // check if a bit in a certain position is zero or one
      // Starting from the LSB which is the rightmost bit.
      bool isBitZeroOrOne = bitRead(count, bitPosition);
      digitalWrite(LED_PINS[bitPosition], isBitZeroOrOne);
    }
    delay(2000);
    clearLcdSecondRow(count);
  }
}

void clearLcdSecondRow(uint8_t iteration)
{
  if (iteration == 15)
  {
    lcd.clear();
    initialLcdDisplay();
    initialDisplay();
    delay(1000);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("               ");
  }
}

void initialDisplay()
{
  for (uint8_t blink = 0; blink < 3; blink++)
  {
    for (uint8_t pin = 0; pin < 4; pin++)
    {
      digitalWrite(LED_PINS[pin], HIGH);
    }
    delay(500);

    for (uint8_t pin = 0; pin < 4; pin++)
    {
      digitalWrite(LED_PINS[pin], LOW);
    }
    delay(500);
  }
}

void initialLcdDisplay()
{
  lcd.setCursor(0, 0); // column 0 row 0
  lcd.print("4 bit Counter");

  lcd.setCursor(0, 1); // column 0 row 1
  lcd.print("decimal:Binary");
}

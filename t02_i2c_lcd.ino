#define BAUDRATE 115200
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd(0x27);  
int show;

void setup()
{
  int error;
  Serial.begin(BAUDRATE);
  Serial.println("LCD...");

  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.println(error);
  if (error == 0) 
    Serial.println("LCD found.");
   else {
    Serial.println("LCD not found.");
    while(1);
  }

  // initialize the lcd
  lcd.begin(16, 2); 
  show = 0;
} 

void loop()
{
  Serial.print("Show = ");
  Serial.println(show);
  if (show == 0) {
    lcd.setBacklight(255);
    lcd.home(); lcd.clear();
    lcd.print("Hello LCD");
    delay(1000);

    lcd.setBacklight(0);
    delay(400);
    lcd.setBacklight(255);

  } else if (show == 1) {
    lcd.clear();
    lcd.print("Cursor On");
    lcd.cursor();

  } else if (show == 2) {
    lcd.clear();
    lcd.print("Cursor Blink");
    lcd.blink();

  } else if (show == 3) {
    lcd.clear();
    lcd.print("Cursor OFF");
    lcd.noBlink();
    lcd.noCursor();

  } else if (show == 4) {
    lcd.clear();
    lcd.print("Display Off");
    lcd.noDisplay();

  } else if (show == 5) {
    lcd.clear();
    lcd.print("Display On");
    lcd.display();

  } else if (show == 7) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** first line.");
    lcd.setCursor(0, 1);
    lcd.print("*** second line.");

  } else if (show == 8) {
    lcd.scrollDisplayLeft();
  } else if (show == 9) {
    lcd.scrollDisplayLeft();
  } else if (show == 10) {
    lcd.scrollDisplayLeft();
  } else if (show == 11) {
    lcd.scrollDisplayRight();
  } // if

  delay(2000);
  show = (++show) % 12;

} 

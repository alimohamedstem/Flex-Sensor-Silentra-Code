#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//oled 0.96
#define ALARM 2
#define FLEX1 A6
#define FLEX2 A0
#define FLEX3 A1
#define FLEX4 A2
#define FLEX5 A3
int max = 300;
int min1 = 210;
int min2 = 180;
int min3 = 69;
int min4 = 100;
int min5 = 96;
int F1, F2, F3, F4 , F5;
String letters = "";  // String to store accumulated letters
void Alarm()
{
    digitalWrite(ALARM, HIGH);
    delay(100);
    digitalWrite(ALARM, LOW);
} 
void setup() {
  lcd.init();  // initialize the LCD
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("  SILENTRA");  // Display "SILENTRA" on the first row
   pinMode(ALARM, OUTPUT);
}

void loop() {
  F1 = analogRead(FLEX1);
  F2 = analogRead(FLEX2);
  F3 = analogRead(FLEX3);
  F4 = analogRead(FLEX4);
  F5 = analogRead(FLEX5);
//delay(500);
  // Check if all five sensors are closed
  if (F1 < min1 && F2 < min2 && F3 < min3 && F4 < min4 && F5 < min5) {
    letters = "";  // Clear the letters variable
       // Clear the LCD to reflect the change
    lcd.setCursor(0, 1);
    lcd.print("                ");  // Clear the second row if all fingers are closed
  }
  // Check for specific sensor combinations and add the corresponding letter
  else if (F1 < min1 && F2 >= min2 && F3 >= min3 && F4 >= min4 && F5 >= min5) {
    letters += "a";  // F1 closed
  }
  else if (F1 >= min1 && F2 < min2 && F3 >= min3 && F4 >= min4 && F5 >= min5) {
    letters += "b";  // F2 closed
  }
  else if (F1 >= min1 && F2 >= min2 && F3 < min3 && F4 >= min4 && F5 >= min5) {
    letters += "c";  // F3 closed
  }
  else if (F1 >= min1 && F2 >= min2 && F3 >= min3 && F4 < min4 && F5 >= min5) {
    letters += "d";  // F4 closed
  }
  else if (F1 >= min1 && F2 >= min2 && F3 >= min3 && F4 >= min4 && F5 < min5) {
    letters += "e";  // F5 closed
  }
  // Check for combinations of two sensors closed
  else if (F1 < min1 && F2 < min2 && F3 >= min3 && F4 >= min4 && F5 >= min5) {
    letters += "f";  // F1 + F2 closed
  }
  else if (F1 < min1 && F2 >= min2 && F3 < min3 && F4 >= min4 && F5 >= min5) {
    letters += "g";  // F1 + F3 closed
  }
  else if (F1 < min1 && F2 >= min2 && F3 >= min3 && F4 < min4 && F5 >= min5) {
    letters += "h";  // F1 + F4 closed
  }
  else if (F1 < min1 && F2 >= min2 && F3 >= min3 && F4 >= min4 && F5 < min5) {
    letters += "i";  // F1 + F5 closed
  }
  // Check for combinations of three sensors closed
  else if (F1 < min1 && F2 < min2 && F3 < min3 && F4 >= min4 && F5 >= min5) {
    letters += "j";  // F1 + F2 + F3 closed
  }
  else if (F1 < min1 && F2 < min2 && F3 >= min3 && F4 < min4 && F5 >= min5) {
    letters += "k";  // F1 + F2 + F4 closed
  }
  else if (F1 < min1 && F2 < min2 && F3 >= min3 && F4 >= min4 && F5 < min5) {
    letters += "l";  // F1 + F2 + F5 closed
  }
  else if (F1 < min1 && F2 >= min2 && F3 < min3 && F4 < min4 && F5 >= min5) {
    letters += "m";  // F1 + F3 + F4 closed
  }
  else if (F1 < min1 && F2 >= min2 && F3 >= min3 && F4 < min4 && F5 < min5) {
    letters += "n";  // F1 + F4 + F5 closed
  }
  else if (F2 < min2 && F3 < min3 && F4 < min4 && F5 >= min5) {
    letters += "o";  // F2 + F3 + F4 closed
  }
  else if (F1 >= min1 && F2 < min2 && F3 < min3 && F4 < min4 && F5 < min5){
     letters +=" ";
     Alarm();
  }
   // Check for removing a letter (when F1, F2, F3, F4 are closed)
  if (F1 >= min1 && F2 >= min2 && F3 >= min3 && F4 < min4 && F5 < min5) {
    if (letters.length() > 0) {
      letters.remove(letters.length() - 1);  // Remove last letter from the second row
    }
  }

  // Update the second row with the letters accumulated
 lcd.setCursor(0, 1);
//lcd.print(" Silence Speaks");  
 
//lcd.print(F1);
//lcd.print(" ");
//lcd.print(F3);
//lcd.print(" ");
//
lcd.print("                ");
 lcd.setCursor(0, 1);
//lcd.print(F2);
//lcd.print(" ");
//lcd.print(F5);
//lcd.print(" ");
lcd.print(letters);

  delay(600);  // Small delay to debounce sensor readings
}

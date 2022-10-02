 #include <LiquidCrystal.h>
int Contrast = 60;
const int rs = 5, en = 4, d4 = 22, d5 = 23, d6 = 24, d7 = 25; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  analogWrite(6, Contrast);
  lcd.begin(16, 2);
}
void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Hello Friends");

  lcd.setCursor(0, 1);
  lcd.print("CornGem 2022");
}

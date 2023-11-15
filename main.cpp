#include "juego.h"

int color=0;

void detalle(){
  if (color==1)
  {
    for (int i = 0; i< NUM_LEDS; i++)
    {
      leds[i] = azu;
      delay(5);
    }
    color=0;
  }
  else
  {
    for (int i = 0; i< NUM_LEDS; i++)
    {
      leds[i] = nar;
      delay(5);
    }
    color=1;
  };
}

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);//boton joystic en pull-up
    //lcd.backlight();
    lcd.begin(largolcd,altolcd);//lcd con numero de filas y columnas
    attachInterrupt(digitalPinToInterrupt(buttonPin),button,FALLING);
}

void loop() { //Menu
  int i=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BIENVENIDO");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">");
    lcd.setCursor(1,0);
    lcd.print(" S A L D O ");
    lcd.setCursor(1,1);
    lcd.print(" J U G A R");
    delay(2000);
  while(presionado==0){
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    //Serial.print(xPosition);
    //Serial.print(yPosition);
    //delay(1000);
    if (xPosition>=3000 || yPosition>=3000)//joystic hacia la derecha o abajo = movimiento hacia abajoxPosition>=4000 || yPosition>=4000
    {
      i=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(">");
      lcd.setCursor(1,0);
      lcd.print(" S A L D O ");
      lcd.setCursor(1,1);
      lcd.print(" J U G A R");
      delay(100);
    }
    if (xPosition<=1000 || yPosition<=1000)//joystic hacia la izquierda o arriba = movimiento hacia arribaxPosition<=2000 || yPosition<=2000
    {
      i=1;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(">");
      lcd.setCursor(1,0);
      lcd.print(" S A L D O ");
      lcd.setCursor(1,1);
      lcd.print(" J U G A R");
      delay(100);
    }
    else {;};
  };
  if (i==1){
    int a=play();
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("A JUGAR");
    //delay(2000);
    presionado=0;
  }
  if (i==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN DESARROLLO");
    delay(2000);
    presionado=0;
  }
  else {;};
}

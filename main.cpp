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

void loop()//Menu
{
  detalle();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">BIENVENIDO");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">");
    lcd.setCursor(1,0);
    lcd.print(" S A L D O ");
    lcd.setCursor(1,1);
    lcd.print(" J U G A R");
  detalle();
  int i=0; //cursor del menu
  while(presionado==0){
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    if (xPosition>=4000 || yPosition>=4000)//joystic hacia la derecha o abajo = movimiento hacia abajo
    {
      i=1;
      lcd.setCursor(0,0);
      lcd.print("> J U G A R");
      delay(300);
    }
    if (xPosition<=2000 || yPosition<=2000)//joystic hacia la izquierda o arriba = movimiento hacia arriba
    {
      i=0;
      lcd.setCursor(0,1);
      lcd.print("> S A L D O");
      delay(300);
    }
    else {;};
  };
  if (i=1){
    int a=play();
  }
  if (i=0){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EN DESARROLLO");
  }
  else {;};
}
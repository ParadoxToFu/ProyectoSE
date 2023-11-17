#include "juego.h"
#include <Wire.h>

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);//boton joystic en pull-up
    //lcd.backlight();
    lcd.begin(largolcd,altolcd);//lcd con numero de filas y columnas
    attachInterrupt(digitalPinToInterrupt(buttonPin),button,FALLING);
}

void loop()//Menu
{ 
  int i=0;
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("BIENVENIDO");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SELECCIONE:");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print(">");
    lcd.setCursor(1,1);
    lcd.print(" S A L D O ");
    lcd.setCursor(1,2);
    lcd.print(" J U G A R");
  while(presionado==0)
  {
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    //Serial.print(xPosition);
    //Serial.print(yPosition);
    //delay(2000);
    if (yPosition<=2000){//arriba(xPosition<=2000)derecha
      i=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SELECCIONE:");
      lcd.setCursor(0,1);
      lcd.print(">");
      lcd.setCursor(1,1);
      lcd.print(" S A L D O ");
      lcd.setCursor(1,2);
      lcd.print(" J U G A R");
      delay(100);
    }
    if (yPosition>=3500){//abajoarribax(xPosition>=3500)Izquierda
      i=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SELECCIONE:");
      lcd.setCursor(0,2);
      lcd.print(">");
      lcd.setCursor(1,1);
      lcd.print(" S A L D O ");
      lcd.setCursor(1,2);
      lcd.print(" J U G A R");
      delay(100);
    }
    //else{;};
  }
  if (i==1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A JUGAR");
    presionado=0;
    delay(1000);
    int z=1;
    while (z==1){
    z=play();
    }
    printf("Fin del programa\n%i\n",z);
    delay(2000);
  }
  if (i==0)
  {
    presionado=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN DESARROLLO");
    delay(2000);
  }
}

/*
#include <Arduino.h>
#include <stdio.h> 
#include <stdlib.h>
#include <LiquidCrystal.h>// libreria LCD
#include <Wire.h>

#define largolcd    16  //cambiar a 20
#define altolcd     2   //Cambiar a 4
#define rs          22  //pines lcd
#define en          23
#define d4          5
#define d5          18
#define d6          19
#define d7          21
#define buttonPin   33
#define xPin        34
#define yPin        35

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int presionado=0;
int xPosition = 0;
int yPosition = 0;

void IRAM_ATTR button(){ //Interrupcion boton joystic
presionado=1;
}

void setup() {
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
  lcd.clear();
  Serial.print(digitalRead(buttonPin));
  lcd.setCursor(0,0);
  lcd.print(">BIENVENIDO");
  lcd.clear();
  delay(100);
  /*
  lcd.setCursor(0,0);
  lcd.print(">");
    lcd.setCursor(1,0);
    lcd.print(" S A L D O ");
    lcd.setCursor(1,1);
    lcd.print(" J U G A R");
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
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("A Jugar");
    delay(2000);
  }
  if (i=0){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EN DESARROLLO");
  }
  else {;};
}
*/
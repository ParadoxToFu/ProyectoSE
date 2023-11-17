/*
#include <Arduino.h>
#include <stdio.h> 
#include <stdlib.h>
#include <FastLED.h>
#include <LiquidCrystal.h>// libreria LCD
//#include <Wire.h>

#define buttonPin   32
#define xPin        34
#define yPin        35
#define LED_PIN     15   //Pin de la tira WS2812
#define NUM_LEDS    30  //Numero de leds en la tira
#define marcas      4   //posiciones a jugar dadas por el usuario
#define random      10  //posiciones ganadoras
#define largolcd    20  //cambiar a 20
#define altolcd     4   //Cambiar a 4
#define rs          22  //pines lcd
#define en          23
#define d4          18
#define d5          19
#define d6          5
#define d7          21

//CRGB ver=(19,100,14);
//CRGB ama=(255,255,0);
//CRGB bla=(255,255,255);
CRGB azu=CRGB(0,0,255);//colores: axul, naranja, rojo, leds apagados
CRGB nar=CRGB(255,128,0);
CRGB roj=CRGB(255,0,0);
CRGB apa=CRGB(0,0,0);
CRGB leds[NUM_LEDS];
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int presionado=0;
int xPosition = 0;
int yPosition = 0;

int i; //recorre el array de los leds para inicio
int j;  //leds a marcar
signed int k;  //recorre el array de leds
int selec[marcas]={33,33,33,33};
int suerte;

//////////////////////////////////////////////////////////////

void IRAM_ATTR button(){ //Interrupcion boton joystic
presionado=1;
}

void inicio()//enciende todos los leds
{
  int i=0;
    for (i = 0; i< NUM_LEDS; i++){
        leds[i] = azu;
        FastLED.show();
        delay(50);
    }
     for (i = 0; i< NUM_LEDS; i++){
        leds[i] =nar;
        FastLED.show();
        delay(50);
    }
    for (i = 0; i< NUM_LEDS; i++){
        leds[i] = azu;
        FastLED.show();
        delay(50);
    }
}

void seleccion(){
  int rest=marcas;
  presionado=0;
  j=0;//# de leds marcados
  k=0;//posision el array de los leds
  leds[k]=roj;
  FastLED.show();
  int l=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Posiciones Restantes");
  delay(1000);
  printf("Numeros Seleccionados=\n");
  while (j<marcas){
    l=k;
    lcd.setCursor(9,2);
    lcd.print(rest);
    yPosition = analogRead(yPin);
    //Serial.print(yPosition);
    if (yPosition<=1000){//joystic hacia abajo
      k++;
      if (k>=NUM_LEDS){//mayor igual
        k=0;
        }
      leds[l]=azu;
      leds[k]=roj;
      FastLED.show();
      //printf("k%i\n",k);
      delay(100);
      }
    if (yPosition>=3000){//joystic hacia arriba
      k--;
      if (k<=-1){//menor igual
        k=NUM_LEDS-1;
        }
      leds[l]=azu;
      leds[k]=roj;
      FastLED.show();
      //printf("k%i\n",k);
      delay(100);
      }
    if (presionado==1)//se añade el led por su posicion a la lista de los seleccionados por el usuario
    {
      selec[j]=k;
      printf("%i ",selec[j]);
      leds[k]=roj;
      FastLED.show();
      j++;
      rest=marcas-j;
      delay(100);
      presionado=0;
     }
    for(int i=0;i<marcas;i++){
      leds[selec[i]] = roj;
      FastLED.show();
    }
  }
  printf("\n");
  lcd.setCursor(9,2);
  lcd.print(rest);
  delay(2000);
}

void pazu(int a[], CRGB b[]){
for (i = 0; i< random; i++)
    {
        b[a[i]] = azu;
        FastLED.show();
        delay(50);
    }
}

void pnar(int a[], CRGB b[]){
for (i = 0; i< random; i++)
    {
        b[a[i]] = nar;
        FastLED.show();
        delay(50);
    }
}

void recorrido(int a[], CRGB b[]){//efecto de luz led
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cruza los dedos!");
      pazu(a,b);
      pnar(a,b);
}

void comprobacion(int a[], int b[], int c, int d)//array leds ganandores, array de selecionados, #leds ganadores, #leds seleccionados 
{
j=0;
for (i = 0;i <c; i++)
{
  int x=a[i];
  for (j=0;j<d;j++){
    int y=b[j];
    if (y==x){suerte=1;}
    else {;}
  }
}
if (suerte!=1){suerte=0;}// si no tuvo ni un acierto, perdio
}

void gameover(){
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("MALA SUERTE");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("FIN DEL JUEGO");
  delay(2000);
}

int play() {
  inicio();
  for(int i=0;i<marcas;i++){
      selec[i] = 30;
      FastLED.show();
    }
  seleccion();
  int arr[random];
  srand(time(NULL));
  printf("Numeros Ganadores=\n");
  for (int i=0;i<random;i++)
    {
      arr[i]=1+rand()%(0-29);
      printf("%i ",arr[i]);
    }
  printf("\n");
  recorrido (arr,leds);
  delay(1000);
  recorrido (arr,leds);
  delay(1000);
  recorrido (arr,leds);
  delay(1000);
  pnar(arr,leds);
  comprobacion(arr, selec, random, marcas);
  delay(2000);
  if(suerte==1){         
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GANASTE UN INTENTO!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("JUGAR DENUEVO?");
  delay(3000);
  presionado=0;
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.setCursor(1,1);
  lcd.print(" SI ");
  lcd.setCursor(1,2);
  lcd.print(" NO");
  while(presionado==0)      
  {
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    if (yPosition>=3000){//joystic hacia arriba
      i=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("JUGAR DENUEVO?");
      lcd.setCursor(0,1);
      lcd.print(">");
      lcd.setCursor(1,1);
      lcd.print(" SI ");
      lcd.setCursor(1,2);
      lcd.print(" NO");
      delay(100);
    }
    if (yPosition<=1000){//joystic hacia abajo
      i=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("JUGAR DENUEVO?");
      lcd.setCursor(0,2);
      lcd.print(">");
      lcd.setCursor(1,1);
      lcd.print(" SI ");
      lcd.setCursor(1,2);
      lcd.print(" NO");
      delay(100);
    }
    //else{;};
    }
    if (i==1){
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print("ADIOS");
      delay(2000);
      suerte=0;
      return suerte;
     }
    if (i==0)
    {
      return suerte;
    }
    printf("\n%i\n",suerte);
    }
}

/////////////////////////////////////////////////////////////

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
    if (yPosition>=3000){//joystic hacia arriba(xPosition<=2000)derecha
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
    if (yPosition<=1000){//joystic hacia abajo(xPosition>=3500)Izquierda
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
*/

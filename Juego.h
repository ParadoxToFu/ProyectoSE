#ifndef Juego_H
#define Juego_H

#include <Arduino.h>
#include <stdio.h> 
#include <stdlib.h>
#include <FastLED.h>
#include <LiquidCrystal.h>// libreria LCD

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
extern CRGB azu;
extern CRGB nar;
extern CRGB roj;
extern CRGB apa;
extern CRGB leds[NUM_LEDS];
extern LiquidCrystal lcd;
extern int presionado;
extern int xPosition;
extern int yPosition;

void IRAM_ATTR button();
void inicio();
void seleccion();
void recorrido(int a[], CRGB b[]);
void comprobacion(int a[], int b[], int c, int d);
void gameover();
int  play();

#endif

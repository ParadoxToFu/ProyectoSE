#include "juego.h"

int xPosition = 0;
int yPosition = 0;

int i; //recorre el array de los leds para inicio
int j;  //# de leds marcados
signed int k;  //recorre el array de leds
int presionado=0;
int suerte=1;
int selec[marcas];

CRGB azu=(0,0,255);//colores: axul, naranja, rojo, leds apagados
CRGB nar=(288,128,0);
CRGB roj=(255,0,0);
CRGB apa=(0,0,0);
CRGB leds[NUM_LEDS];
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void IRAM_ATTR button(){ //Interrupcion boton joystic
presionado=1;
}

void inicio(){//enciende todos los leds
  i=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inicio del juego");
    for (i = 0; i< NUM_LEDS; i++){
        leds[i] = azu;
        delay(80);
    }
}

void seleccion(){
  int rest=marcas-j;
  j=0;//# de leds marcados
  k=0;//posision el array de los leds
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Selecciones Restantes:");
  lcd.setCursor(8,1);
  lcd.print(rest);
  while (j<marcas+1){
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    if (k!=selec[0]||k!=selec[1]||k!=selec[2]||k!=selec[3]||k!=selec[4]){//Parpadeo de leds mientras el "cursor esta encima de ellos"
      leds[k]=roj;
      delay(50);
      leds[k]=azu;
      delay(50);
    }
    if ((presionado==1)&&k!=selec[0]||k!=selec[1]||k!=selec[2]||k!=selec[3]||k!=selec[4])//se añade el led por su posicion a la lista de los seleccionados por el usuario
    {
      selec[j]=k;
      leds[k]=roj;
      j++;
      rest=marcas-j;
      presionado=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Selecciones Restantes:");
      lcd.setCursor(8,1);
      delay(200);
      lcd.print(rest);
     }
    if (xPosition>=4000 || yPosition>=4000){k++;delay(150);}//joystic hacia la derecha o abajo = movimiento a la derecha
    if (xPosition<=2000 || yPosition<=2000){k--;delay(150);}//joystic hacia la izquierda o arriba = movimiento a la izquierda
    if (k<=-1){k=NUM_LEDS;delay(150);}//menor igual
    if (k>=NUM_LEDS+1){k=0;delay(150);}//mayor igual
    else {;};
  }
}

void recorrido(int a[], CRGB b[]){//efecto de luz led
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("¡Cruza los dedos!");
    for (i = 0; i< random; i++)
    {
        b[a[i]] = nar;
        delay(100);
        b[a[i]] = azu;
        delay(100);
    }
    for (i = 0; i< random; i++)
    {
        b[a[i]] = nar;
        delay(100);
        b[a[i]] = azu;
        delay(100);
    }
    for (i = 0; i< random; i++)
    {
        b[a[i]] = nar;
        delay(100);
    }
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
  lcd.setCursor(0,0);
  lcd.print("Mala Suerte");
  delay(600);
  lcd.setCursor(0,1);
  lcd.print("Fin del Juego");
}

int play()
{
while (suerte==1)// preguntar si quiere volver a jugar, con un boton de interrupcion??
{
inicio();
seleccion();
int arr[random];
srand(time(NULL));
for (int i=0;i<random;i++)
  {
    arr[i]=1+rand()%(0-30);
  }
recorrido (arr,leds);
comprobacion(arr, selec, random, marcas);
return suerte;
}
gameover();
return suerte;
}
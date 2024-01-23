#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <FirebaseJson.h>

#define FIREBASE_HOST "proyectoembebidos-c74df-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBV6CPicWw9JyLqaknWXmZu8DlehBpEQ8g"

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

#define SS_PIN 5
#define RST_PIN 22

extern MFRC522 rfid;
extern MFRC522::MIFARE_Key key;
extern byte nuidPICC[4];

void consulta();

#endif

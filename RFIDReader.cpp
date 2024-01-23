#include "RFIDReader.h"

MFRC522 rfid(SS_PIN, RST_PIN); // rfid
MFRC522::MIFARE_Key key;

byte nuidPICC[4];

/* Para el setup del proyecto, falta implementar y probar
void setup() 
{
  Serial.begin(115200);
  SPI.begin(); // Para el SPI
  rfid.PCD_Init(); 
  Serial.println();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  } 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.println();
  Serial.println();
  Serial.println("Iniciando el Programa");
}
*/
  
void consulta() {
  // Espera a que se acerque un targeta
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Verifica que se ha leido
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  String uid = "";
  for (byte i = 0; i < 4; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  Serial.print("UID detectada: ");
  Serial.println(uid);

  HTTPClient http;
  http.begin("https://" + String(FIREBASE_HOST) + "/EmbebidosAPP.json?auth=" + String(FIREBASE_AUTH));
  int httpCode = http.GET();
  if(httpCode > 0) {
    String payload = http.getString();
    FirebaseJson json;
    json.setJsonData(payload);
    FirebaseJsonData jsonData;
    for (int i = 1; i <= 4; i++) { // Se asumen 4 entradas en la base de datos
      String path = String(i) + "/id";
      json.get(jsonData, path);
      if (jsonData.stringValue == uid) {
        path = String(i) + "/saldo";
        json.get(jsonData, path);
        String saldo = jsonData.stringValue;
        Serial.print("Código: ");
        Serial.println(i);
        Serial.print("Saldo: ");
        Serial.println(saldo);
        break;
      }
    }
  } else {
    Serial.println("Error al obtener Datos");
  }
  http.end();
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

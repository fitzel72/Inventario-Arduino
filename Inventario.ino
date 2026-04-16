#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <Wire.h>
#include <RTClib.h>

#define CS_RFID 10
#define RST_RFID 9
#define CS_SD 4
#define MAX_TARJETAS 10

MFRC522 rfid(CS_RFID, RST_RFID);
RTC_DS1307 rtc;
String uidString;

// Arreglos para guardar múltiples tarjetas y su estado
String uidRegistrados[MAX_TARJETAS];
String estadoTarjeta[MAX_TARJETAS];
int numTarjetas = 0;

void setup() {
  Serial.begin(9600);
  delay(2000); 
  Serial.println();
  Serial.println("=== INICIANDO SISTEMA ===");
  
  SPI.begin();
  
  // Inicializar SD
  if (!SD.begin(CS_SD)) {
    Serial.println("Error: SD no detectada");
  } else {
    Serial.println("SD OK");
  }
  
  // Inicializar RFID
  rfid.PCD_Init();
  Serial.println("RFID OK");
  
  // Inicializar RTC
  if (!rtc.begin()) {
    Serial.println("Error: RTC no detectado");
  } else {
    Serial.println("RTC OK");
  }
  
  Serial.println("\nSISTEMA DE INVENTARIO");
  Serial.println("Acerca una tarjeta o llavero\n");
}

int buscarTarjeta(String uid) {
  for (int i = 0; i < numTarjetas; i++) {
    if (uidRegistrados[i] == uid) {
      return i;
    }
  }
  return -1;
}

void agregarTarjeta(String uid) {
  if (numTarjetas < MAX_TARJETAS) {
    uidRegistrados[numTarjetas] = uid;
    estadoTarjeta[numTarjetas] = "ENTRADA";
    numTarjetas++;
  }
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;
  
  // Leer UID
  uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += String(rfid.uid.uidByte[i]);
    if (i < rfid.uid.size - 1) uidString += " ";
  }
  
  // Buscar o agregar tarjeta
  int indice = buscarTarjeta(uidString);
  if (indice == -1) {
    agregarTarjeta(uidString);
    indice = numTarjetas - 1;
  } else {
    // Alternar estado
    if (estadoTarjeta[indice] == "ENTRADA") {
      estadoTarjeta[indice] = "SALIDA";
    } else {
      estadoTarjeta[indice] = "ENTRADA";
    }
  }
  
  // Obtener fecha y hora
  DateTime now = rtc.now();
  String fecha = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day());
  String hora = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  
  // Mostrar en monitor
  Serial.print(uidString);
  Serial.print(",");
  Serial.print(fecha);
  Serial.print(",");
  Serial.print(hora);
  Serial.print(",");
  Serial.println(estadoTarjeta[indice]);
  
  // Guardar en SD
  File myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(uidString);
    myFile.print(",");
    myFile.print(fecha);
    myFile.print(",");
    myFile.print(hora);
    myFile.print(",");
    myFile.println(estadoTarjeta[indice]);
    myFile.close();
  }
  
  rfid.PICC_HaltA();
  delay(500);
}

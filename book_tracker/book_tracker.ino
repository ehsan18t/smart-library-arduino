#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SPI.h>
#include <MFRC522.h>

// RFIDa

#define indicator D0
#define RST_PIN   D3     // Reset pin
#define SS_PIN    D8     // Slave Select pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String scannedUID = "";  // Variable to hold the scanned UID

// RFID END

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

const char* ssid = "Bachelors Base"; //--> Your wifi name or SSID.
const char* password = "bananparina69"; //--> Your wifi password.


//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------

WiFiClientSecure client; //--> Create a WiFiClientSecure object.

String GAS_ID = "AKfycbyWRutvqboMTeVSIZmYodkyy4Dx_HA3H56XzdF19sjkS2aepJYqT6o7Ox_9IiPsvpvk"; //--> spreadsheet script ID

void setup() {
  // Indicator
  pinMode(indicator, OUTPUT);
  
  // RFID
  Serial.begin(115200);
  SPI.begin();     // Initialize SPI bus
  mfrc522.PCD_Init();  // Initialize MFRC522
  Serial.println("MFRC522 initialized");


  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  client.setInsecure();
}

void loop() {
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Card detected!");

    // blink 100ms
    digitalWrite(indicator, HIGH);
    delay(100);
    digitalWrite(indicator, LOW);
    

    Serial.print("UID Length: ");
    Serial.print(mfrc522.uid.size, DEC);
    Serial.println(" bytes");

    scannedUID = "";  // Clear the previous scanned UID
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      scannedUID += mfrc522.uid.uidByte[i] < 0x10 ? "0" : "";
      scannedUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.print("Scanned UID: ");
    Serial.println(scannedUID);
  
    sendData(scannedUID);

    mfrc522.PICC_HaltA();     // Halt PICC
    mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD
  }
}

void sendData(String str) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------

  String url = "/macros/s/" + GAS_ID + "/exec?shelf=1&row=1 &id=" + str;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/113.0\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------

  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("Content-Type: text/html; charset=UTF-8")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
    // blink 1 sec
    digitalWrite(indicator, HIGH);
    delay(1000);
    digitalWrite(indicator, LOW);
  //----------------------------------------
}

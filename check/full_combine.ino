#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
// Set these to run example. 
#define FIREBASE_HOST "smart-shopping-cart-a1285-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "tASqA1ozbYoj9Jjd9MvGLOzzYq1YQWTxaChf9UZ5" 
#define WIFI_SSID "oppo"  // type your wifi device
#define WIFI_PASSWORD "22222222"  //type your wifi password

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char i1 = "Maggi";
char r1 = "45rs";
char i2 = "Lays";
char r2 = "20rs";

void setup() {
   Serial.begin(9600); 
 
  // connect to wifi. 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  /*delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.print("I PHONE");
    display.print("Rs 150000");
    display.display();*/

} 
 
int n = 0; 
 
void loop() {
    // set value 
  Firebase.setFloat("number", 42.0); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
   
  // update value 
  Firebase.setFloat("number", 43.0); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
 
  // get value  
  Serial.print("number: "); 
  Serial.println(Firebase.getFloat("number")); 
  delay(1000); 
 
  // remove value 
  Firebase.remove("number"); 
  delay(1000); 
 
  // set string value 
  Firebase.setString("message", "hello world"); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /message failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
   
  // set bool value 
  Firebase.setBool("truth", false); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("setting /truth failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  delay(1000); 
 
  // append a new value to /logs 
  String name = Firebase.pushInt("logs", n++); 
  // handle error 
  if (Firebase.failed()) { 
      Serial.print("pushing /logs failed:"); 
      Serial.println(Firebase.error());   
      return; 
  } 
  Serial.print("pushed: /logs/"); 
  Serial.println(name); 
  delay(1000); 

  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "29 C2 07 5E") // Make sure you change this with your own UID number
  {
    Serial.println("Authorised access");
    Serial.println();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.print(i1);
    display.print(r1);
    display.display();
    display.clearDisplay();
    delay(1000);
  }

  else if (content.substring(1) == "47 42 23 A1") // Make sure you change this with your own UID number
  {
    Serial.println("Authorised access");
    Serial.println();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println(i2);
    display.print(r2);
    display.display();
    display.clearDisplay();
    delay(1000);
  }

  else   {
    Serial.println(" Access denied");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("You can't Buy this item!");
    display.display();
    display.clearDisplay();
    delay(1000);
    //delay(3000);
  }

}

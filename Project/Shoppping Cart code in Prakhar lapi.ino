
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
char i1[10] = "ChocoBakes Cookies";
char r1[10] = "45rs";
char i2[10] = "Maaza";
char r2[10] = "20rs";

void setup() 
{
    Serial.begin(9600);
    SPI.begin();      
    mfrc522.PCD_Init();   
    Serial.println("Approximate your card to the reader...");
    Serial.println();
  

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("WELCOME");
  display.display();

   

}
void loop() 
{
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  Serial.print("UID tag :");
  String content= "";
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
  if (content.substring(1) == "23 24 DD 1A") // Make sure you change this with your own UID number
  {
    Serial.println("Authorised access");
    Serial.println();
    display.display();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println(i1);
    display.println(r1);
    display.display();
    display.clearDisplay();
    delay(1000);
  }

  else if (content.substring(1) == "42 47 4C 1A") // Make sure you change this with your own UID number
  {
    Serial.println("Authorised access");
    Serial.println();
    display.display();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println(i2);
    display.println(r2);
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
    display.println("You  can't  Buy  this item!");
    display.display();
    display.clearDisplay();
    delay(1000);
    //delay(3000);
  }
}
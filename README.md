# IoT Smart Shopping Cart

## Project Overview
This **IoT Smart Shopping Cart** project automatically adds products to a shopping list by scanning them using RFID technology as you place them in the cart. It reduces the need for manual scanning at checkout counters, saving time and minimizing queues. The cart displays the added items and their prices, and the only remaining step for customers is to make the payment at the counter.

## Features
- Automatically adds products to a shopping list by scanning RFID tags.
- Displays the product name and price on an OLED screen.
- Differentiates between authorized and unauthorized products.
- Helps reduce time spent at the checkout counter.

## Components Used
- Arduino
- MFRC522 RFID Reader
- OLED Display (SSD1306, I2C)
- RFID Tags for products
- Jumper wires, breadboard, and power supply

## Prerequisites
To run this project, you need the following libraries installed in your Arduino IDE:
- **SPI.h** (for communication between the RFID reader and Arduino)
- **MFRC522.h** (for handling the RFID module)
- **Wire.h** (for I2C communication)
- **Adafruit_GFX.h** (for graphics display on the OLED)
- **Adafruit_SSD1306.h** (for controlling the OLED screen)

Install these libraries via the Arduino Library Manager if not already present.

## Circuit Diagram
1. **MFRC522 RFID Reader**:
   - SDA -> Pin 10
   - SCK -> Pin 13
   - MOSI -> Pin 11
   - MISO -> Pin 12
   - RST -> Pin 9
   - VCC -> 3.3V
   - GND -> GND

2. **OLED Display** (SSD1306):
   - SDA -> A4
   - SCL -> A5
   - VCC -> 3.3V
   - GND -> GND

## Setup Instructions

1. **Clone the Repository**:
   Download the project code from the repository or copy the code provided above into your Arduino IDE.

2. **Install Required Libraries**:
   - Go to Sketch > Include Library > Manage Libraries.
   - Search for **MFRC522**, **Adafruit SSD1306**, and **Adafruit GFX** and install them.

3. **Upload the Code**:
   - Open the Arduino IDE and upload the code to your Arduino board.
   - Make sure the RFID and OLED connections are properly made as per the circuit diagram.

4. **Modify Product Information**:
   - You can modify the product names and prices in the code by changing the variables `i1`, `r1`, `i2`, and `r2`.
   - Replace the RFID tag UIDs in the `if` statements with the UIDs of the tags you're using.

## Code Overview

The provided code has the following main functionalities:
1. **RFID Scanning**: 
   - The RFID reader detects if a card/tag is presented and reads its UID.
   - The UID is compared with predefined UIDs in the code to identify the product.

2. **OLED Display**:
   - The OLED screen shows a welcome message when powered on.
   - When a recognized product is scanned, it displays the product name and price.
   - If an unrecognized product is scanned, it displays an "Access denied" message.

3. **Product List**:
   - `i1`, `r1`: Represents the first product (e.g., "ChocoBakes Cookies" for 45rs).
   - `i2`, `r2`: Represents the second product (e.g., "Maaza" for 20rs).
   - You can expand the product list by adding more RFID UIDs and corresponding products.

## How It Works

- When you scan a product's RFID tag near the reader, the RFID module reads its UID.
- The system compares the UID with predefined UIDs (associated with specific products).
- If a match is found, the product is displayed on the OLED screen along with its price.
- If an unrecognized product is scanned, the system will deny access and notify the user on the OLED screen.

## Project Flow

1. Power on the system.
2. The OLED screen will display "WELCOME".
3. As products are scanned (using RFID), the product names and prices will be displayed on the OLED screen.
4. The customer continues adding products to the cart without waiting at the counter for scanning.
5. At checkout, the customer proceeds directly to payment after the items have been automatically added.

## Future Improvements
- **Expand Product List**: Add more RFID tags and associate them with additional products.
- **Payment Integration**: Integrate a payment system to enable automatic billing.
- **Mobile App**: Create a mobile app that syncs with the cart for real-time updates on the items added.

## Cart Table 
![image](https://github.com/user-attachments/assets/011c64ae-c118-4bd0-9dae-e6b4d3499afa)


## Team 
![image](https://github.com/user-attachments/assets/b0c0f73c-d29b-442d-8669-2a568069b19b)

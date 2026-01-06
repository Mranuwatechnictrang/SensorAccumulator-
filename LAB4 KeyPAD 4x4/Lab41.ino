/* LAB4.1 4x4  */ 
// https://app.cirkitdesigner.com/project/a2fae946-3597-4420-930b-c4fa3786b62f

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Keypad.h>

#define ledBPin 13 
#define Sol_Pin 8  // Solinoid

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4; // Number of rows
const byte COLS = 4; // Number of columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {12, 11, 10, 9};   // Connect to R1, R2, R3, R4
byte colPins[COLS] = {7, 6, 5, 4};   // Connect to C1, C2, C3, C4

// Create a Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input_password = "";

// รหัสผ่าน
const String password_1 = "1234";

void setup() {
    Serial.begin(9600); // Initialize serial communication
    Serial.println("4x4 Keypad Test");
    pinMode(ledBPin,OUTPUT);
    pinMode(Sol_Pin,OUTPUT);

    digitalWrite(ledBPin,0) ; 
    digitalWrite(Sol_Pin,0) ; 

    lcd.init();
    lcd.backlight();
    lcd.clear();
         
    lcd.setCursor(0,0);
    lcd.print("4x4 Keypad Test");
    lcd.setCursor(0,1);
    lcd.print("Anuwat");
    delay(2000) ;

    lcd.clear();


}

void loop() {
 
    lcd.setCursor(0,0);
    lcd.print("Key Pressed:");
    char key = keypad.getKey(); // Get the key pressed
    if (key) { // If a key is pressed
        Serial.print("Key Pressed: ");
        Serial.println(key); // Print the key to the serial monitor

        /* ปุ่ม * == > Clear */ 
        if (key == '*') {
            input_password = "";
            lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("CLEAR PASSWORD");
            delay(1000);
            lcd.clear();
        }
        
        else if (key == '#') {
            if (input_password==password_1){
                lcd.clear();
                lcd.print("Password OK");
                Serial.print("Password OK");
                digitalWrite(ledBPin,1) ; 
                digitalWrite(Sol_Pin,1) ; 
                delay(3000);
                digitalWrite(ledBPin,0) ; 
                digitalWrite(Sol_Pin,0) ; 
               
            }
            else {
                lcd.clear();
                lcd.print("Password FAIL");
                delay(3000);
            }
        input_password = "";
        lcd.clear();

        }

        else {
            input_password += key;
            lcd.setCursor(0,1);
            lcd.print(input_password);
        }
    }

  
   

}

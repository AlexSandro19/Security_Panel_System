#include <Keypad.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, A1, A2, A3, A4);  // sets the interfacing pins

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
int user_input_count = 1; // for each iteration, user can input only 4 digits
String correct_pass = "3322";
String user_pass = "";
bool pass_valid = false;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);  // initializes the 16x2 LCD
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3,  LOW);
  digitalWrite(A4, LOW);
  lcd.clear();  
}


  
void loop(){
    Serial.println("Password checking through Keypad\n");
    Serial.print("Value of pass_valid in the beginning: ");
    Serial.println(pass_valid);
    while(!pass_valid){ //while pass if not correct
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Input Password:");
      lcd.setCursor(0,1);
      while(user_input_count <= 4){
        char customKey = customKeypad.getKey();
        if (customKey){
          lcd.print("*");
          user_pass.concat(customKey);
          user_input_count = user_input_count + 1;
        }
      }   
      Serial.print("Correct pass: ");
      Serial.println(correct_pass);   
      Serial.print("User pass: ");
      Serial.println(user_pass);   
      if (user_pass.equals(correct_pass)){
          pass_valid = true;
          lcd.clear();
          lcd.setCursor(0,0);
      }else{
          lcd.clear();
          lcd.setCursor(0,0);  
          lcd.print("Wrong Password:");
          lcd.setCursor(0,1);  
          lcd.print("Try Again!");
          delay(1000); 
          user_input_count = 1;
          user_pass = "";
      }
    }
    
    Serial.print("Value of pass_valid before confirming: ");
    Serial.println(pass_valid);
    if(pass_valid){
      lcd.setCursor(0,0);
      lcd.print("Input is correct");
      lcd.setCursor(0,1);
      lcd.print("Access Granted"); 
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(2000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(2000);
      pass_valid = false;
      user_input_count = 1;
      user_pass = "";
    } 

    Serial.print("Value of pass_valid at end: ");
    Serial.println(pass_valid);
   
    


    
  
}

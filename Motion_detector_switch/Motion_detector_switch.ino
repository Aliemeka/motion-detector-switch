/*
 * Motion dectector switch
 * Author: Emeka Allison
 * An Arduino Uno program
 * 
 * An automatic switch which uses two passive infrared sensors (PIR) to control the 
 * lightening of a room.
 * 
 * Components:
 * Arduino Uno
 * 2 Relay
 * Step-down Transformer
 * 2 PIR sensors
 * 2 Light bulbs
 * LCD display
 * 
 * Description:
 * When motion is detected in one sensor, it switches on the relay. If no motion is   
 * detected in two minutes the relay is switched off.
 * 
 * 
 */

#include<LiquidCrystal.h>


LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //sets LCD output pins
int relay[2]={8,9}; //set relay output to pin 8 and pin 9
int pir[2]={12,11};  //set pir input to pin 12 and pin 11
boolean currentState[2]={LOW,LOW}; //sets trigger states to be low
int relaytotal=2; 
boolean lastState[2] = {HIGH, HIGH}; //sets current states to low

void setup()
{
  Serial.begin(9600); //set the Serial Monitor on the computer to start
  Serial.println("Ready"); //Displays
  lcd.begin(16, 2); //set 16x2 LCD display
  pinMode (12,  INPUT); //makes pin 12 input
  pinMode (11, INPUT);  //makes pin 11 input
  pinMode (8, OUTPUT);  //makes pin 8 output
  pinMode (9, OUTPUT);  //makes pin 9 output
  digitalWrite(8,LOW);  //turns off pin 8
  digitalWrite(9,LOW);  //turns off pin 9
  
  //Default LCD display
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(2,0);
  lcd.print("SWITCH STATUS");
  lcd.setCursor(0,1);
  lcd.print("               ");
  lcd.print("NO MOTION!!!");
  delay(1500);
  lcd.print("               ");
  lcd.print("RELAY OFF");
}

void loop()
{
  for(int i=0; i<=1;i++){
    currentState[i]=digitalRead(pir[i]);
    delay(200);
    if(currentState[i]==HIGH){
      delay(100);
      
      if(currentState[i]==HIGH){
        digitalWrite(relay[i],HIGH);
        //LCD display status when circuit is on
        if(lastState[i] != currentState[i]){
          lcd.setCursor(0,1);
          lcd.print("               ");
          lcd.print("MOTION DETECTED");
          delay(1500);
          lcd.print("               ");
          lcd.print("RELAY ON");
        }
      }
       
    }
    else{
      delay(12000);
      digitalWrite(relay[i],LOW);

      //LCD display status when circuit is off
      if(lastState[i] != currentState[i]){ 
        lcd.setCursor(0,1);
        lcd.print("               ");
        lcd.print("NO MOTION!!!");
        delay(1500);
        lcd.print("               ");
        lcd.print("RELAY OFF");
      }
    }
    delay(500);

    //Serial monitor
    Serial.print(digitalRead(pir[i]));
    Serial.print(" ");
    Serial.println(digitalRead(relay[i]));
    
    lastState[i] = currentState[i];
  }
  delay(500);
}

 


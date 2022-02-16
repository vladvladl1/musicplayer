#include <NewTone.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h> 
#define TONE_PIN 38 // Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor).

LiquidCrystal_I2C lcd(0x27, 16, 2 );
int reciever = 36;
IRrecv irrecv(reciever);
decode_results results;
byte play[8]{
0b00000,
0b11000,
0b11100,
0b11110,
0b11111,
0b11110,
0b11100,
0b11000
};
byte slash[8]{
0b01110,
0b01110,
0b01110,
0b01110,
0b01110,
0b01110,
0b01110,
0b01110
};

byte dai[8]{
0b11011,
0b11011,
0b11011,
0b11011,
0b11011,
0b11011,
0b11011,
0b11011
};
// Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

int melody2[] = { 100, 233, 43, 23, 56, 2, 21, 123 };
int melody3[] = { 1, 100, 100, 100, 100, 100, 100, 100,100,100,100,100,100,100,100,100,100,100,100,100,100,297 };
int noteDurations3[] = { 2, 2, 2, 2, 2, 2, 2, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

int measures[] = 
{
  440,440,440,440,
  440,415,440,494,523,
  494,587,523,494,440,415,
  440,659,523,659,440,330,370,415,
  440,440,440,440,
  440,415,440,494,523,
  494,587,523,494,440,415,
  440,659,523,659,440,
  587,587,587,587,
  587,554,587,659,698,
  523,523,523,523,
  523,494,523,587,659,
  466,466,466,466,
  466,440,494,523,587,523,494,587,
  440,659,370,415,440,659,523,659,
  440,0
};
int stt=0;
int noteDurations4[] = { 4,4,4,4,8,8,8,8,2,8,8,3,8,8,8,8,8,8,8,8,8,8,8,4,4,4,4,8,8,8,8,2,8,8,3,8,8,8,8,8,8,8,2,4,4,4,4,8,8,8,8,2,4,4,4,4,8,8,8,8,2,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,2,4};
void setup() {
   Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.begin();
  lcd.createChar(0,play);
  lcd.createChar(1,slash);
  lcd.createChar(2,dai);
  
  } 
int value;
int adecvat=0;
int othervalue=0;
void loop() {

     if(irrecv.decode(&results)){
          value = results.value;
          stt=1;
      
      Serial.println(results.value);
      irrecv.resume();
      
    }
  if(stt==0 && adecvat==0){
    lcd.print("Welcome to your");
    lcd.setCursor(0,1);
    lcd.print("Cheap MP3 Player");
  }

 if(value==6228 | value==4180){
    adecvat++;
   
    
     if(adecvat==5){
       adecvat=1;
     }  
     value = value+1000;
  }
 if(value==6227 | value==4179){
    adecvat--;
     if(adecvat==0 | adecvat==-1){
       adecvat=4;
     }
     value = value+1000;
 }
 switch(adecvat){
  case 1:
  lcd.clear();
   lcd.print(adecvat);
   lcd.print(":tanana        ");
   lcd.setCursor(0,1);
   lcd.print("                ");
   othervalue = 4161;
   break;
  case 2:
  lcd.clear();
   lcd.print(adecvat);
   lcd.print(":tir        ");
   lcd.setCursor(0,1);
   lcd.print("                ");
   othervalue = 4162;
   break;
   case 3:
   lcd.clear();
   lcd.print(adecvat);
   lcd.print(":francais        ");
   lcd.setCursor(0,1);
   lcd.print("                ");
   othervalue = 4163;
   break;
 }
 

 if(value==6261 | value==4213){
  
    value=othervalue;
 }
  
 
 if(value==4161 | value == 6209){
  lcd.clear();
  lcd.print("    1:tanana");
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.write(byte(1));
  lcd.print(" ");
  lcd.write(byte(2));
  lcd.print(" ");
  lcd.write(byte(1));
  
  for (int thisNote = 0; thisNote <8; thisNote++) { // Loop through the notes in the array.
        if(irrecv.decode(&results)){
          value = results.value;
          Serial.println(results.value);
           irrecv.resume();
           break;
           }
    int noteDuration = 1000/noteDurations[thisNote];
    NewTone(TONE_PIN, melody[thisNote], noteDuration); // Play thisNote for noteDuration.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
 }

   if(value==4162 | value == 6210){
    lcd.clear();
  lcd.print("     2:tir");
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.write(byte(1));
  lcd.print(" ");
  lcd.write(byte(2));
  lcd.print(" ");
  lcd.write(byte(1));
   
  for (int thisNote = 0; thisNote < 22; thisNote++) { // Loop through the notes in the array.
    if(irrecv.decode(&results)){
          value = results.value;
          Serial.println(results.value);
           irrecv.resume();
           break;
           }
    int noteDuration = 1000/noteDurations3[thisNote];
    NewTone(TONE_PIN, melody3[thisNote], noteDuration); // Play thisNote for noteDuration.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
   }

   if(value==4163 | value == 6211){
    lcd.clear();
  lcd.print("   3:francais");
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.write(byte(1));
  lcd.print(" ");
  lcd.write(byte(2));
  lcd.print(" ");
  lcd.write(byte(1));
  for (int thisNote = 0; thisNote < 83; thisNote++) { // Loop through the notes in the array.
    if(irrecv.decode(&results)){
          value = results.value;
          Serial.println(results.value);
           irrecv.resume();
           break;
           }
    int noteDuration = 1000/noteDurations4[thisNote];
    NewTone(TONE_PIN, measures[thisNote], noteDuration); // Play thisNote for noteDuration.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
}
  if(value==6230 | value == 4182){
    lcd.clear();
    lcd.print("    stopped");
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.write(byte(1));
  lcd.print(" ");
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.write(byte(1));
        if(irrecv.decode(&results)){
          value = results.value;
          Serial.println(results.value);
           irrecv.resume();
           
        } 
       delay(1000);
  }




  
}
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 2, 3, 4, 5);
int ai, af, bi, bf;
bool a = false, b = false;
void setup() {  
  lcd.begin(16, 2);
  pinMode(A0, INPUT); //a i
  pinMode(A1, INPUT); //a f
  pinMode(A2, INPUT); //b i
  pinMode(A3, INPUT); //b f
 
}  
  
void loop(){
  if(!a){
    if(digitalRead(A0)){
      ai = millis();
      a =  true;
    }
  }
  else{
    if(digitalRead(A1)){
      af = millis();
      a = false;
      lcd.setCursor(0, 0);
      lcd.print(float(af - ai)/1000);
    }
  }

  if(!b){
    if(digitalRead(A2)){
      bi = millis();
      b =  true;
    }
  }
  else{
    if(digitalRead(A3)){
      bf = millis();
      b = false;
      lcd.setCursor(0, 1);
      lcd.print(float(bf - bi)/1000);
    }
  }
}  

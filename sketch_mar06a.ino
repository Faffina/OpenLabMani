#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 2, 3, 4, 5);
int ai, bi, ci, di, af, bf, cf, df;
bool a = false, b = false, c = false, d = false;
int modalita;

void dueConometri(){
  if(!a){
    if(digitalRead(A0)){
      ai = millis();
      a =  true;
    }
  }
  else{
    if(digitalRead(A1)){
      bi = millis();
      a = false;
      lcd.setCursor(3, 0);
      lcd.print(float(bi - ai)/1000);
    }
  }

  if(!b){
    if(digitalRead(A2)){
      ci = millis();
      b =  true;
    }
  }
  else{
    if(digitalRead(A3)){
      di = millis();
      b = false;
      lcd.setCursor(3, 1);
      lcd.print(float(di - ci)/1000);
    }
  }
}

void unConometro(){
  if(!a){
    if(digitalRead(A0)){
      ai = millis();
      a =  true;
    }
  }
  else{
    if(digitalRead(A1)){
      bi = millis();
      a = false;
      lcd.setCursor(3, 0);
      lcd.print(float(bi - ai)/1000);
    }
  }
}

void oscuramento(){
  if(a)
  {
    if(!digitalRead(A0)){
      af = millis();
      lcd.setCursor(3, 0);
      lcd.print(float(af - ai)/1000);
      a = false;
    }
  }
  else
  {
    if(digitalRead(A0))
    {
      ai = millis();
      a = true;
    }
  }
  if(b)
  {
    if(!digitalRead(A1)){
      bf = millis();
      lcd.setCursor(3, 1);
      lcd.print(float(bf - bi)/1000);
      b = false;
    }
  }
  else
  {
    if(digitalRead(A1))
    {
      bi = millis();
      b = true;
    }
  }
  if(c)
  {
    if(!digitalRead(A2)){
      cf = millis();
      lcd.setCursor(3, 2);
      lcd.print(float(cf - ci)/1000);
      c = false;
    }
  }
  else
  {
    if(digitalRead(A2))
    {
      ci = millis();
      c = true;
    }
  }
  if(d)
  {
    if(!digitalRead(A3)){
      df = millis();
      lcd.setCursor(3, 4);
      lcd.print(float(df - di)/1000);
      d = false;
    }
  }
  else
  {
    if(digitalRead(A3))
    {
      di = millis();
      d = true;
    }
  }
}

void print(a, b, c, d){
  lcd.setCursor(0,0);
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print(b);
  lcd.setCursor(0,2);
  lcd.print(c);
  lcd.setCursor(0,3);
  lcd.print(d);
}

void setup() {  
  lcd.begin(16, 2);
  pinMode(A0, INPUT); //a i
  pinMode(A1, INPUT); //a f
  pinMode(A2, INPUT); //b i
  pinMode(A3, INPUT); //b f
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  digitalWrite(8, HIGH);
}  
  
void loop(){
  if(digitalRead(8)){
    menu();
  }
  else{
    switch(modalita){
      case 0:
        print("ab ", "", "", "");
        unConometro();
        break;
      case 1:
        print("ab", "cd", "", "");
        dueConometri();
        break;
      case 2:
        print("a", "b", "c", "d")
        break;
    }
  }
}  
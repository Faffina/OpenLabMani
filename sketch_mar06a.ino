#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned long ai, bi, ci, di, af, bf, cf, df;
bool a = false, b = false, c = false, d = false;
int modalita;
float l1, l2, l3, l4;
int encoderPin1 = 10;
int encoderPin2 = 11;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
String farsi[] = {"sel mod", "uno", "due", "oscu", "v uno", "v due", "v oscu"};

void dueConometri(bool v = false){
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
      lcd.setCursor(0, 0);
      if(!v){lcd.print("a-b "+String(float(bi - ai)/1000, 2)+" s   ");}
      else{lcd.print("a-b "+String(l1/(float(bi - ai)/1000), 2)+" m/s   ");}
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
      lcd.setCursor(0, 1);
      if(!v){lcd.print("c-d "+String(float(di - ci)/1000, 2)+" s   ");}
      else{lcd.print("c-d "+String(l2/(float(di - ci)/1000), 2)+" m/s   ");}
    }
  }
}

void unConometro(bool v = false){
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
      lcd.setCursor(0, 0);
      if(!v){lcd.print("a-b "+String(float(bi - ai)/1000, 2)+" s   ");}
      else{lcd.print("a-b "+String(l1/(float(bi - ai)/1000), 2)+" m/s   ");}
    }
  }
}

void oscuramento(bool v = false){   
  if(a)
  {
    if(!digitalRead(A0)){
      af = millis();
      lcd.setCursor(0, 0);
      if(!v){lcd.print("a "+String(float(af - ai)/1000)+" s   ");}
      else{lcd.print("a "+String(l1/(float(af - ai))/1000)+" m/s   ");}
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
      lcd.setCursor(0, 1);
      if(!v){lcd.print("b "+String(float(bf - bi)/1000)+" s   ");}
      else{lcd.print("b "+String(l2/(float(bf - bi))/1000)+" m/s   ");}
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
      lcd.setCursor(0, 2);
      if(!v){lcd.print("c "+String(float(cf - ci)/1000)+" s   ");}
      else{lcd.print("c "+String(l3/(float(cf - ci))/1000)+" m/s   ");}
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
      lcd.setCursor(0, 3);
      if(!v){lcd.print("d "+String(float(df - di)/1000)+" s   ");}
      else{lcd.print("d "+String(l4/(float(df - di))/1000)+" m/s   ");}
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

void print(String a,String b,String c,String d){
  lcd.setCursor(0,0);
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print(b);
  lcd.setCursor(0,2);
  lcd.print(c);
  lcd.setCursor(0,3);
  lcd.print(d);
}

void sd(){
  String temp = farsi[0]; 
  for(int i=0;i<6;i++) farsi[i] = farsi[i+1]; 
  farsi[6] = temp;
}

void ss()
{
  String temp = farsi[6]; 
  for(int i=6;i>=0;i--) farsi[i+1] = farsi[i];  
  farsi[0] = temp;
}

float seleziona(String info){
  encoderValue = 0;
  lastencoderValue = 0;
  lcd.setCursor(0,0);
  lcd.print(info);
  while(true){
    lcd.setCursor(0,1);
    lcd.print("d = ");
    lcd.print(float(encoderValue)/14.0f);
    lcd.print(" cm ");
    updateEncoder();
    if(digitalRead(3)) break;
  }
  return float(encoderValue)/14.0f;
}

void menu(){
  a = false;
  b = false;
  c = false;
  d = false;
  ai = 0;
  bi = 0;
  ci = 0;
  di = 0; 
  int pos;
  while(true){
    updateEncoder();
    if(lastencoderValue/4 - encoderValue/4 < 0) {pos++; ss();}
    if(lastencoderValue/4 - encoderValue/4 > 0) {pos--; sd();}
    int cur = (abs(pos) % 7) - 1;
    if (cur > 0){
      print("> " + farsi[0], farsi[1], "", "");
      if(digitalRead(3)){
      modalita = cur;
      if(cur < 3) break;
      else{
        if(cur == 3) {l1 = seleziona("dis ta a-b");}
        if(cur == 4) {l1 = seleziona("dis ta a-b");l2 = seleziona("dis ta c-d");}
        if(cur == 3) {l1 = seleziona("dis ta a");l2 = seleziona("dis ta b");l3 = seleziona("dis ta c");l4 = seleziona("dis ta d");}
        break;
      }}
    }
    else{print(farsi[0], farsi[1], "", "");}
  }
}

void updateEncoder(){
  int MSB = digitalRead(10); //MSB = most significant bit
  int LSB = digitalRead(11); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) lastencoderValue = encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) lastencoderValue = encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}

void setup() {  
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
  lcd.begin(16,2);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), menu, RISING);
}  

void loop(){
    switch(modalita){
      case 0:
        unConometro();
        break;
      case 1:
        dueConometri();
        break;
      case 2:
        oscuramento();
        break;
      case 3:
        unConometro(true);
        break;
      case 4:
        dueConometri(true);
        break;
      case 5:
        oscuramento(true);
        break;
    }
} 

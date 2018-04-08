#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // oggetto LiquidCrystal per condrolarre il disaply
unsigned long ai, bi, ci, di, af, bf, cf, df; // valori per calco delle funzioni unConometro, dueConometri osscuramto
bool a = false, b = false, c = false, d = false; // volori logici delle funzioni unConometro, dueConometri osscuramto
int modalita; //valore enum della modalita 
int as = A0, bs = A1, cs = A2, ds = A3, bottone = 10, bswitch = 11, clk = 2, dt = 3; // vlore dei pin
float l1, l2, l3, l4; // distanza inserite da utente salvate k
volatile int lastEncoded = 0; // volore per logica della funzionde updateEncoder
volatile long encoderValue = 0; // valore assoluto delle posizone delle rotary encoded
String Smodalita[] = { "uno     ", "due     ", "oscu    ", "v uno     ", "v due   ", "v oscu   "}; // fataso che descrivonao le diverse modalita

/*mdalita di due conometro, l'argomento v indica se che un distaza inserita dalla utente*/
void dueConometri(bool v = false){
  if(!a){
    if(digitalRead(as)){
      ai = millis();
      a =  true;
    }
  }
  else{
    if(digitalRead(bs)){
      bi = millis();
      a = false;
      lcd.setCursor(0, 0);
      if(!v){lcd.print("a-b "+String(float(bi - ai)/1000, 2)+" s   ");}
      else{lcd.print("a-b "+String(l1/(float(bi - ai)/1000), 2)+" cm/s   ");}
    }
  }

  if(!b){
    if(digitalRead(cs)){
      ci = millis();
      b =  true;
    }
  }
  else{
    if(digitalRead(ds)){
      di = millis();
      b = false;
      lcd.setCursor(0, 1);
      if(!v){lcd.print("c-d "+String(float(di - ci)/1000, 2)+" s   ");}
      else{lcd.print("c-d "+String(l2/(float(di - ci)/1000), 2)+" cm/s   ");}
    }
  }
}

/*mdalita di un conometro, l'argomento v indica se che un distaza inserita dalla utente*/
void unConometro(bool v = false){
  if(!a){
    if(digitalRead(as)){
      ai = millis();
      a =  true;
    }
  }
  else{
    if(digitalRead(bs)){
      bi = millis();
      a = false;
      lcd.setCursor(0, 0);
      if(!v){lcd.print("a-b "+String(float(bi - ai)/1000, 2)+" s   ");}
      else{lcd.print("a-b "+String(l1/(float(bi - ai)/1000), 2)+" cm/s   ");}
    }
  }
}
/*mdalita di osscuramto, l'argomento v indica se che un distaza inserita dalla utente*/
void oscuramento(bool v = false){   
  if(a)
  {
    if(!digitalRead(as)){
      af = millis();
      lcd.setCursor(0, 0);
      if(!v){lcd.print("a "+String(float(af - ai)/1000)+" s   ");}
      else{lcd.print("a "+String(l1/(float(af - ai)/1000))+" cm/s   ");}
      a = false;
    }
  }
  else
  {
    if(digitalRead(as))
    {
      ai = millis();
      a = true;
    }
  }
  if(b)
  {
    if(!digitalRead(bs)){
      bf = millis();
      lcd.setCursor(0, 1);
      if(!v){lcd.print("b "+String(float(bf - bi)/1000)+" s   ");}
      else{lcd.print("b "+String(l2/(float(bf - bi)/1000))+" cm/s   ");}
      b = false;
    }
  }
  else
  {
    if(digitalRead(bs))
    {
      bi = millis();
      b = true;
    }
  }
  if(c)
  {
    if(!digitalRead(cs)){
      cf = millis();
      lcd.setCursor(0, 2);
      if(!v){lcd.print("c "+String(float(cf - ci)/1000)+" s   ");}
      else{lcd.print("c "+String(l3/(float(cf - ci)/1000))+" cm/s   ");}
      c = false;
    }
  }
  else
  {
    if(digitalRead(cs))
    {
      ci = millis();
      c = true;
    }
  }
  if(d)
  {
    if(!digitalRead(ds)){
      df = millis();
      lcd.setCursor(0, 3);
      if(!v){lcd.print("d "+String(float(df - di)/1000)+" s   ");}
      else{lcd.print("d "+String(l4/(float(df - di)/1000))+" cm/s   ");}
      d = false;
    }
  }
  else
  {
    if(digitalRead(ds))
    {
      di = millis();
      d = true;
    }
  }
}

/*seleziona un vaolore foalt per lo spazio utilizando il rotary encoded*/
float seleziona(String info){
  encoderValue = 0; //azeramento dei volori rotary encoded
  lcd.setCursor(0,0); //print di delle informazioni
  lcd.print(info);
  while(true){ //while loop per sgilere la distnza
    lcd.setCursor(0,1);
    lcd.print("d = ");
    lcd.print(float(encoderValue/4)/10.0f); // print della distnza atualle
    lcd.print(" cm ");
    if(!digitalRead(bottone)) break; // uscita delle loop quando vine premuto il bottone delle rotary encoded
  }
  lcd.clear();
  delay(500);
  return float(encoderValue/4)/10.0f; 
}

/*funzione menu per seglier la modalita*/
void menu(){
  a = false; //azzermaento dei datti logoci e di calcolo per impedire errrori
  b = false;
  c = false;
  d = false;
  ai = 0;
  bi = 0;
  ci = 0;
  di = 0; 
  int rel;
  while(true){
    rel = abs(encoderValue / 4) % 6; // valore relativo delle posizone divoso 4 per diminure la volcita
    lcd.setCursor(0,0);
    lcd.print("seleziona mod");
    lcd.setCursor(0,1);
    lcd.print("> " + Smodalita[rel]);
    if(!digitalRead(bottone)){
      delay(500);
      modalita = rel;
      lcd.clear();
      if(rel == 3) l1 = seleziona("dis a-b");
      if(rel == 4) {l1 = seleziona("dis a-b"); l2 = seleziona("dis c-d");}
      if(rel == 5) {l1 = seleziona("dis a"); l2 = seleziona("dis b"); l3 = seleziona("dis c"); l4 = seleziona("dis d");}
      break;
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hai selzioto:");
  lcd.setCursor(0,1);
  lcd.print(Smodalita[rel]);
  delay(1500);
  lcd.clear();
  while(digitalRead(bswitch)){lcd.setCursor(0,0); lcd.print("abbasa l'interutore");}
  lcd.clear();
}

void updateEncoder(){
  int MSB = digitalRead(clk); //MSB = most significant bit
  int LSB = digitalRead(dt); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}
/*dicarazione dei pin e le loro modaita, inzializione delle oggetto lcd e Serial(opzionale per test)*/
void setup() {  
  //Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(as, INPUT); 
  pinMode(bs, INPUT); 
  pinMode(cs, INPUT); 
  pinMode(ds, INPUT); 
  pinMode(bottone, INPUT);
  pinMode(bswitch, INPUT);
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  attachInterrupt(digitalPinToInterrupt(clk), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dt), updateEncoder, CHANGE);
}  

void loop(){
  if(digitalRead(bswitch)) menu();//apre il menu se il switch e alto
  switch(modalita){ //seleziona la modalita e chiama la rispetiva funzionne
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
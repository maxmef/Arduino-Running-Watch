/* Lcd shift register pin layout 
 *  the com port is positive when high
                  
                __1_
             6 |    | 2   
               |_7__|
             5 |    | 3
               |____|
                 4 
LSBFIRST!!!
*/
int CLOCK = 7;
int DATA = 5;
int LATCH = 6;
int comPin = 3;
int colon = 4;
boolean onetime = false;
int SPEAKER = 2;

boolean StartStop = false;   // false = stop, true = start
int SSBUTTON = 10; // interrupt 1 
boolean lastSS = LOW;
boolean currentSS = LOW;


int CLEARBUTTON = 11;
boolean lastC = LOW;
boolean currentC = LOW;



int numbers[10][2] = {
  {B00000010,B11111100}, //0
  {B10011110,B01100000}, //1
  {B00100100,B11011010}, //2
  {12,242}, //3
  {152,102}, //4
  {B01001000,B10110110}, //5
  {64,190}, //6
  {30,224}, //7
  {0,254}, //8
  {B00001000,B11110110},  //9
};
int i = 0;
int j = 0;
int k = 0;
int l = 0;


void setup() 
{
 pinMode(CLOCK,OUTPUT);
 pinMode(DATA,OUTPUT);
 pinMode(LATCH,OUTPUT);
 pinMode(comPin,OUTPUT);
 pinMode(colon,OUTPUT);
 pinMode(SSBUTTON,INPUT);

Serial.begin(9600);
attachInterrupt(SSBUTTON, startStop, FALLING);
 
}
boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if(last != current)
  {
    delay(10);
    current = digitalRead(pin);
  }

  return current;
}
void loop() 
{
  for(i=0; i<10; i++)
  {
 
 
  setDigit(numbers[i][0], numbers[i][1], numbers[j][0], numbers[j][1],numbers[k][0], numbers[k][1],numbers[l][0], numbers[l][1]);
             

    Serial.println(i);
    Serial.println(j);
    Serial.println(k);
    Serial.println(l); 
    Serial.println(             );      
   
           
  }
  j++;
  if(j==6)
  {
   j=0;
   k++;
  }
  if(k==2)
  {
    k = 0;
  }
}
 
void setDigit(int posDigit1, int negDigit1, int posDigit2, int negDigit2,
int posDigit3, int negDigit3, int posDigit4, int negDigit4)
{
 int x = 0;
  while(x<10)
  {
    if( x>= 5 && StartStop == true)
    {
      digitalWrite(colon, HIGH);
    }
    else
    {
      digitalWrite(colon,LOW);
    }
    digitalWrite(comPin,HIGH);
    digitalWrite(LATCH,LOW);
    shiftOut(DATA, CLOCK,LSBFIRST, posDigit1);
    shiftOut(DATA, CLOCK,LSBFIRST, posDigit2);
    shiftOut(DATA, CLOCK,LSBFIRST, posDigit3);
    shiftOut(DATA, CLOCK,LSBFIRST, posDigit4);
    digitalWrite(LATCH,HIGH);
    
    delay(50);
    if(x >= 5 && StartStop == true)
    {
      digitalWrite(colon, LOW);
    }
    else
    {
      digitalWrite(colon, HIGH);
    }
    digitalWrite(comPin,LOW);
    digitalWrite(LATCH,LOW);
    shiftOut(DATA, CLOCK,LSBFIRST, negDigit1);
    shiftOut(DATA, CLOCK,LSBFIRST, negDigit2);
    shiftOut(DATA, CLOCK,LSBFIRST, negDigit3);
    shiftOut(DATA, CLOCK,LSBFIRST, negDigit4);
    digitalWrite(LATCH,HIGH);
    
    delay(50);

    currentSS = debounce(lastSS, SSBUTTON);
    if(lastSS == LOW && currentSS == HIGH)
    {
      StartStop = !StartStop;
      tone(SPEAKER, 4000);
      delay(15);
      noTone(SPEAKER);
    }
    
    if(StartStop == true)
    {
      x++;
    }
    if(StartStop == false)
    {
     currentC = debounce(lastC, CLEARBUTTON);
    if(lastC == LOW && currentC == HIGH)
    {
      tone(SPEAKER,4000);
      delay(15);
      noTone(SPEAKER);
      
      
      posDigit1 = numbers[0][0];
      negDigit1 = numbers[0][1];
      i=0;
      posDigit2 = numbers[0][0];
      negDigit2 = numbers[0][1];
      j=0;
      posDigit3 = numbers[0][0];
      negDigit3 = numbers[0][1];
      k=0;
      posDigit4 = numbers[0][0];
      negDigit4 = numbers[0][1];
      l=0;
      x=0;
      
    }
  }
    
     
   
      
    }
  }


void clearLcd(int pin, int startStopState)
{
  
}


    
  
  
  
  

  
 
 

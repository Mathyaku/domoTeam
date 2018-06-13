/*

*/
#include <IRremote.h>

// variables
const int ButtonCena1 = A0;
const int ButtonCena2 = A1;

const int DimmerCopa = A5;
const int DimmerSala = A4;

const int LedCozinha = 7;
const int LedCorredor = 8;
const int LedSala = 9;
const int LedCopa = 10;

const int Motor1  = 5;
const int Motor2  = 6;

//states
int buttonCena1State = 0; // Entretenimento
int buttonCena2State = 0; // Jantar

//IR communication
int Receiver = 11;

IRrecv irrecv(Receiver);
IRsend irsend;
 
decode_results results;


void setup() {
    //Receiver Configuration
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    
    //Pin Setups
    pinMode(ButtonCena1, INPUT);
    pinMode(ButtonCena2, INPUT);
    
    pinMode(LedCorredor, OUTPUT);
    pinMode(LedSala, OUTPUT);
    pinMode(LedCopa, OUTPUT);
    pinMode(LedCozinha, OUTPUT);
    
    pinMode(DimmerSala, INPUT);
    pinMode(DimmerCopa, INPUT);
    
    pinMode(Motor1, OUTPUT);
    pinMode(Motor2, OUTPUT);
    
    // init variables
    analogWrite(LedSala, 255);
    analogWrite(LedCopa, 255);
    digitalWrite(LedCozinha, LOW);
    digitalWrite(LedCorredor, LOW);
}

void loop() {
  buttonCena1State = analogRead(ButtonCena1);
  buttonCena2State = analogRead(ButtonCena2);
  
  if (irrecv.decode(&results)) {
    Serial.print("Protocal: ");
    Serial.println(results.decode_type, DEC);
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
  
  if(buttonCena1State)
  {
    //iluminação
    analogWrite(LedSala, 76); //255*0.3
    analogWrite(LedCopa, 0);
    digitalWrite(LedCozinha, HIGH);
    digitalWrite(LedCorredor, HIGH);
    
    // persianas
    analogWrite(Motor1, 200);
    analogWrite(Motor2, 0);
    
    //Liga TV
    if (Serial.read()!= -1){
      irsend.sendSony(0xa90, 12);
      Serial.print("Sent Sony TV ");
    }
    
    //Liga Home Theather
    if (Serial.read()!= -1){
      irsend.sendNEC(0x00ff01fe, 32);
      Serial.print("Sent NEC Home Theater ");
    }
    
  }
  
  if(buttonCena2State)
  {
    //iluminação
    analogWrite(LedSala, 0);
    analogWrite(LedCopa, 178); //255*0.7
    digitalWrite(LedCozinha, HIGH);
    digitalWrite(LedCorredor, HIGH);
    
    // persianas
    analogWrite(Motor1, 0);
    analogWrite(Motor2, 200);
    
    //Liga Home Theather
    if (Serial.read()!= -1){
      irsend.sendNEC(0x00ff01fe, 32);
      Serial.print("Sent NEC Home Theater ");
    }
  }
    
}

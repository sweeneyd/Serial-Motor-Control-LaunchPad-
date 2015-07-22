const int ledPin = P1_0;
const int M3 = P1_3;
const int M4 = P1_4;
const int speedCtrl = P2_1;
float dutyCycle = 0;
float ledDuty = 0;

void setup(){
  // setup serial comms
  Serial.begin(9600);
  
  // setup PWM control pin
  pinMode(ledPin, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(speedCtrl, OUTPUT);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  analogWrite(speedCtrl, 0);
}

void loop(){
  if(Serial.available()){
    int ch = Serial.read();
    if(isDigit(ch)){
      dutyCycle = map(ch, '0', '9', 0, 255);
      ledDuty = map(ch, '0', '9', 0, 255);
      analogWrite(speedCtrl, dutyCycle);
      analogWrite(ledPin, ledDuty);
      Serial.print("Motor Speed: ");
      Serial.print(ch-48);
      Serial.print("\n");
    }
    else{
      Serial.println("Motor shutdown");
      analogWrite(speedCtrl, 0);
      
    }
  }
}

void serialEvent() {
  

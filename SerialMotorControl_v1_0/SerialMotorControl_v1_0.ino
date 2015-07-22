/* 
  ==============================================================================
  SERIAL MOTOR CONTROL v1.0
  For use with the MSP430 Launchpad Motor Control BoosterPack
  Link: http://store.43oh.com/index.php?route=product/product&path=64&product_id=103
  
  Adaptation of Serial Event example (Sean Alvarado, 2013)/(Igoe, 2011)
  Created 29 September 2014
  by Dan Sweeney (Virginia Tech SBES)
  
  Last Updated: 22 July 2015
  ==============================================================================
*/ 

// GLOBAL VARIABLES
String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

const int M3 = P1_3;
const int M4 = P1_4;
const int speedCtrl = P2_1;

// FUNCTIONS ===================================================================

// Interprets duty cycle;
void dutyCycle (String inputString) {
  int dutyCycle = inputString.substring(1, 5).toInt();
  if (dutyCycle > 255) {
    Serial.println("Duty cycle out of range: too large.");
    Serial.println("Duty cycle set to 255.");
    dutyCycle = 255;
  }
  else if (dutyCycle < 0) {
    Serial.println("Duty cycle out of range: too small.");
    Serial.println("Duty cycle set to 0.");
    dutyCycle = 0;
  }
  else {
    Serial.print("Duty cycle: ");
    Serial.println(dutyCycle);
//    digitalWrite(speedCtrl, LOW);
    analogWrite(speedCtrl, dutyCycle);
  }
  Serial.println();
}

// Sets motor direction
void motorDir(String inputString) {
  switch (inputString[0]) {
      // Forward direction
      case 'F':
        // Set direction of Motor
        digitalWrite(M3, HIGH);
        digitalWrite(M4, LOW);
        Serial.println("Direction: Forward");
        break;
        
      // Reverse direction
      case 'R':
        // Set direction of Motor
        digitalWrite(M3, LOW);
        digitalWrite(M4, HIGH);
        Serial.println("Direction: Reverse");
        break;
        
      // Incorrect input or Quit
      default:
        digitalWrite(M3, LOW);
        digitalWrite(M4, LOW);
        Serial.println("Input only F (forward) or R (reverse).");
        Serial.println("Communication protocol: [D000]");
        
    }
}

// SETUP =======================================================================
void setup() {
  // setup pins
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(speedCtrl, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

// LOOP ========================================================================
void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    //set motor direction
    motorDir(inputString);
    
    // Set duty cycle
    dutyCycle(inputString);
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

// SERIAL EVENT ================================================================
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
    stringComplete = true;
    } 
  }
}

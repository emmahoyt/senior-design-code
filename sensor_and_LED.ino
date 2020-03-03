
// THIS program should read high or low from sensor, turn on or off led. Based on led the motor runs or not.
// WITH ODD NUMBER OF BUTTON PUSHES THE MOTOR SHOULD BE ON AND WITH EVEN NUMBER OF BUTTON PUSHES THE MOTOR SHOULD BE OFF

// defines pins numbers

int runtime = 1; // time to run motor in seconds


const int buttonPin = 2;     // the number of the pushbutton pin
const int stepPin = 9;
const int dirPin = 8;
int ledPin = 7;  // LED connected to digital pin 13
int inPin = A0;    // pushbutton connected to digital pin 7 (A0) (high or low sensor)
int val = 0;      // variable to store the read value
bool runflag = true;
int buttonstate = 0; // variable for reading the pushbutton status
//int buttonPresses = 0;
//int buttonPress = 0;
bool buttondummy = false;
bool sensordummy = false;


#include <Servo.h> // servo position
Servo myservo;
int pos = 0;
//int picpos = 26;  // variable to store the servo position

void setup() {
  // Sets the two pins as Outputs
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  pinMode(inPin, INPUT);    // sets the digital pin A0 as input

  myservo.attach(11);
  myservo.write(0);
  delay(15);
  askquestion();
 
    // initialize the pushbutton pin as an input:
     pinMode(buttonPin, INPUT_PULLUP);
     
      
}
void loop() {

  val = digitalRead(inPin);   // read the input pin
  //digitalWrite(ledPin, val);  // sets the LED to the button's value

  //should turn motor on

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);
       Serial.println("don't run motor");
    runflag = true;
  }

  else {
sensordummy = true;
  }
    while (sensordummy == true){
    digitalWrite(ledPin, LOW);
    delay(10);

    digitalWrite(dirPin, HIGH);
    // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
     Serial.println("run motor");
    if (runflag) {
      runflag = false;
      unsigned long tstart = millis();
      Serial.println(tstart);
      while ((millis() - tstart) < (runtime * 1000)) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
        sensordummy = false;
      }
    }
    }
buttonstate = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonstate == LOW) {
    // turn motor on:
    
    buttondummy = true;
    }
    
  else if (buttonstate == HIGH) {
    
    // motor is off:
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);
  }
    while (buttondummy == true){
     digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
    buttondummy = false;
  }
  }
}
  



        
    
  
//buttonstate = digitalRead(buttonPin);
//
//  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//  if (buttonstate == LOW) {
//    // turn motor on:
//    
//    dummy = true;
//    }
//    
//  else if (buttonstate == HIGH) {
//    
//    // motor is off:
//    digitalWrite(dirPin, LOW);
//    digitalWrite(stepPin, LOW);
//  }
//    while (dummy == true){
//     digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
//  // Makes 200 pulses for making one full cycle rotation
//  for(int x = 0; x < 200; x++) {
//    digitalWrite(stepPin,HIGH); 
//    delayMicroseconds(500); 
//    digitalWrite(stepPin,LOW); 
//    delayMicroseconds(500); 
//    dummy = false;
//  }
//  }
//  
  


void askquestion() {
  Serial.println("What size filament is it?");
  Serial.println("Enter a for 1.75 and b for 2.85.");
  while (Serial.available() == 0) { //has the code wait for input
  }

  char ans = Serial.read();

  if (ans == 'a') {                 //if user enters a it will run 1.75 filament code
    Serial.println("You seleced 1.75.");
    myservo.write(90);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position



  } else if (ans == 'b') {
    Serial.println("You selected 2.85.");
    // set servo to whatever
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position



  } else {
    Serial.println("Didn't understand.");
    Serial.println();
    delay(10);
    purgeinput();
    askquestion();
  }

}

void purgeinput() {
  while (Serial.read() > -1) {
  }
}

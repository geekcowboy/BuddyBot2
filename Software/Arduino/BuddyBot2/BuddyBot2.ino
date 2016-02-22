#include <Servo.h>
#include <SoftwareSerial.h>


#define LaserPin 7
#define RXpin 10
#define TXpin 11
#define XServoPin 5
#define YServoPin 6
#define moveAmt 20

int Xpos = 90;
int Ypos = 90;
char BluetoothData;

Servo XServo, YServo;
SoftwareSerial HC(RXpin, TXpin);

void setup() {
  Serial.begin(9600);
  delay(5000);

  // put your setup code here, to run once:
  pinMode(LaserPin, OUTPUT);
  pinMode(RXpin, INPUT);
  pinMode(TXpin, OUTPUT);

  digitalWrite(LaserPin, LOW);

  XServo.attach(XServoPin);
  YServo.attach(YServoPin);
  XServo.write(90);
  delay(5);
  YServo.write(90);
  delay(5);

  HC.begin(9600);
  Serial.println("BuddyBot 2.0 initialized....");
}

void loop() {
  if (HC.available()) {
    BluetoothData = HC.read();
    Serial.println(BluetoothData);
    switch (BluetoothData) {
      
      case 'a':
        digitalWrite(LaserPin, LOW);
        break;
        
      case 'b':
        digitalWrite(LaserPin, HIGH);
        break;
        
      case 'c':  // increment, move left
        Xpos += moveAmt;
        if (Xpos >= 0) {
          XServo.write(Xpos);
          delay(5);
        }
        else {
          Xpos = 0;
        }
        break;
        
      case 'd': // decrement, move right
        Xpos -= moveAmt;
        if (Xpos <= 180) {
          XServo.write(Xpos);
          delay(5);
        }
        else {
          Xpos = 180;
        }
        break;

      case 'e':  // decrement, move up
        Ypos -= moveAmt;
        if (Ypos >= 0) {
          YServo.write(Ypos);
          delay(5);
        }
        else {
          Ypos = 0;
        }
        break;
        
      case 'f': // increment, move down
        Ypos += moveAmt;
        if (Ypos <= 180) {
          YServo.write(Ypos);
          delay(5);
        }
        else {
          Ypos = 180;
        }
        break;
        
      default:
        break;
    }
    delay(100);
  }
}


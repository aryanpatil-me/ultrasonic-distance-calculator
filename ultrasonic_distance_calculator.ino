// Libraries
#include <LiquidCrystal.h>

// Variables
// for Ultrasonic distance (HC-SR04) sensor
int tiltPin = 2;
int echoPin = 3;
int pingTravelTime;
float pingTravelDist;
float targetDist;
int microSec = 10;
int delayTime = 50;
// for lcd display
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
int wait = 3000;
// creating object for library
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// for button
int buttonPin = A0;
int buttonVal;
// variables for 'for' loop...makes the measurement more accurate.
int numMeas=50;
float avgDist;
float distSum = 0;

void setup() {
  // setting pinModes for pins
  pinMode(tiltPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);  // using internal pull up resistor.
  // starting lcd display
  lcd.begin(16, 2);
  // starting serial monitor
  Serial.begin(9600);
}

void loop() {
  buttonVal = digitalRead(buttonPin);
  // Printing instructions for user.
  lcd.setCursor(0, 0);
  lcd.print("Point the Target!");
  lcd.setCursor(0, 1);
  lcd.print("Push the button!");
  // waiting for user to press button...
  while(buttonVal == 1){
    buttonVal = digitalRead(buttonPin);
  }
  // calculating the measurements for accurate measurement.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Measuring...");
  for(int i=1;i<=numMeas;i+=1){
  digitalWrite(tiltPin, LOW);
  delayMicroseconds(microSec);
  digitalWrite(tiltPin, HIGH);
  delayMicroseconds(microSec);
  digitalWrite(tiltPin, LOW);
  pingTravelTime = pulseIn(echoPin, HIGH);
  pingTravelDist = ((pingTravelTime * 767. * 5280. * 12.) / (3600. * 1000000.));
  targetDist = pingTravelDist / 2;
  delay(delayTime);
  distSum = distSum + targetDist;
  }
  avgDist = distSum / numMeas;
  // printing the final output on lcd screen.
  Serial.println(avgDist);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Avg. Target Dist.");
  lcd.setCursor(0, 1);
  lcd.print(avgDist);
  lcd.print(" inches");
  delay(wait);

  distSum = 0; // finally making distSum = 0...so that it do not store the old values.
}

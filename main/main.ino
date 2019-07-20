/*
   Nayalash Mohammad
   main.ino
   
   Libraries Needed
   Adafruit GFX Library
   Adafruit_SSD1306
   
*/

//OLED DISPLAY LIBRARIES
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//prox pins
int proxLed = 8;
int trigPin = 9;
int echoPin = 10;

//shock pins
int shockLed = 6;
int shock = 7;
int shockVal;

//tilt pins
int tiltLed = 4;
int tilt = 5;
int tiltVal;

void setup() {
  //prox
  pinMode(proxLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //shock
  pinMode(shockLed, OUTPUT);
  pinMode(shock, INPUT);
  //tilt
  pinMode(tiltLed, OUTPUT);
  pinMode(tilt, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
}
void loop() {
  display.display();
  proxSensor();
  shockSensor();
  tiltSensor();
}

void tiltSensor() {
  tiltVal = digitalRead(tilt);
  if (tiltVal == HIGH) { // if sensor is tilted
    Serial.print("Towing"); //SerialPrint "Towing"
    digitalWrite(tiltLed, HIGH);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(5, 0);
    display.print("Car Being Towed"); // LCD Print
  } else {
    digitalWrite(tiltLed, LOW);
  }
}

void shockSensor() {

  shockVal = digitalRead(shock);
  if (shockVal == HIGH ) { // if sensor is vibrated
    Serial.print("Breakin ");
    digitalWrite(shockLed, HIGH);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(5, 0);
    display.print("Car Breakin Detected");
  } else {
    digitalWrite (shockLed, LOW);
  }
}


void proxSensor() {
  long duration;
  int distance;


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
//  Serial.print("Distance: ");
//  Serial.println(distance);

  if (distance < 5) {
    Serial.print("Loitering ");
    digitalWrite(proxLed, HIGH);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(5, 0);
    display.print("Car Loitering Alert");

  } else {
    digitalWrite (proxLed, LOW);
  }
}
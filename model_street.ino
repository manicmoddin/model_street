#include <Adafruit_NeoPixel.h>
int tRed = D1;   
int tAmber = D2; 
int tGreen = D3;
int pButton = D4;
int streetLight = D5;
int pRed = D6;
int pGreen = D7;
int pWait = D8;
int lightSensor = A0;

int lightDelay = 1500;
int pWantingToCross = 0;
int lightLevel = 0;

int state = 0;

unsigned long lastmillis = 0;

Adafruit_NeoPixel streetLights(4, streetLight, NEO_GRB + NEO_KHZ800);

void redAmber() {
  //serial.println("Red & Amber");
  digitalWrite(tRed, HIGH);
  digitalWrite(tAmber, HIGH);
  digitalWrite(tGreen, LOW);
}

void green() {
  //serial.println("Green");
  digitalWrite(tRed, LOW);
  digitalWrite(tAmber, LOW);
  digitalWrite(tGreen, HIGH);
}

void amber() {
  //serial.println("Amber");
  digitalWrite(tRed, LOW);
  digitalWrite(tAmber, HIGH);
  digitalWrite(tGreen, LOW);
  state = 1;
}

void red() {
  //serial.println("Red");
  digitalWrite(tRed, HIGH);
  digitalWrite(tAmber, LOW);
  digitalWrite(tGreen, LOW);
}

void pedestrianWait() {
  //serial.println("P Wait");
  digitalWrite(pWait, HIGH);
  digitalWrite(pRed, HIGH);
  digitalWrite(pGreen, LOW);
}

void pedestrianRed() {
  //serial.println("P Red");
  digitalWrite(pWait, LOW);
  digitalWrite(pRed, HIGH);
  digitalWrite(pGreen, LOW);
}

void pedestrianGreen() {
  //serial.println("P Green");
  digitalWrite(pWait, LOW);
  digitalWrite(pRed, LOW);
  digitalWrite(pGreen, HIGH);
}

ICACHE_RAM_ATTR void wantingToCross() {
  //serial.println("Wanting to Cross");
  //digitalWrite(led, HIGH);
  pWantingToCross = 1;
}

void setup() {
  Serial.begin(115200);
  streetLights.begin();
  streetLights.fill(streetLights.Color(0,0,0));
  streetLights.show(); // Initialize all pixels to 'off'
  pinMode(tRed,OUTPUT);   
  pinMode(tAmber,OUTPUT); 
  pinMode(tGreen,OUTPUT); 
  pinMode(pRed, OUTPUT);
  pinMode(pGreen, OUTPUT);
  pinMode(pWait, OUTPUT);
  // pinMode(streetLight, OUTPUT);
  pinMode(pButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pButton), wantingToCross, RISING);

  // Default to red being on
  red();

  // Default to streetlights being off
  streetLights.fill(0x000);

  // Default to Pedestrian being Red
  pedestrianRed();
}

void loop(){
  unsigned long now = millis();
  if (pWantingToCross == 1) {
    pedestrianWait();
    
    if ((now - lastmillis >= lightDelay) && (state == 0)){
      //serial.println("Turning on Amber");
      amber();
      lastmillis = now;
      state = 1;
    }
    
    if ((now - lastmillis >= lightDelay) && (state == 1)){
      //serial.println("Turning on Red");
      red();
      delay(1000);
      pedestrianGreen();
      lastmillis = now;
      state = 2;
    }

    if ((now - lastmillis >= (lightDelay * 6)) && (state == 2)){
      //serial.println("Turning on P Red");
      pedestrianRed();
      redAmber();
      lastmillis = now;
      state = 3;
    }

    if ((now - lastmillis >= lightDelay ) && (state == 3)){
      //serial.println("Turning on Green");

      green();
      lastmillis = now;
      state = 0;
      pWantingToCross = 0;
    }

     
  }
  else { 
    green();
  }
  lightLevel = analogRead(lightSensor);
  if (lightLevel <= 200) {
    // Serial.println("Lights on");
    streetLights.fill(streetLights.Color(255,255,255));
    streetLights.show();
  }
  
  else {
    //serial.println("Lights Off");
    streetLights.fill(streetLights.Color(0,0,0));
    streetLights.show();
  }
}
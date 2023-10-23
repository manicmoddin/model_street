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

void redAmber() {
  digitalWrite(tRed, HIGH);
  digitalWrite(tAmber, HIGH);
  digitalWrite(tGreen, LOW);
}

void green() {
  digitalWrite(tRed, LOW);
  digitalWrite(tAmber, LOW);
  digitalWrite(tGreen, HIGH);
}

void amber() {
  digitalWrite(tRed, LOW);
  digitalWrite(tAmber, HIGH);
  digitalWrite(tGreen, LOW);
}

void red() {
  digitalWrite(tRed, HIGH);
  digitalWrite(tAmber, LOW);
  digitalWrite(tGreen, LOW);
}

void pedestrianWait() {
  digitalWrite(pWait, HIGH);
  digitalWrite(pRed, HIGH);
  digitalWrite(pGreen, LOW);
}

void pedestrianRed() {
  digitalWrite(pWait, LOW);
  digitalWrite(pRed, HIGH);
  digitalWrite(pGreen, LOW);
}

void pedestrianGreen() {
  digitalWrite(pWait, LOW);
  digitalWrite(pRed, LOW);
  digitalWrite(pGreen, HIGH);
}

ICACHE_RAM_ATTR void wantingToCross() {
  Serial.println("Wanting to Cross");
  //digitalWrite(led, HIGH);
  pWantingToCross = 1;
}

void setup() {
  Serial.begin(115200);
  pinMode(tRed,OUTPUT);   
  pinMode(tAmber,OUTPUT); 
  pinMode(tGreen,OUTPUT); 
  pinMode(pRed, OUTPUT);
  pinMode(pGreen, OUTPUT);
  pinMode(pWait, OUTPUT);
  pinMode(streetLight, OUTPUT);
  pinMode(pButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pButton), wantingToCross, RISING);

  // Default to red being on
  red();

  // Default to streetlights being off
  digitalWrite(streetLight, LOW);

  // Default to Pedestrian being Red
  pedestrianRed();
}

void loop(){
  if (pWantingToCross == 1) {
    pedestrianWait();
    delay(lightDelay);
    amber();
    delay(lightDelay);
    red();
    pedestrianGreen();
    delay(lightDelay*6);
    pedestrianRed();
    redAmber();
    delay(lightDelay);
    pWantingToCross = 0;
  }
  green();
  lightLevel = analogRead(lightSensor);
  if (lightLevel <= 200) {
    //Serial.println("Lights on");
    digitalWrite(streetLight, HIGH);
  }
  else {
    //Serial.println("Lights Off");
    digitalWrite(streetLight, LOW);
  }
}
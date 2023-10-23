int tRed = D1;   
int tAmber = D2; 
int tGreen = D3;
int pButton = D4;

int lightDelay = 1500;
int pWantingToCross = 0;

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
  pinMode(pButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pButton), wantingToCross, RISING);

  // Default to red being on
  red();
}

void loop(){
  if (pWantingToCross == 1) {
    delay(lightDelay);
    amber();
    delay(lightDelay);
    red();
    delay(lightDelay*6);
    redAmber();
    delay(lightDelay);
    pWantingToCross = 0;
  }
  green();
}
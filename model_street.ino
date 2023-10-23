int tRed = D1;   
int tAmber = D2; 
int tGreen = D3; 

int lightDelay = 1500; 

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

void setup() {
  pinMode(tRed,OUTPUT);   
  pinMode(tAmber,OUTPUT); 
  pinMode(tGreen,OUTPUT); 

  // Default to red being on
  red();
}

void loop(){
  red();
  delay(lightDelay*4);
  redAmber();
  delay(lightDelay);       
  green();  
  delay(lightDelay*4);          
  amber();
  delay(lightDelay);    
}
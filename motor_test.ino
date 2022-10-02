int motorApin1 = 30; //IN1
int motorApin2 = 12; //IN2
int motorAspeed = 13; //ENA
int motorBpin1 = 11; //IN3
int motorBpin2 = 32; //IN4
int motorBspeed = 10; //ENB
int motorCpin1 = 34; //IN3
int motorCpin2 = 8; //IN4
int motorCspeed = 9; //ENB
int motorDpin1 = 7; //IN3
int motorDpin2 = 36; //IN4
int motorDspeed = 6; //ENB
int motorEpin1 = 38; //IN3
int motorEpin2 = 4; //IN4
int motorEspeed = 5; //ENB
int motorFpin1 = 3; //IN3
int motorFpin2 = 40; //IN4
int motorFspeed = 2; //ENB
int speed = 500; //speeds above 150


void setup() {
  // put your setup code here, to run once:
  pinMode(motorApin1, OUTPUT);
  pinMode(motorApin2, OUTPUT);
  pinMode(motorAspeed, OUTPUT);
  pinMode(motorBpin1, OUTPUT);
  pinMode(motorBpin2, OUTPUT);
  pinMode(motorBspeed, OUTPUT);
  pinMode(motorCpin1, OUTPUT);
  pinMode(motorCpin2, OUTPUT);
  pinMode(motorCspeed, OUTPUT);
  pinMode(motorDpin1, OUTPUT);
  pinMode(motorDpin2, OUTPUT);
  pinMode(motorDspeed, OUTPUT);
  pinMode(motorEpin1, OUTPUT);
  pinMode(motorEpin2, OUTPUT);
  pinMode(motorEspeed, OUTPUT);
  pinMode(motorFpin1, OUTPUT);
  pinMode(motorFpin2, OUTPUT);
  pinMode(motorFspeed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
  digitalWrite(motorApin1, HIGH);
  digitalWrite(motorApin2, LOW);
  analogWrite(motorAspeed, speed);
  
  digitalWrite(motorBpin1, HIGH);
  digitalWrite(motorBpin2, LOW);
  analogWrite(motorBspeed, speed);
  
  digitalWrite(motorCpin1, HIGH);
  digitalWrite(motorCpin2, LOW);
  analogWrite(motorCspeed, speed);
  
  digitalWrite(motorDpin1, HIGH);
  digitalWrite(motorDpin2, LOW);
  analogWrite(motorDspeed, speed);
  
  digitalWrite(motorEpin1, HIGH);
  digitalWrite(motorEpin2, LOW);
  analogWrite(motorEspeed, speed);
  
  digitalWrite(motorFpin1, HIGH);
  digitalWrite(motorFpin2, LOW);
  analogWrite(motorFspeed, speed);
  //delay(1000);

  //digitalWrite(motorApin1, LOW);
  //digitalWrite(motorApin2, HIGH);
  //analogWrite(motorAspeed, speed);
  
  //digitalWrite(motorBpin1, LOW);
  //digitalWrite(motorBpin2, HIGH);
  //analogWrite(motorBspeed, speed);
  
  //digitalWrite(motorCpin1, LOW);
  //digitalWrite(motorCpin2, HIGH);
  //analogWrite(motorCspeed, speed);
  
  //digitalWrite(motorDpin1, LOW);
  //digitalWrite(motorDpin2, HIGH);
  //analogWrite(motorDspeed, speed);
  
  //digitalWrite(motorEpin1, LOW);
  //digitalWrite(motorEpin2, HIGH);
  //analogWrite(motorEspeed, speed);
  
  //digitalWrite(motorFpin1, LOW);
  //digitalWrite(motorFpin2, HIGH);
  //analogWrite(motorFspeed, speed);
  //delay(1000);
  
}


// display screen
#include <LiquidCrystal.h>

// dissolved o2 sensor
#include <do_grav.h>

// temperature sensors
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A14
#define TWO_WIRE_BUS A0

// constants
#define MIN_PH 6.5
#define MAX_PH 7.5
#define IDEAL_TEMP 37

// feeding constants: Fi = Vo * u * exp(u * t)
#define Rf 7 // rate of flow thru feed tube, unit: mL/sec
#define Vo 1000 // initial e coli volume, unit: mL
#define u 0.0150515
#define cycleLen 5000 // feed intervals are every 300 loops (50 loops = 1min 45s, 300 = 10.5min, 5000 ~ 3hrs)
int curIntervA = 0;
int curIntervB = 0;

int counterA = 1;
int counterB = 1;


// button vars
const int buttonPinA = 2;
const int buttonPinB = 3;
int buttonStateA;
int buttonStateB;

// CONTROLS
bool stpA = true;
bool stpB = true;

// left chamber
const int sensorpHA = A15;
const int sensorTempA = A14;
const int motorSpeedA = 6; // stirring
const int motorDir1A = 36; // right
const int motorDir2A = 37; // left
const int baseSpeedA = 9; // right pink lid
const int baseDir1A = 30; // right
const int baseDir2A = 31; // left
const int outflowSpeedA = 8; // left pink lid
const int outflowDir1A = 32; // right 
const int outflowDir2A = 33; // left
const int feedSpeedA = 7; // blue lid
const int feedDir1A = 34; // right
const int feedDir2A = 35; // left

// right chamber
const int sensorpHB = A1;
const int sensorTempB = A12;
const int motorSpeedB = 13; // stirring
const int motorDir1B = 24; // right
const int motorDir2B = 25; // left
const int baseSpeedB = 11; // right pink lid
const int baseDir1B = 26; // right
const int baseDir2B = 27; // left
const int outflowSpeedB = 10; // left pink lid
const int outflowDir1B = 28; // right 
const int outflowDir2B = 29; // left
const int feedSpeedB = 12; // blue lid
const int feedDir1B = 22; // right
const int feedDir2B = 23; // left

// values
float pHA = 0;
float pHB = 0;
const int speed = 255;

int sensorO2 = A13;
Gravity_DO DO = Gravity_DO(sensorO2);

uint8_t user_bytes_received = 0;
const uint8_t bufferlen = 32;
char user_data[bufferlen];

const int rs = 48, en = 49, d4 = 52, d5 = 53, d6 = 50, d7 = 51;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensorA(&oneWire); 
OneWire twoWire(TWO_WIRE_BUS);
DallasTemperature tempSensorB(&twoWire); 

void parse_cmd(char* string) {
  strupr(string);
  String cmd = String(string);
  if(cmd.startsWith("CAL")){
    int index = cmd.indexOf(',');
    if(index != -1){
      String param = cmd.substring(index+1, cmd.length());
      if(param.equals("CLEAR")){
        DO.cal_clear();
        Serial.println("CALIBRATION CLEARED");
      }
    }
    else{
      DO.cal();
      Serial.println("DO CALIBRATED");
    }
  }
}

void setup() {
    // execute once
    Serial.begin(9600); 
    Serial.println("Bioreactor Test"); 
    // start up o2 sensor
    Serial.println(F("Use command \"CAL\" to calibrate the circuit to 100% saturation in air\n\"CAL,CLEAR\" clears the calibration"));
    if(DO.begin()){
      Serial.println("Loaded EEPROM");
    }
    // start display
    lcd.begin(16, 2);
    lcd.print("First line");
    lcd.setCursor(0,1);
    lcd.print("Second line");
    // Start up temperature sensor
    tempSensorA.begin(); 
    tempSensorB.begin(); 

//     control button
    pinMode(buttonPinA, INPUT);
    pinMode(buttonPinB, INPUT);

    // digital pins
    pinMode(motorDir1A,OUTPUT);
    pinMode(motorDir2A,OUTPUT);
    pinMode(motorSpeedA, OUTPUT);
    digitalWrite(motorDir1A,HIGH);
    digitalWrite(motorDir2A,LOW);
    pinMode(baseDir1A,OUTPUT);
    pinMode(baseDir2A,OUTPUT);
    pinMode(baseSpeedA, OUTPUT);
    digitalWrite(baseDir1A,HIGH);
    digitalWrite(baseDir2A,LOW);
    pinMode(outflowDir1A,OUTPUT);
    pinMode(outflowDir2A,OUTPUT);
    pinMode(outflowSpeedA, OUTPUT);
    digitalWrite(outflowDir1A,HIGH);
    digitalWrite(outflowDir2A,LOW);
    pinMode(feedDir1A,OUTPUT);
    pinMode(feedDir2A,OUTPUT);
    pinMode(feedSpeedA, OUTPUT);
    digitalWrite(feedDir1A,HIGH);
    digitalWrite(feedDir2A,LOW);
    pinMode(motorDir1B,OUTPUT);
    pinMode(motorDir2B,OUTPUT);
    pinMode(motorSpeedB, OUTPUT);
    digitalWrite(motorDir1B,HIGH);
    digitalWrite(motorDir2B,LOW);
    pinMode(baseDir1B,OUTPUT);
    pinMode(baseDir2B,OUTPUT);
    pinMode(baseSpeedB, OUTPUT);
    digitalWrite(baseDir1B,HIGH);
    digitalWrite(baseDir2B,LOW);
    pinMode(outflowDir1B,OUTPUT);
    pinMode(outflowDir2B,OUTPUT);
    pinMode(outflowSpeedB, OUTPUT);
    digitalWrite(outflowDir1B,HIGH);
    digitalWrite(outflowDir2B,LOW);
    pinMode(feedDir1B,OUTPUT);
    pinMode(feedDir2B,OUTPUT);
    pinMode(feedSpeedB, OUTPUT);
    digitalWrite(feedDir1B,HIGH);
    digitalWrite(feedDir2B,LOW);
}

void loop() {
    // check off button
    buttonStateA = digitalRead(buttonPinA);
    buttonStateB = digitalRead(buttonPinB);
    if (buttonStateA == HIGH) {
      stpA = !stpA;
    }
    if (buttonStateB == HIGH) {
      stpB = !stpB;
    }

    Serial.print("Status: (");
    Serial.print(stpA); 
    Serial.print(", ");
    Serial.print(stpB); 
    Serial.println(")");

    if (!stpA || !stpB) {
      Serial.print("Round: (");
      Serial.print(counterA); 
      Serial.print(", ");
      Serial.print(counterB); 
      Serial.println(")");
    }
    
    if (stpA) {
      analogWrite(motorSpeedA, 0);
    } else {
      analogWrite(motorSpeedA, speed);
//      analogWrite(outflowSpeedA, speed);
      Serial.println("spinner A on");
      // execute repeatedly
      // check pH
      unsigned long avgpHA = 0;
      for (int i = 0; i < 9; i++) {
        avgpHA += analogRead(sensorpHA);
      }
      pHA = (float)avgpHA * 5.0 / 1024 / 10;
      pHA *= 3.5;
      
      if (pHA < MIN_PH) {
        analogWrite(baseSpeedA, speed);
        Serial.println("base A on");
      } else {
        analogWrite(baseSpeedA, 0);
      }
  
      // feed
      if (counterA % cycleLen == 0) {
        analogWrite(feedSpeedA, speed);
        analogWrite(outflowSpeedA, speed);
        // new exp feed code
        int Fij = 1;
        for (int i = 0; i < cycleLen; i++) {
          Fij += int(exp(u * (i + counterA)));
        }
        Fij *= Vo * u / cycleLen;
        curIntervA = int(Fij / Rf);
        Serial.print("feed A ON: ");
        Serial.print(Fij);
        Serial.print(", ");
        Serial.println(curIntervA);
      }
      if (counterA % cycleLen >= curIntervA) {
        Serial.println("feed a OFF");
        analogWrite(feedSpeedA, 0);
        analogWrite(outflowSpeedA, 0);
      }
      counterA = counterA + 1;
    }
    
    if (stpB) {
      analogWrite(motorSpeedB, 0);
    } else {
      analogWrite(motorSpeedB, speed);
//      analogWrite(outflowSpeedB, speed);
      // check pH
      unsigned long avgpHB = 0;
      for (int i = 0; i < 9; i++) {
        avgpHB += analogRead(sensorpHB);
      }
      pHB = (float)avgpHB * 5.0 / 1024 / 10;
      pHB *= 3.5;
      
      if (pHB < MIN_PH) {
        analogWrite(baseSpeedB, speed);
      } else {
        analogWrite(baseSpeedB, 0);
      }
  
      // feed
      if (counterB % cycleLen == 0) {
        analogWrite(feedSpeedB, speed);
        analogWrite(outflowSpeedB, speed);
        // new exp feed code
        int Fij = 1;
        for (int i = 0; i < cycleLen; i++) {
          Fij += int(exp(u * (i + counterB)));
        }
        Fij *= Vo * u / cycleLen;
        curIntervB = int(Fij / Rf);
      }
      if (counterB % cycleLen > curIntervB) {
        analogWrite(feedSpeedB, 0);
        analogWrite(outflowSpeedB, 0);
      }
      counterB = counterB + 1;
    }

    // TODO CHECK FOR ZERO/UNINIT VALUES
    Serial.print("pH: (");
    Serial.print(pHA);
    Serial.print(", ");  
    Serial.print(pHB); 
    Serial.println(")");

    Serial.print("Temperature: (");
    tempSensorA.requestTemperatures(); // Send the command to get temperature readings
    tempSensorB.requestTemperatures(); // Send the command to get temperature readings  
    float tempA = tempSensorA.getTempCByIndex(0);
    float tempB = tempSensorB.getTempCByIndex(0); 
    Serial.print(tempA); 
    Serial.print(", ");
    Serial.print(tempB); 
    Serial.println(")");
    Serial.print("Dissolved Oxygen: ");
    Serial.println(DO.read_do_percentage());
    Serial.print("\n");
    // display
    lcd.print("DO: ");
    lcd.print(DO.read_do_percentage());
    lcd.print(" pH: (");
    lcd.print(pHA);
    lcd.print(",");
    lcd.print(pHB);
    lcd.print(")");
    lcd.setCursor(0,1);
    lcd.print("Temp: (");
    lcd.print(tempA);
    lcd.print(",");
    lcd.print(tempB);
    lcd.print(")");
      
    delay(1000);
}

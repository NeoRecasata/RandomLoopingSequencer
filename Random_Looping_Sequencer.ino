/*
   Random Looping Sequencer with random pulses/trigers
   Code by: Neo Recasata

   TODO:
   Steps encoder (Changes the step length)
   MCP-4725 voltage output for CV (DONE)

   This currently has:
   1. Random CV with randomness potentiometer
   2. CV Step Erase feature
   3. Random trigger with probability potentiometer
   4. Trigger Step Erase feature

   DAC PINS
   SDA -> A4
   SCL -> A5
*/

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

#define potPin A0 //CV probability
#define pot2Pin A1 //trigger probability
#define pot3Pin A2 //step length
#define clockPin 3
#define pulsePin 4
#define cvErasePin 5
#define pulseSequenceErasePin 6
#define trigLed 7

int sequence[16]; //step array
int pulseSequence[16]; //array of triggers/pulses
int count = 0; //number of steps
int randNum = 0;
int randNum2 = 0;
int steps = 16;

void setup() {
  //Serial.begin(115200); //UNCOMMENT FOR DEBUGGING
  pinMode(pulsePin, OUTPUT);
  pinMode(trigLed, OUTPUT);

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x60);

  dac.setVoltage(0, false);
}

void loop() {
  do {

    stepsLength(); //determine steps length

    if (digitalRead(clockPin) == LOW) {

      //check if cv erase switch is high
      cvErase();

      //check if pulse erase switch is high
      pulseErase();

      //change voltage of step depending on the cv pot
      changeStepCv();

      //Output cv
      //Serial.print(count); //UNCOMMENT FOR DEBUGGING
      //Serial.print(" "); //UNCOMMENT FOR DEBUGGING
      dac.setVoltage(sequence[count], false);
      //Serial.println(sequence[count]); //UNCOMMENT FOR DEBUGGING

      //change voltage of step depending on the pulse pot
      changeStepPulse();

      //Output pulse
      if (pulseSequence[count] == 1) {
        //Serial.println("pulse"); //UNCOMMENT FOR DEBUGGING
        digitalWrite(trigLed, HIGH);
        digitalWrite(pulsePin, HIGH);
        delay(12);
        digitalWrite(trigLed, LOW);
        digitalWrite(pulsePin, LOW);
      }

      count += 1;
    }

    //wait if clock is low (Credits to Benjie Jiao's RandomTriggers)
    while (digitalRead(clockPin) == LOW) delay(1);

  } while (count < steps);
  count = 0;
}

static bool getRandomBool(int probability) {
  //returns true or false based on the probability
  //randVal starts from 10 to help keep the pot at 0 when it is fully ccw and ends at 1013
  int randVal = random(10, 1013);
  return randVal <= probability;
}

static void cvErase() {
  //erase or set to 0 the current step if the erase pin is high
  if (digitalRead(cvErasePin) == HIGH) {
    sequence[count] = 0;
  }
}

static void pulseErase() {
  //erase or set to 0 the current step if the erase pin is high
  if (digitalRead(pulseSequenceErasePin) == HIGH) {
    pulseSequence[count] = 0;
  }
}

static void changeStepCv() {
  //generate a 12bit random number
  randNum = random(0, 4096);
  //randomly change values in the array depending on the potentiometer
  if (getRandomBool(analogRead(potPin))) {
    sequence[count] = randNum;
  }
}

static void changeStepPulse() {
  //generate random number from 0 to 1
  randNum2 = random(0, 2);
  //randomly generate triggers based on the trigger potentiometer
  if (getRandomBool(analogRead(pot2Pin))) {
    //Serial.println(pulseSequence[count]); //UNCOMMENT FOR DEBUGGING
    //Serial.println("pulse"); //UNCOMMENT FOR DEBUGGING
    pulseSequence[count] = randNum2;
  }
}

static void stepsLength() {
  /* Predefined steps
      2, 3, 4, 5, 6, 8, 12, 16
  */

  int potValue = analogRead(pot3Pin);

  //Dividing the potentiometer to 8 different step lengths
  if ((0 <= potValue) && (potValue <= 127)) {
    steps = 2;
  }
  else if ((128 <= potValue) && (potValue <= 255)) {
    steps = 3;
  }
  else if ((256 <= potValue) && (potValue <= 383)) {
    steps = 4;
  }
  else if ((384 <= potValue) && (potValue <= 511)) {
    steps = 5;
  }
  else if ((512 <= potValue) && (potValue <= 639)) {
    steps = 6;
  }
  else if ((640 <= potValue) && (potValue <= 767)) {
    steps = 8;
  }
  else if ((768 <= potValue) && (potValue <= 895)) {
    steps = 12;
  }
  else if ((896 <= potValue) && (potValue <= 1023)) {
    steps = 16;
  }
}

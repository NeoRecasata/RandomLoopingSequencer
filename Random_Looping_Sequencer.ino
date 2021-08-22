/*
 * Random Looping Sequencer with random pulses/trigers
 * Code by: Neo Recasata
 * 
 * TODO: 
 * Steps encoder (Changes the step length)
 * MCP-4725 voltage output for CV
 * 
 * This currently has:
 * 1. Random CV with randomness potentiometer
 * 2. CV Step Erase feature
 * 3. Random trigger with probability potentiometer
 * 4. Trigger Step Erase feature
*/

#define potPin A0
#define pot2Pin A1
#define clockPin 3
#define pulsePin 4
#define cvErasePin 5
#define pulseSequenceErasePin 6
#define trigLed 7


int sequence[16]; //step array
int pulseSequence[16]; //array of triggers/pulses
int count = 0; //number of steps
int randNum = 0;
int steps = 16;ccc

void setup() {
  Serial.begin(115200);
  pinMode(pulsePin, OUTPUT);
}

void loop() {
  
  
  do {
    //generate a 12bit random number
    randNum = random(0,4096);
    
    if(digitalRead(clockPin) == LOW) {

      cvErase();

      pulseErase();
      
      changeStepCv();

      //Output cv
      Serial.print(count);
      Serial.print(" "); 
      Serial.println(sequence[count]);

      changeStepPulse();

      //Output pulse
      if(pulseSequence[count]==1) {
        Serial.println("pulse");
        digitalWrite(trigLed, HIGH);
        digitalWrite(pulsePin,HIGH);
        delay(12);
        digitalWrite(trigLed, LOW);
        digitalWrite(pulsePin, LOW);
      }
      
      count+=1;
    }
    
    //wait if clock is low (Credits to Benjie Jiao's RandomTriggers)
    while(digitalRead(clockPin) == LOW) delay(1);
    
  }while(count<steps);
  count = 0;
}

static bool getRandomBool(int probability){
  //returns true or false based on the probability
  //randVal starts from 10 to help keep the pot at 0 when it is fully ccw
  int randVal = random(10,1023);
  return randVal <= probability;
}

static void cvErase() {
  //erase or set to 0 the current step if the erase pin is high
      if(digitalRead(cvErasePin) == HIGH) {
        sequence[count] = 0;
      }
}

static void pulseErase() {
  //erase or set to 0 the current step if the erase pin is high
      if(digitalRead(pulseSequenceErasePin) == HIGH) {
        sequence[count] = 0;
      }
}

static void changeStepCv() {
  //randomly change values in the array depending on the potentiometer
      if(getRandomBool(analogRead(potPin))) {
        sequence[count] = randNum;
      }
}

static void changeStepPulse() {
  //randomly generate triggers based on the trigger potentiometer
      if(getRandomBool(analogRead(pot2Pin))) {
        Serial.println(pulseSequence[count]);
        pulseSequence[count] = 1;
      } 
}

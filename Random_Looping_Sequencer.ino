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
 * 2. Erase feature
 * 3. Random trigger with probability potentiometer
*/

#define potPin A0
#define pot2Pin A1
#define clockPin 3
#define pulsePin 4
#define erasePin 5


int sequence[16]; //step array
int count = 0; //number of steps
int randNum = 0;
int steps = 16;

void setup() {
  Serial.begin(9600);
  pinMode(pulsePin, OUTPUT);
}

void loop() {
  
  
  do {
    //generate a 12bit random number
    randNum = random(0,4096);
    
    if(digitalRead(clockPin) == HIGH) {

      //erase or set to 0 the current step if the erase pin is high
      if(digitalRead(erasePin) == HIGH) {
        sequence[count] = 0;
      }
      
      //randomly change values in the array depending on the potentiometer
      if(getRandomBool(analogRead(potPin))) {
        sequence[count] = randNum;
      }
      
      Serial.print(count);
      Serial.print(" "); 
      Serial.println(sequence[count]);

      //randomly generate triggers based on the trigger potentiometer
      if(getRandomBool(analogRead(pot2Pin))) {
        digitalWrite(pulsePin,HIGH);
        delay(12);
        digitalWrite(pulsePin, LOW);
      }
      
      count+=1;
    }
    
    //wait if clock is high (Credits to Benjie Jiao's RandomTriggers)
    while(digitalRead(clockPin) == HIGH) delay(1);
    
  }while(count<steps);
  count = 0;
}

static bool getRandomBool(int probability){
  //returns true or false based on the probability
  //randVal starts from 10 to help keep the pot at 0 when it is fully ccw
  int randVal = random(10,1023);
  return randVal <= probability;
}

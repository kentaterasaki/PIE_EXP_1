// Constants for controlling LED behavior
const uint16_t period = 400; // Time interval between toggling LED in milliseconds
const int numLeds = 4;
int ledPins[numLeds] = {4, 5, 6, 7};
uint32_t pastTime; // Global variable to store the time that LED last changed state
int firstCounter = 0;
int potPin = A0; //Initializes Potentiometer pin 
const int buttonPin = 3;  // the number of the pushbutton pin
int buttonState = 0;  
int modeCounter = 0;
// Function to check if it's time to change LED state
bool it_is_time(uint32_t t, uint32_t t0, uint16_t dt) {
  return ((t >= t0) && (t - t0 >= dt)) ||         // The first disjunct handles the normal case
            ((t < t0) && (t + (~t0) + 1 >= dt)); 
}

void setup() {
  // Set LED pins as OUTPUT
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  pastTime = millis();
}

void loop() {
  buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      modeCounter = modeCounter + 1;
      if (modeCounter >= 5){
        modeCounter = 0;
      }
      Serial.println(modeCounter);
    }
    else {
      Serial.print(modeCounter);
      if (modeCounter == 0){
        blink();
      }
      if (modeCounter == 1){
        swap();
      }
      if (modeCounter == 2){
        on();
      }
      if (modeCounter == 3){
        randomled();
      }
      if (modeCounter == 4){
        bounce();
      }

    }

}

// Function to create a blinking effect for all LEDs
void blink() {
  int potValue = analogRead(potPin);
  // Map the potentiometer value (0-1023) to the desired range of period (e.g., 100-2000)
  uint16_t mappedPeriod = map(potValue, 0, 1023, 100, 2000);
  // Update the period based on the potentiometer value
  int period = mappedPeriod;
  // Local variable to store the current value of the millis timer
  uint32_t t;          
  // Get the current value of the millis timer               
  t = millis();       
  // If BLINK_INTERVAL milliseconds have elapsed since blink_time, Toggle the state of all LEDs                
  if (it_is_time(t, pastTime, period)) { 
    digitalWrite(ledPins[0], !digitalRead(ledPins[0])); 
    digitalWrite(ledPins[1], !digitalRead(ledPins[1])); 
    digitalWrite(ledPins[2], !digitalRead(ledPins[2])); 
    digitalWrite(ledPins[3], !digitalRead(ledPins[3])); 
    // Update the time of the last state change
    pastTime = t;
  }
}

// Function to create a swapping effect between LED pairs
void swap() {
  int potValue = analogRead(potPin);
  // Map the potentiometer value (0-1023) to the desired range of period (e.g., 100-2000)
  uint16_t mappedPeriod = map(potValue, 0, 1023, 100, 2000);
  // Update the period based on the potentiometer value
  int period = mappedPeriod;
  uint32_t t; // Local variable to store the current value of the millis timer
  t = millis();
  if (it_is_time(t, pastTime, period)) { // If BLINK_INTERVAL milliseconds have elapsed since blink_time, 
    if (firstCounter % 2 == 0) { // Turn on the first pair of LEDs and turn off the second pair
      digitalWrite(ledPins[0], HIGH); 
      digitalWrite(ledPins[1], HIGH);
      digitalWrite(ledPins[2], LOW); 
      digitalWrite(ledPins[3], LOW);
    }
    // Turn off the first pair of LEDs and turn on the second pair
    else { 
      digitalWrite(ledPins[0], LOW); 
      digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[2], HIGH); 
      digitalWrite(ledPins[3], HIGH);
    }
    // Increment the counter and update the time of the last state change
    firstCounter = firstCounter + 1;
    pastTime = t;
  }
}

// Function to turn on all LEDs
void on() {
  digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], HIGH);
}

// Function to create a random blinking effect for one LED
void randomled() {
  int potValue = analogRead(potPin);
  // Map the potentiometer value (0-1023) to the desired range of period (e.g., 100-2000)
  uint16_t mappedPeriod = map(potValue, 0, 1023, 100, 2000);
  // Update the period based on the potentiometer value
  int period = mappedPeriod;
  uint32_t t; 
  t = millis();
  int randomLED = random(numLeds);
  if (it_is_time(t, pastTime, period)) {
    // Toggle the state of a randomly selected LED
    digitalWrite(ledPins[randomLED], !digitalRead(ledPins[randomLED]));
    // Update the time of the last state change
    pastTime = t;
  } 
} 

// Function to create a "snake" effect
void bounce() {
  int potValue = analogRead(potPin);
  // Map the potentiometer value (0-1023) to the desired range of period (e.g., 100-2000)
  uint16_t mappedPeriod = map(potValue, 0, 1023, 100, 2000);
  // Update the period based on the potentiometer value
  int period = mappedPeriod;
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    // while(millis() < time_now + period){   
    // }
    delay(period);
    digitalWrite(ledPins[i], LOW);
  } 
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    // while(millis() < time_now + period){        
    // }
    delay(period);
    digitalWrite(ledPins[i], LOW);
  } 
}

    




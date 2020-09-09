int led1 = 6;
int led2 = 7;
int toggleLed = 5;
int pushButton = 2;

int ledState1 = LOW;
int ledState2 = LOW;

unsigned long previousMillis1 = 0;
const long period1 = 1000;

unsigned long previousMillis2 = 0;
const long period2 = 200;

int debouncePeriod = 20;
int debounceMillis = 0;

bool buttonPushed = false;
int ledChange = LOW;
int lastState = HIGH;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(toggleLed, OUTPUT);
  pinMode(pushButton, INPUT);
  attachInterrupt(digitalPinToInterrupt(pushButton), pushButton_ISR, CHANGE); 
}

void pushButton_ISR()
{
  buttonPushed = true;
}

void loop()
{
  unsigned long currentMillis = millis();

if (currentMillis - previousMillis1 >= period1) { 
    previousMillis1 = currentMillis;  
    if (ledState1 == LOW) { 
      ledState1 = HIGH;
    } else {
      ledState1 = LOW;
    }
    digitalWrite(led1, ledState1);   
 }

 if (currentMillis - previousMillis2 >= period2) {
    previousMillis2 = currentMillis;  
    if (ledState2 == LOW) {
      ledState2 = HIGH;
    } else {
      ledState2 = LOW;
    }
    digitalWrite(led2, ledState2);
 }

 if (buttonPushed = true)    // check if ISR is called
  {
    if ((currentMillis - debounceMillis) > debouncePeriod && buttonPushed)  // generate 20ms debounce delay to avoid multiple presses
    {
      debounceMillis = currentMillis;      // save the last debounce delay time
      if (digitalRead(pushButton) == LOW && lastState == HIGH)     // change the led after push button is pressed
      {
        ledChange = ! ledChange;
        digitalWrite(toggleLed, ledChange);   
        lastState = LOW;
      }
      else if (digitalRead(pushButton) == HIGH && lastState == LOW)    
      {
        lastState = HIGH;
      }
     buttonPushed = false;
    }
  }
}

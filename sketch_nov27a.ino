const int START = 2;
const int END = 7;
const int BUTTON = 12;
const int DELAY = 120;
const int MAX_MODE_TIME = 4000;

int mode = 0;
int modeTime = 0;

boolean isClicked = false;

void setup() {
  for (int i = START; i <= END; ++i) {
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop() {
  Serial.println(digitalRead(BUTTON));
  
  if (modeTime >= MAX_MODE_TIME || isClicked) {
    modeTime = 0;
    isClicked = false;
    
    ++mode;
  }

  switch(mode) {
    case 0:
      modeTime += chainMode(DELAY);
      break;
    case 1:
      modeTime += allBligthningMode(DELAY);
      break;
    case 2:
      modeTime += reverseChainMode(DELAY);
      break;
    case 3:
      modeTime += roundaboutMode(DELAY);
      break;
    case 4:
      modeTime += randomBligthningMode(DELAY);
      break;
    default:
      mode = 0;
  }
  
  checkButtonAndDelay(DELAY);
  modeTime += DELAY;
}

int chainMode(int delayValue) {
  int delaySum = 0;
  
  for (int i = START; i <= END; ++i) {
    digitalWrite(i, HIGH);
    checkButtonAndDelay(delayValue);
    digitalWrite(i, LOW);
    checkButtonAndDelay(delayValue);

    delaySum += (delayValue * 2);
  }

  return delaySum;
}

int reverseChainMode(int delayValue) {
  int delaySum = 0;
  
  for (int i = END; i >= START; --i) {
    digitalWrite(i, HIGH);
    checkButtonAndDelay(delayValue);
    digitalWrite(i, LOW);
    checkButtonAndDelay(delayValue);

    delaySum += (delayValue * 2);
  }

  return delaySum;
}

int roundaboutMode(int delayValue) {
  return chainMode(delayValue) + reverseChainMode(delayValue);
}

int allBligthningMode(int delayValue) {
  checkButtonAndDelay(delayValue);
  for (int i = START; i <= END; ++i) {
    digitalWrite(i, HIGH);
  }
  
  checkButtonAndDelay(delayValue);
  for (int i = START; i <= END; ++i) {
    digitalWrite(i, LOW);
  }

  return delayValue * 2;
}

int randomBligthningMode(int delayValue) {
  int delaySum = 0;
  
  for (int i = 0; i <= (END - START + 1) * 4; ++i) {
    int randomLedPin = random(START, END + 1);
    digitalWrite(randomLedPin, HIGH);
    checkButtonAndDelay(delayValue / 2);
    digitalWrite(randomLedPin, LOW);
    checkButtonAndDelay(delayValue / 2);

    delaySum += delayValue;
  }

  return delaySum;
}

void checkButtonAndDelay(int value) {
  if (digitalRead(BUTTON) == HIGH) {
    Serial.println("check!");
    isClicked = true;
  }
  delay(value);
}


const int buttonOne = A3;
const int buttonTwo = A7;
const int buttonThree = A5;

const int ledGreen = D7;
const int ledRed = D6;

int previousButtonOneState = HIGH;
int previousButtonTwoState = HIGH;
int previousButtonThreeState = HIGH;

int buttonOneState = HIGH;
int buttonTwoState = HIGH;
int buttonThreeState = HIGH;

int indexCount = 0;
int codeList[4];

void setup() {
  Serial.begin(9600);
  pinMode(buttonOne, INPUT);  
  pinMode(buttonTwo, INPUT);  
  pinMode(buttonThree, INPUT);  

  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);


}

void loop() {
  //Light LED if correct code is inputted
  /*
  codeList[0] = 3;
  codeList[1] = 1;
  codeList[2] = 2;
  codeList[3] = 1;
  */
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  
  if(returnCodeState(codeList)){
    Serial.print("CORRECT");
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    delay(5000);
    //Turn off after 5 seconds
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    delay(5000);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    //Reset code combination
    codeList[0] = 0;
    codeList[1] = 0;
    codeList[2] = 0;
    codeList[3] = 0;
  }
  
  
  buttonOneState = digitalRead(buttonOne);
  buttonTwoState = digitalRead(buttonTwo); 
  buttonThreeState = digitalRead(buttonThree); 
  delay(10); // Fixing debounce

  if(indexCount > 3){
    indexCount = 0;
  }
  
  //Record value input on release press
  if (previousButtonOneState == LOW && buttonOneState == HIGH) {
      buttonPress(1);
      previousButtonOneState = HIGH;
  }
  if (previousButtonTwoState == LOW && buttonTwoState == HIGH) {
      buttonPress(2);
      previousButtonTwoState = HIGH;
  }
  if (previousButtonThreeState == LOW && buttonThreeState == HIGH) {
      buttonPress(3);
      previousButtonThreeState = HIGH;
  }

  //Button press down
  if (buttonOneState == LOW) {
    previousButtonOneState = buttonOneState;
    delay(10);
  }
  if (buttonTwoState == LOW) {
    previousButtonTwoState = buttonTwoState;
    delay(10);
  }
  if (buttonThreeState == LOW) {
    previousButtonThreeState = buttonThreeState;
    delay(10);
  }
  
}

void buttonPress(int codeDigit){
  codeList[indexCount] = codeDigit;
  Serial.print("Code=");
  Serial.print(codeList[0]);
  Serial.print(codeList[1]);
  Serial.print(codeList[2]);
  Serial.print(codeList[3]);
  Serial.print("|");
  Serial.print("Index= ");
  Serial.println(indexCount);
  indexCount++;
}

bool returnCodeState(int codeList[]){
  
  if(codeList[0] == 2 && codeList[1] == 2 && codeList[2] == 1 && codeList[3] == 1 ){
    Serial.println("Correctcode");
    return true;
  }
  else{
    return false;
  }
}







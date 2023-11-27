# HW11

I want to create a cipher machine with the password sequence:

1. turn the potentiometer to its maximum value
2. push button 1
3. turn the potentiometer to the minimum value
4. press button 2
If correct, Red led goes on. If not, blue led goes on.

So I connected two push buttons, relays and two led bulbs in parallel, here is my schematic and the connected circuits.

![GkIPFP.jpg](https://imgpile.com/images/GkIPFP.jpg)

![Gku8tE.png](https://imgpile.com/images/Gku8tE.png)

![GkIsJL.jpg](https://imgpile.com/images/GkIsJL.jpg)

In order to test if my code is correct, I used the following code to test separately：

Potentiometer：
void setup() {
  Serial.begin(9600);
}
void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
}
 
button：
 void setup() {
  pinMode(2, INPUT_PULLUP); // D2
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(2) == LOW) {
    Serial.println("Button 1 pressed");
  }
}

LED
void setup() {
  pinMode(4, OUTPUT); //D4
}
void loop() {
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
}

This is my Finite State Machine for my password.

![GkuYdM.jpg](https://imgpile.com/images/GkuYdM.jpg)

Pseudocode：
Define potPin as A0 (pin for the sliding potentiometer)
Define button1Pin as 2 (pin for button 1)
Define button2Pin as 3 (pin for button 2)
Define ledSuccess as 4 (pin for the success LED)
Define ledFailure as 5 (pin for the failure LED)

Declare step as 0 (to track the current step of the password input)

Setup function:
  Initialize pins:
    - Set potPin as INPUT
    - Set button1Pin and button2Pin as INPUT_PULLUP
    - Set ledSuccess and ledFailure as OUTPUT

Main loop:
  Read the analog value from potPin into potValue
  Check if button1 and button2 are pressed

  Depending on the value of step, perform actions:
    - If step is 0:
      - If potValue is greater than 2000, set step to 1
    - If step is 1:
      - If button1 is pressed, set step to 2
      - If button2 is pressed, call failure()
    - If step is 2:
      - If potValue is less than 50, set step to 3
      - If potValue is greater than 950, call failure()
    - If step is 3:
      - If button2 is pressed, light up ledSuccess for 2 seconds, then turn it off and reset step to 0
      - If button1 is pressed, call failure()

Failure function:
  Light up ledFailure for 2 seconds, then turn it off and reset step to 0


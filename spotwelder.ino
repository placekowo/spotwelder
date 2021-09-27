#include <TM1637.h> // grove 4 digit display library

const int relay = 10; // define relay pin

const int button = 11; // define button pin, momentary switch pulled low when pressed

const int rotCLK = 2; // define pins for rotary encoder
const int DT = 3;

const int CLK = 13; // define pins for display
const int DIO = 12;

TM1637 tm(CLK,DIO); // define display pins for library

int counter = 300; // starting ms value
const int increment = 10; // increment between steps
const int maxlimit = 1000; // max ms value
const int minlimit = 10; // min ms value

int buttonState = 1;

void displayNumber(int num) { // display integers passed to function
  tm.display(3, num % 10); 
  tm.display(2, num / 10 % 10);
  tm.display(1, num / 100 % 10);
  tm.display(0, num / 1000 % 10);
}

void activateRelay(int duration) { // pulses relay for set duration
  digitalWrite(relay, HIGH);
  Serial.println("relay on");
  delay(duration);
  digitalWrite(relay, LOW);
  Serial.println("relay off");
}

void setup() {

tm.init(); // init display
tm.set(2); // set display brightness  

pinMode(rotCLK,INPUT); // setting pins as inputs and outputs
pinMode(DT,INPUT);
pinMode(relay,OUTPUT); 
pinMode(button,INPUT_PULLUP);

Serial.begin(9600); // start serial communication at 9600 baud for troubleshooting

displayNumber(counter); // displays start counter value after power is applied to the arduino, otherwise it only shows after moving encoder
} 

void loop() {
  if (counter <= minlimit){ // stop counter from going above max value or below 10
    counter = minlimit + increment; 
  } 
  if (counter >= maxlimit){
    counter = maxlimit - increment; // bit of a hack to stop the counter from going above or below max & min value
  }
  
static uint16_t state=0; // some dark wizadry to debounce the rotary encoder signals
state=(state<<1) | digitalRead(rotCLK) | 0xe000;
if (state==0xf000){
  state=0x0000;
  if(digitalRead(DT))
  counter = counter - increment; // increase or decrease value in set increments
  else
  counter = counter + increment;
  displayNumber(counter);
  Serial.println(counter);
    }

if(digitalRead(button) == LOW) { // setting state of button so that it only triggers relay for set delay, even when switch held down
  if (buttonState == 1) {
    Serial.println("zappy zap");
    activateRelay(counter); }
  buttonState = 0; } 
  else {
  buttonState = 1; }
}

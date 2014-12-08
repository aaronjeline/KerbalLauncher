//Kerbal Space Launcher. Aaron Eline 2014
//Keyboard implimination from: http://mitchtech.net/arduino-usb-hid-keyboard/

uint8_t buf[8] = { 0 }; //Keyboard report buffer
//Pin definitions
const int launchKey = 13;
const int led = 8;
const int launchButton = 7;
const int rcsSwitch = 11;
boolean doneLaunch;
int rcsBit;
//Vars for keyboard keys
const int space = 44;
const int r = 21;
const int t = 23;
void setup()
{
  //Initialize Serial Communications for the keyboard
  Serial.begin(9600);
  //Set up pins
  pinMode(launchKey, INPUT);
  pinMode(led, OUTPUT);
  pinMode(launchButton, INPUT);
  pinMode(rcsSwitch, INPUT);
  //Setup state
  doneLaunch = false;
  
  rcsBit = 0;
}



void loop()
{
  //Init switch state
  int keyState;
  keyState = digitalRead(launchKey);
  int launchState;
  launchState = digitalRead(launchButton);
  int rcsState;
  rcsState = digitalRead(rcsState);
  //Turn on the LED if the key is turned
  if(keyState == LOW)
  {
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  /*Press spacebar if the button is pressed WHILE the key is turned
   *We also want to make sure space is only pressed once,
   *so check to make sure the button wasn't pressed last loop */
  if(launchState == LOW && doneLaunch == false && keyState == LOW)
  {
    sendKey(space);  
    doneLaunch = true;
  }
  if(launchState == HIGH && doneLaunch == true){
    doneLaunch = false;
  }  
  
  if(rcsState == LOW && rcsBit == 0){
    sendKey(r);
    rcsBit = 1;
  }else if(rcsState == HIGH && rcsBit == 1){
    sendKey(r); 
    rcsBit = 0;
  }
}




//Keyboard Implimentation, see:http://mitchtech.net/arduino-usb-hid-keyboard/
  void sendKey(int keyNum){
    buf[2] = keyNum;
    Serial.write(buf, 8);
    releaseKey();
  }
  void releaseKey()
  {
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8);
  }

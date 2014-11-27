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

void setup()
{
  //Initialize Serial Communications for the keyboard
  Serial.begin(9600);
  //Set up pins
  pinMode(launchKey, INPUT);
  pinMode(led, OUTPUT);
  pinMode(launchButton, INPUT);
  //Setup state
  doneLaunch = false;
  rcsBit = 0;
}



void loop()
{
  initState();
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
    sendKey(44); //Spacebar 
    doneLaunch = true;
  }
  if(launchState == HIGH && doneLaunch == true){
    doneLaunch = false;
  }  
  
  
  
  
}

void initState(){
  //Setup switch detection
  int keyState;
  keyState = digitalRead(launchKey);
  int launchState;
  launchState = digitalRead(launchButton);
  int rcsState;
  rcsState = digitalRead(rcsState);
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

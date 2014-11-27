//Kerbal Space Launcher. Aaron Eline 2014
//Based on: http://mitchtech.net/arduino-usb-hid-keyboard/

uint8_t buf[8] = { 0 }; //Keyboard report buffer
const int launchKey = 13;
const int led = 8;
const int launchButton = 7;
boolean doneLaunch;
void setup()
{
  Serial.begin(9600);
  pinMode(launchKey, INPUT);
  pinMode(led, OUTPUT);
  pinMode(launchButton, INPUT);
  doneLaunch = false;
}



void loop()
{
  int keyState;
  keyState = digitalRead(launchKey);
  int launchState;
  launchState = digitalRead(launchButton);
  
  if(keyState == LOW)
  {
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  
  if(launchState == LOW && doneLaunch == false && keyState == LOW)
  {
    sendKey(44); //Spacebar 
    doneLaunch = true;
  }
  if(launchState == HIGH && doneLaunch == true){
    doneLaunch = false;
  }  
  
  
  
  
}

//Keyboard Code
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

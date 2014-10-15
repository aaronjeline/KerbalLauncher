/* Arduino as USB Keyboard test
 * A simple helloworld
 * Aaron Eline
 * Based on: http://mitchtech.net/arduino-usb-hid-keyboard/
 */

uint8_t buf[8] = { 
  0 }; 	/* Keyboard report buffer */
boolean done;
const int launchButton = 12;
const int keySwitch = 13;
boolean active;
const int keyLED = 11;
const int rcsSwitch = 10;
int rcsBit;
const int sasSwitch = 9;
int sasBit;

void setup() 
{
  
  Serial.begin(9600);
  done = false;
  delay(200);
  pinMode(launchButton, INPUT);
  pinMode(keySwitch, INPUT);
  pinMode(keyLED, OUTPUT);
  pinMode(rcsSwitch, INPUT);
  pinMode(sasSwitch, INPUT);
  rcsBit = 1;
  sasBit = 1;
  

  
}


void loop()                                                                                                                                           
{
  int launchState;
  launchState = digitalRead(launchButton);
  int keyState;
  keyState = digitalRead(keySwitch);
  int rcsState;
  rcsState = digitalRead(rcsSwitch);
  int sasState;
  sasState = digitalRead(sasSwitch);
  
  
  if(keyState == LOW){  
    active = true;
    digitalWrite(keyLED, HIGH);
  }else{
    active = false;
    digitalWrite(keyLED, LOW);
  }
  if(active){
  if(digitalRead(12) == HIGH /*&& !done*/){
    
    sendKey(44); //Spacebar
    //done = true;
  }
  
  if(rcsState == LOW && rcsBit == 1){
    sendKey(21); //r
    rcsBit = 0;
  }else if (rcsState == HIGH && rcsBit == 0){
    sendKey(21); //r
    rcsBit = 1;
  }
  
  if(sasState == LOW && sasBit == 1){
    sendKey(23); //t
    sasBit = 0;
  }else if (sasState == HIGH && sasBit == 0){
    sendKey(23); //t
    sasBit = 1;
  }
  
  
  
  
  
  if(done && launchState == HIGH){
    done=false;
  }
  }
  
}



void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
}

void sendKey(int keyNum){
  buf[2] = keyNum;
  Serial.write(buf, 8);
  releaseKey();
}

//


#include <Keyboard.h>
#include <Arduino.h>
#include <NeoPixelConnect.h>

int S1_pin = 29;
int S2_pin =28;
int mykey = 27 ;

unsigned long last_run=0;
int volum =0;
bool polsaPolsat = false;
NeoPixelConnect led(16, 1, pio0, 0); 

void puja(){
  //Serial1.println("A");
  Keyboard.consumerPress(KEY_VOLUME_INCREMENT);
    delay(100);
    Keyboard.consumerRelease();      
}
void baixa(){
    //Serial1.println("B");
    Keyboard.consumerPress(KEY_VOLUME_DECREMENT);
    delay(100);
    Keyboard.consumerRelease();

}
void polsa(){
  //Serial1.println("C");
    Keyboard.consumerPress(KEY_MUTE);
    delay(100);
    Keyboard.consumerRelease();
}
void shaft_moved(){
  if (millis()-last_run>5){
    if  (digitalRead(S2_pin)==1){
        volum++;
    
    
    //Serial1.println("A");
     }
    if (digitalRead(S2_pin)==0){
    volum--;

    //Serial1.println("B");
    }
  last_run=millis();
  }
}

void  reset_to_0(){
  polsaPolsat = true;
  //Serial1.println("C");
}

void setup() {  
  Keyboard.begin();
  //Serial1.begin(57600);
  //Serial1.println("boot1");
  
  pinMode(S1_pin,INPUT);
  pinMode(S2_pin,INPUT);
  pinMode(mykey,INPUT);
  attachInterrupt(digitalPinToInterrupt(S1_pin),  shaft_moved, FALLING);
  attachInterrupt(digitalPinToInterrupt(mykey), reset_to_0, FALLING);
  
}
void setColor(int red, int green, int blue) {
  // Set the brightness of each color using analogWrite()
   led.neoPixelFill(red, green, blue, true); // le pasamos el valor de RGB del color que queremos
  
}
void loop() {  
  
    delay(10);
    for (int i = 0; i <= 360; i++) {
    if(polsaPolsat || (volum != 0)){
        //Serial1.println(volum);
        if(polsaPolsat ){
          polsaPolsat = false;
          volum =0;
          polsa();
        }
        if(volum > 0){
          volum--;
          puja();
        }else if(volum< 0){
          volum++;
          baixa();
        }
        if(abs(volum) > 5){
          delay(25);
        }else{
          delay(50);
        }
        
      }
    // Calculate the color values based on the angle
    int red = (sin(radians(i)) + 1) * 127;
    int green = (sin(radians(i + 120)) + 1) * 127;
    int blue = (sin(radians(i + 240)) + 1) * 127;

    // Set the color
    setColor(red, green, blue);
    delay(10);
  }
  
  

} 

#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm audio;

char wave[] = "filter.wav";

int inputPin = 3;               // PIR sensor PIN
int pirState = LOW;             // Motion detection starts at off
int val = 0;
int delayReading = 0; 
int personDetected = 1;
int audioInProgress = 0;

void setup() {
  audio.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  pinMode(inputPin, INPUT);     // Sensor as Input
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  audio.setVolume(5);
  Serial.begin(9600);
  
}

void loop(){
  Serial.println("Before wait");
  delay(delayReading);   
  Serial.println("After delayReading interval");              
  
  val = digitalRead(inputPin);
  
  Serial.println(val);
  if (val == personDetected && audio.isPlaying() == audioInProgress) {
      
      delayReading = 10000;  // The length of the song 
      // Check to see if PIR picks up on motion and song is not playing
      Serial.println("Motion detected!");
      audio.play(wave);
  }
  else { 
      delayReading = 0; 
  }
}

#include <DFPlayerMini_Fast.h>
#include <ezButton.h>

#include "Arduino.h"
#include "SoftwareSerial.h"

#define rxPin 10
#define txPin 11

#define LED_A 3
#define LED_B 5

#define POWER_BUTTON 6

//ezButton POWER_BUTTON(6);
ezButton CHANGE_FOLDER(7);
ezButton NEXT_BUTTON(8);
ezButton PAUSE_BUTTON(9);

#define VLM_PIN A0
#define SAMPLES 20 //average of x values to stabilize reading , 10 ?

#define BUSY_PIN 2

#define VOLUME_LEVEL 7 // 0 - 30 ( 18 is a good level )
#define MAX_VLM_LVL 23
#define MP3_SOUNDS_FOLDER 10

#define USE_POTENTIOMETER false

#define DEBUG 1
#if DEBUG
  #define D_print(...) Serial.print(__VA_ARGS__)
  #define D_println(...) Serial.println(__VA_ARGS__)
#else
  #define D_print(...)
  #define D_println(...)
#endif

int fadeDuration = 800; //LEDS fade duration in ms

int num_tracks_in_folder = 0;
int num_folders = 2;
int actual_track_n = 0;
int actual_folder = 1;
int next_folder = 1;

SoftwareSerial mySoftwareSerial(rxPin, txPin); // RX, TX
DFPlayerMini_Fast myDFPlayer;

//microphone state
boolean lastPowerState = HIGH; // being INPUT_PULLUP, IT IS REVERSED
int powerState = HIGH;
int OnState = LOW;
int OffState = HIGH;

boolean isOn = false;//false default
boolean isPlaying = false;
boolean initSound = false;
boolean folder_changed = false;
boolean has_media = true;

int current_volume = 0;
int inputVolume = 0;
int outputVolume = 0;
int last_vlm_val = 0;

void setup()
{
  // define pin modes for tx, rx:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUSY_PIN,INPUT);
  pinMode(VLM_PIN,INPUT_PULLUP);
  pinMode(POWER_BUTTON,INPUT_PULLUP);

  //POWER_BUTTON.setDebounceTime(50);
  CHANGE_FOLDER.setDebounceTime(20);
  NEXT_BUTTON.setDebounceTime(50);
  PAUSE_BUTTON.setDebounceTime(50);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  delay(1000);

  //Starting
  D_println();
  D_println(F("DFRobot DFPlayer Mini"));
  D_println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  
  D_println(F("DFPlayer Mini online."));
  // check errors+
  if ( checkForErrors() != 1 ){
    D_println("[ No errors ]");

    D_println();
    myDFPlayer.volume(VOLUME_LEVEL);  //Set volume value. From 0 to 30
    delay(200);
  
    D_print("Current Volume : ");
    D_print( myDFPlayer.currentVolume() );
    D_println();
    D_print("Total Num tracks: ");
    D_print(myDFPlayer.numSdTracks());
    D_println();
  
    num_tracks_in_folder = myDFPlayer.numTracksInFolder(actual_folder);
  
    D_print("Current track : ");
    D_print(myDFPlayer.currentSdTrack());
    D_println();
    // num_folders = myDFPlayer.numFolders() //contar 1 menos debido a la carpeta de SOUNDS

    //Initiation();
    
  }else{
    D_println("[ Some errors to fix ]");
  }

  if (!USE_POTENTIOMETER) {
    myDFPlayer.volume(VOLUME_LEVEL);
    current_volume = VOLUME_LEVEL;
  }
  
}

void loop()
{
  CHANGE_FOLDER.loop();
  NEXT_BUTTON.loop();
  PAUSE_BUTTON.loop();

  isPlaying = digitalRead(BUSY_PIN) == LOW;

  handleVolumeControl();
  handlePowerButton();
  handlePlaybackButtons();
}

void Initiation() {
  D_println();
  D_println(F("STARTING.."));
  isOn = true;

  current_volume = VOLUME_LEVEL;
  myDFPlayer.volume(VOLUME_LEVEL);  // opcional si no se actualiza en otro lado

  actual_track_n = 1;
  initSound = true;

  fadeLed(digitalRead(LED_A));  // efecto LED
}

void handlePowerButton() {
  static unsigned long lastPressTime = 0;
  int currentState = digitalRead(POWER_BUTTON);

  if (currentState != lastPowerState) {
    delay(20); // Debounce simple

    if (digitalRead(POWER_BUTTON) == currentState) {
      unsigned long now = millis();

      if (now - lastPressTime > 800) {
        D_println();
        D_print("Power button pressed. New state: ");
        D_println(currentState);

        // 1. Reproducir sonido ON/OFF
        delay(50);
        myDFPlayer.playFolder(MP3_SOUNDS_FOLDER, 1);

        // 2. Ejecutar el fade LED mientras suena
        if (!isOn) {
          Initiation();  // hace fade
        } else {
          turnOff();     // hace fade
        }

        isOn = !isOn;
        lastPressTime = now;
      }
    }

    lastPowerState = currentState;
  }
}

void handlePlaybackButtons() {
  // if (!isOn) return; 
  if (PAUSE_BUTTON.isPressed()) {
    if (isPlaying) pause();
    else resume();
  }

  if (NEXT_BUTTON.isPressed()) {
    playNextSong();
  }

  if (CHANGE_FOLDER.isPressed()) {
    changeFolder();
    updateActualFolder();

    D_println();
    D_print("Changing folder to: ");
    D_println(next_folder);

    num_tracks_in_folder = myDFPlayer.numTracksInFolder(next_folder);
    D_print("Tracks in folder ");
    D_print(next_folder);
    D_print(": ");
    D_println(num_tracks_in_folder);
  }
}

void handleVolumeControl() {
  if (!USE_POTENTIOMETER || powerState != OnState) return;

  int inputVolume = readVolumeAverage();
  int outputVolume = map(inputVolume, 0, 1023, 0, MAX_VLM_LVL);

  if (abs(outputVolume - last_vlm_val) > 1) {
    last_vlm_val = outputVolume;
    current_volume = outputVolume;
    myDFPlayer.volume(outputVolume);

    D_print("Volume changed to: ");
    D_println(current_volume);
  }
}

int readVolumeAverage() {
  long total = 0;
  for (int i = 0; i < SAMPLES; i++) {
    total += analogRead(VLM_PIN);
    delay(2);
  }
  return total / SAMPLES;
}

void fadeLed(boolean input){
  for(int state=0;state<256;state++){
    if (input==LOW){
      analogWrite(LED_A, state);
      analogWrite(LED_B, state);
    }else{
      analogWrite(LED_A, 255-state);
      analogWrite(LED_B, 255-state);
    }
    delay(fadeDuration/256); //=(total fading duration)/(number of iterations)
  }
}

void playNextSong(){

  if(initSound == true){
    // Play init Sound
    actual_track_n = 1;
    initSound = false;
  }else{

    if(actual_folder != next_folder){
      //after changing folder, play first sound of folder
       actual_track_n = 1;
       actual_folder = next_folder;
    }else{
      if(actual_track_n < num_tracks_in_folder) {
        actual_track_n++;
      }else{
        actual_track_n = 1;
      }
        
    }
      
  }
  
  
  myDFPlayer.playFolder(actual_folder,actual_track_n);
  //isPlaying = true;
  D_print("-Playing track "); 
  D_print(actual_track_n);
  D_print("-");
  D_println();

  D_print("Track number: ");
  D_print(actual_track_n);
  D_print(" in folder :");
  D_print(actual_folder);
  D_println();
      
  delay(200);
}

void changeFolder(){

  if(next_folder < num_folders){
    next_folder++;
  }else{
    next_folder = 1;
  }

  actual_track_n = 1;
  
  folder_changed = true;
  
  delay(200);
}

void updateActualFolder(){
  actual_folder = next_folder;
  
  delay(200);
}

void pause(){
  if(initSound == true){
    myDFPlayer.playFolder(actual_folder,actual_track_n);
    D_println("-Playing first song- ");
    initSound = false;
  }else{
    myDFPlayer.pause();
    D_println("-Paused- ");
  }
  delay(500);
}

void resume(){

  if(initSound == false && folder_changed == false){
    myDFPlayer.resume();
    D_println("-Resumed- ");
  }
  
  if(initSound == true){
    myDFPlayer.playFolder(actual_folder,actual_track_n);
    D_println("-Playing first song- ");
    initSound = false;
  }

  if(folder_changed == true){
    myDFPlayer.playFolder(actual_folder,actual_track_n);
    D_println("-Playing first song- ");
    folder_changed = false;
  }
  
  
  delay(500);
}

int checkForErrors() {
  int has_errors = 0;
  
   if ( !myDFPlayer.begin(mySoftwareSerial) ) {  //Use softwareSerial to communicate with mp3.
    D_println(F("Unable to begin:"));
    D_println(F("1.Please recheck the connection!"));
    D_println(F("2.Please insert the SD card!"));
    D_println(myDFPlayer.numSdTracks()); //read mp3 state

    has_errors = 1;
    
    delay(5000);
    return has_errors;
  }

  if( myDFPlayer.numSdTracks() == -1){
    has_errors = 1;
    has_media = false;
    D_println("- SD card not found");
  }

  return has_errors;
}

void turnOff(){
  D_println(F("TURNING OFF.."));
  isOn = false;
  
  myDFPlayer.playFolder(MP3_SOUNDS_FOLDER,1);  //Play the ON SOUND mp3
  //isPlaying = false;
  fadeLed(digitalRead(LED_A));
}



 

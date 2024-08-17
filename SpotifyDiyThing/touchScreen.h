//#include <XPT2046_Touchscreen.h>
#include "CYD28_TouchscreenR.h"
#include <SPI.h>

//#define XPT2046_IRQ 36
//#define XPT2046_MOSI 32
//#define XPT2046_MISO 39
//#define XPT2046_CLK 25
//#define XPT2046_CS 33

#define CYD28_DISPLAY_HOR_RES_MAX 320
#define CYD28_DISPLAY_VER_RES_MAX 240

bool shufflePressed = false;
bool shuffleState = false;
bool prevTrackPressed = false;
bool nextTrackPressed = false;
bool playPausePressed = false;
bool playState = false;


// Button locations
const int playPauseButtonX = 40;
const int playPauseButtonY = 30;
const int shuffleButtonX = 280;
const int shuffleButtonY = 30;
const int previousTrackButtonX = 40;
const int previousTrackButtonY = 90;
const int nextTrackButtonX = 280;
const int nextTrackButtonY = 90;
const int buttonRadius = 16;

//SPIClass mySpi = SPIClass(HSPI);
//
//XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
CYD28_TouchR ts(CYD28_DISPLAY_HOR_RES_MAX, CYD28_DISPLAY_VER_RES_MAX);

SpotifyArduino *spotify_touch;

void touchSetup(SpotifyArduino *spotifyObj) {
//  mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
//  ts.begin(mySpi);
  ts.begin();
  ts.setRotation(1);
  spotify_touch = spotifyObj;
}

bool handleTouched() {
  prevTrackPressed = false;
  nextTrackPressed = false;
  playPausePressed = false;
  shufflePressed = false;
  playState = false;
  shuffleState = false; 

  //if (ts.tirqTouched() && ts.touched()) {
  if (ts.touched()) {
    CYD28_TS_Point p = ts.getPointScaled();
    Serial.print("Pressure = ");
    Serial.print(p.z);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.print(p.y);
    delay(30);
    Serial.println();
     
    // Handle button touches for play/pause, like, previous track, and next track
    if (pow(p.x - playPauseButtonX, 2) + pow(p.y - playPauseButtonY, 2) <= pow(buttonRadius, 2)) {
      Serial.println(">>>>Play/Pause true");
      Serial.printf("Track playing: %d\n", isTrackPlaying);
      playPausePressed = true;
      playState = isTrackPlaying;
      return true;
    } else if (pow(p.x - shuffleButtonX, 2) + pow(p.y - shuffleButtonY, 2) <= pow(buttonRadius, 2)) {
      Serial.println(">>>>Shuffle true");
      Serial.printf("Shuffle enabled: %d\n", isShuffleEnabled);
      shufflePressed = true;
      shuffleState = isShuffleEnabled; // Toggle shuffle state
      return true;
    } else if (pow(p.x - previousTrackButtonX, 2) + pow(p.y - previousTrackButtonY, 2) <= pow(buttonRadius, 2)) {
      Serial.println(">>>>Previous true");
      prevTrackPressed = true;
      return true;
    } else if (pow(p.x - nextTrackButtonX, 2) + pow(p.y - nextTrackButtonY, 2) <= pow(buttonRadius, 2)) {
      Serial.println(">>>>Next true");
      nextTrackPressed = true;
      return true;
    }
  }
  return false;
}
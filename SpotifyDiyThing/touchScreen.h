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

bool playPauseStatus = false;
bool shuffleStatus = false;
bool previousTrackStatus = false;
bool nextTrackStatus = false;

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
  previousTrackStatus = false;
  nextTrackStatus = false;
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
    if (p.x > 20 && p.x < 100 && p.y > 180 && p.y < 220) {
      playPauseStatus = true;
      return true;
    } else if (p.x > 120 && p.x < 200 && p.y > 180 && p.y < 220) {
      shuffleStatus = true;
      return true;
    } else if (p.x > 220 && p.x < 300 && p.y > 180 && p.y < 220) {
      previousTrackStatus = true;
      return true;
    } else if (p.x > 20 && p.x < 100 && p.y > 240 && p.y < 280) {
      nextTrackStatus = true;
      return true;
    }
  }
  return false;
}
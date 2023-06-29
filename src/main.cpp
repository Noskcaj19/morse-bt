#include "Adafruit_NeoPixel.h"
#include "Adafruit_TinyUSB.h"
#include "MorseDecoder.h"
#include "morsedefs.h"
#include "MorseOutput.h"
#include "bluefruit.h"
#include <Arduino.h>

Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(1, PIN_NEOPIXEL);

BLEDis bledis;
BLEHidAdafruit blehid;

void onInputChange(bool on) {
  if (on) {
    neopixel.setPixelColor(0, 0, 16, 0);
  } else {
    neopixel.setPixelColor(0, 0, 0, 0);
  }
  neopixel.show();
}

void onMorse(String morse) {
  Serial.println(morse);
  for (unsigned int i = 0; i < morse.length(); i++) {
    char c = morse.charAt(i);
    blehid.keyPress(c);
    delay(15);
    blehid.keyRelease();
    delay(15);
  }
}

Decoder *decoder = new Decoder(onInputChange, onMorse);

void startAdv();

void setup() {
  pinMode(straightPin, INPUT_PULLUP);

  Serial.begin(9600);

  decoder->setup();
  neopixel.setPixelColor(0, 16, 0, 0);
  neopixel.show();

  Bluefruit.Periph.setConnectCallback([](uint16_t a) {
    Serial.println("Now connected to a bluetooth host");
    neopixel.setPixelColor(0, 0, 0, 16);
    neopixel.show();
  });

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Morse Key");

  bledis.setManufacturer("Noskcaj Industries");
  bledis.setModel("Morse Key CTE-26003A");
  bledis.begin();
  Serial.println("Bluetooth discovery started");

  blehid.begin();
  Serial.println("Bluetooth HID started");

  startAdv();
}

void startAdv() {
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);

  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();

  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   *
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);   // number of seconds in fast mode
  Bluefruit.Advertising.start(0); // 0 = Don't stop advertising after n seconds

  Serial.println("Bluetooth advertising started");
}

void loop() { decoder->decode(); }

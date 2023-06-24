#pragma once

#include <Arduino.h>

#include "morsedefs.h"


namespace MorsePreferences {
// the preferences variable and their defaults

extern uint8_t sidetoneFreq;
extern uint8_t sidetoneVolume;
extern uint8_t keyermode;

extern uint8_t interWordSpace;

extern uint8_t echoToneShift;

////// end of variables stored in preferences


} // namespace MorsePreferences

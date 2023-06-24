/******************************************************************************************************************************
 *  Software for the Morserino-32 (M32) multi-functional Morse code machine, based on the Heltec WiFi LORA (ESP32) module   ***
 *  Copyright (C) 2018-2021  Willi Kraml, OE1WKL                                                                            ***
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with this program.
 *  If not, see <https://www.gnu.org/licenses/>.
 *****************************************************************************************************************************/

#pragma once

enum echoStates {
  START_ECHO,
  SEND_WORD,
  REPEAT_WORD,
  GET_ANSWER,
  COMPLETE_ANSWER,
  EVAL_ANSWER
};
enum morserinoMode // the states the morserino can be in - selected intop level
                   // menu
{
  morseKeyer,
  loraTrx,
  wifiTrx,
  morseTrx,
  morseGenerator,
  echoTrainer,
  morseDecoder,
  shutDown,
  measureNF,
  invalid
};

enum DECODER_STATES // state machine for decoding CW
{
  LOW_,
  HIGH_,
  INTERELEMENT_,
  INTERCHAR_
};

const int straightPin = 10;
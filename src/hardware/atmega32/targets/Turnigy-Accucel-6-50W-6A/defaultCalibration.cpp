/*
    cheali-charger - open source firmware for a variety of LiPo chargers
    Copyright (C) 2015  Paweł Stawicki. All right reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "AnalogInputsPrivate.h"
#include "memory.h"
#include "Utils.h"

const AnalogInputs::DefaultValues AnalogInputs::inputsP_[] PROGMEM = {

    {{0,  0},         {24646,  11357}},   //Vout_plus_pin
    {{0,  0},         {24646,  11357}},   //Vout_minus_pin
    {{1075,  100},         {9701,  1000}},   //Ismps
    {{4096,  100},         {12233,  300}},   //Idischarge

    {{0,  0},         {0,  0}},   //VoutMux
    {{0,  0},         {0,  0}},   //Tintern
    {{0,  0},         {51758,  15230}},   //Vin
    {{19650,  2980},         {18700,  6000}},   //Textern

    {{0,  0},         {49533,  3782}},   //Vb0_pin
    {{0,  0},         {49533,  3782}},   //Vb1_pin
    {{0,  0},         {50504,  7566}},   //Vb2_pin
    {{0,  0},         {49751,  3792}},   //Vb3_pin
    {{0,  0},         {54976,  4197}},   //Vb4_pin
    {{0,  0},         {54400,  4197}},   //Vb5_pin
    {{0,  0},         {54400,  4197}},   //Vb6_pin


    {{1070,  100},         {9700,  1000}},   //IsmpsSet
    {{1490,  100},         {4500,  300}},   //IdischargeSet
};

namespace {
    void assert() {
        STATIC_ASSERT(sizeOfArray(AnalogInputs::inputsP_) == AnalogInputs::PHYSICAL_INPUTS);
    }
}

/*
    cheali-charger - open source firmware for a variety of LiPo chargers
    Copyright (C) 2013  Paweł Stawicki. All right reserved.

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
#include <Arduino.h>

#include "SerialLog.h"
#include "Hardware.h"
#include "Timer.h"
#include "LcdPrint.h"
#include "Program.h"

namespace SerialLog {
    enum State { On, Off, Starting };
    uint32_t startTime;
    State state;
    uint8_t CRC;
    AnalogInputs::Name logging[] = {
            AnalogInputs::VoutBalancer,
            AnalogInputs::Iout,
            AnalogInputs::Cout,
            AnalogInputs::Pout,
            AnalogInputs::Eout,
            AnalogInputs::Textern,
            AnalogInputs::Tintern,
            AnalogInputs::Vin,
            AnalogInputs::Vb1,
            AnalogInputs::Vb2,
            AnalogInputs::Vb3,
            AnalogInputs::Vb4,
            AnalogInputs::Vb5,
            AnalogInputs::Vb6,
    };
}


void SerialLog::initialize()
{
#ifdef ENABLE_SERIAL_LOG
#ifndef ENABLE_SERIAL_LOG_WAIT
    Serial.begin(SERIAL_SPEED);
#endif
    state = Off;
#endif //ENABLE_SERIAL_LOG
}

void SerialLog::powerOn()
{
#ifdef ENABLE_SERIAL_LOG
    if(state != Off)
        return;
    state = Starting;
#endif //ENABLE_SERIAL_LOG
}

void SerialLog::powerOff()
{
#ifdef ENABLE_SERIAL_LOG
    state = Off;
#endif //ENABLE_SERIAL_LOG
}

void SerialLog::send()
{
#ifdef ENABLE_SERIAL_LOG

    if(state == Off)
        return;

#ifdef ENABLE_SERIAL_LOG_WAIT
    Serial.begin(SERIAL_SPEED);
#endif

    if(state == Starting) {
        startTime = Timer::getMiliseconds();
        state = On;
    }

    uint32_t t = Timer::getMiliseconds();
    sendTime(t);

#ifdef ENABLE_SERIAL_LOG_WAIT
    Serial.flush();
    Serial.end();
    pinMode(10, INPUT);
#endif
#endif //ENABLE_SERIAL_LOG
}


void SerialLog::printChar(char c)
{
    Serial.print(c);
    CRC^=c;
}
void SerialLog::printD()
{
    printChar(';');
}

void SerialLog::printString(char *s)
{
    while(*s) {
        printChar(*s);
        s++;
    }
}

void SerialLog::printUInt(uint16_t x)
{
    char buf[8];
    char *str = buf;
    uint8_t maxSize = 7;
    ::printUInt(str, maxSize, x);
    printString(buf);
}


void SerialLog::sendTime(uint32_t t)
{
    if(state != On)
        return;

    CRC = 0;
    t-=startTime;
    printChar('$');
    printUInt(1);   //channel
    printD();
    printUInt(Program::programState_);   //state
    printD();

    printUInt(t/1000);   //timestamp
    printChar('.');
    printUInt((t/100)%10);   //timestamp
    printD();

    //analog inputs
    for(int8_t i=0;i < sizeOfArray(logging);i++) {
        printUInt(AnalogInputs::getRealValue(logging[i]));
        printD();
    }
    //checksum
    printUInt(CRC);
    printChar('\r');
    printChar('\n');
}



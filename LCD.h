/*
   LCD.h  - Library for SPI-type LCDs

   Created by Neal Pisenti, 2015
   JQI - Joint Quantum Institute

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

#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
#include "SPI.h"


//! Typedef for LCD display text
typedef char * dtext_t[2];

class LCD {


    public:
    //! Constructor for LCD class.
    /*!
        reset: reset pin
        register_select: RS pin
        cs: chip select pin
    */
    LCD(int reset, int register_select, int cs);

    void init();

    void write(char * text, byte addr);

    void write(dtext_t text);

    void write(char data);


    void write_cmd(byte cmd);

    void clear();

    private:
    int _reset, _cs, _rs;

};



#endif

/*
   LCD.cpp  - Library for SPI-type LCDs

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

#include "LCD.h"


LCD::LCD(int reset, int register_select, int cs){
    _reset = reset;
    _rs = register_select;
    _cs = cs;

    pinMode(_reset, OUTPUT);
    pinMode(_rs, OUTPUT);
    pinMode(_cs, OUTPUT);

    digitalWrite(_reset, HIGH);
    digitalWrite(_rs, HIGH);
    digitalWrite(_cs, HIGH);

}

void LCD::init(){
    digitalWrite(_reset, LOW);
    delay(2);
    LCD::write_cmd(0x30); // wakeup
    delay(2);
    digitalWrite(_reset, HIGH);
    LCD::write_cmd(0x30); // wakeup
    LCD::write_cmd(0x30); // wakeup

    LCD::write_cmd(0x39); // function set
    LCD::write_cmd(0x14);   // internal osc frequency
    LCD::write_cmd(0x56);   // power control
    LCD::write_cmd(0x6D);   // follower control

    LCD::write_cmd(0x70);   // contrast
    LCD::write_cmd(0x0C);   // display on
    LCD::write_cmd(0x06);   // entry mode
    LCD::write_cmd(0x01);   // clear

    delay(10);
}

void LCD::write(char data){
    digitalWrite(_cs, LOW);
    digitalWrite(_rs, HIGH);
    delay(2);
    SPI.transfer(data);
    delay(2);
    digitalWrite(_cs, HIGH);
}

void LCD::write(char * text, byte addr){

    addr += 0x80;   // additional bit set in DB7;
    LCD::write_cmd(addr);

    int i = 0;
    while(text[i] != '\0' && i < 16){
        LCD::write(text[i]);
        i++;
    }
}

void LCD::write(dtext_t text){
    LCD::write(text[0], 0x00);
    LCD::write(text[1], 0x40);
}

void LCD::write_cmd(byte data){
    digitalWrite(_cs, LOW);
    digitalWrite(_rs, LOW);
    delay(2);
    SPI.transfer(data);
    delay(2);
    digitalWrite(_cs, HIGH);
}

void LCD::clear(){
    LCD::write_cmd(0x01);
}

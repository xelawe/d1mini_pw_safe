

/*
  Copyright (c) 2017, Embedded Adventures, www.embeddedadventures.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  - Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

  - Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  - Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

  Contact us at admin [at] embeddedadventures.com
*/

//Sample sketch for the EPD-200200B ePaper Display

#include <SPI.h>
#include <draw.h>
#include <SSD1607.h>
#include "cylogo.h"

#define DCPIN   12
#define CSPIN   2
#define BUSYPIN 5
#define RSTPIN  15

/* Hardware SPI pins are used for the ESP32/ESP8266/ATmega/ATtiny based boards
    ESP8266
      MOSI - IO13
      SCK  - IO14
    ESP32
      MOSI - IO23
      SCK  - IO18
    ATmega/ATtiny
      MOSI - 11
      SCK  - 13
*/

SSD1607 epd(CSPIN, DCPIN, BUSYPIN, RSTPIN);


void drawLogo(draw_x_type x, draw_y_type y) {
  char lv_buffer[20];

  draw_clear_screen();
  delay(100);
  draw_bitmap(x, y, 1, cylogo);

  draw_fonts_print_str(DRAW_FONT_12DOUBLE_ID, x + 70, y - 12, 128, 0, 2, "CYTRON");
  draw_fonts_print_str(DRAW_FONT_12DOUBLE_ID, x + 70, y - 32, 128, 0, 2, "PASSWORD SAFE");

  draw_fonts_print_str(DRAW_FONT_12DOUBLE_ID, x, y - 80, 128, 0, 2, "SEAL #");
  sealnbr.toCharArray(lv_buffer, sealnbr.length() + 1);
  draw_fonts_print_str(DRAW_FONT_12DOUBLE_ID, x + 50, y - 80, 128, 0, 2, lv_buffer);

}


void drawVoid(draw_x_type x, draw_y_type y) {

  draw_fonts_print_str(DRAW_FONT_12DOUBLE_ID, x - 50, y - 92, 128, 0, 2, "---- ALARM ----");
  //draw_bitmap(x -32 , y - 15, 1, alertpicl);
  //draw_bitmap(x , y - 15, 1, alertpicr);
  draw_bitmap(x - 32 , y - 15, 1, alertpic);


}

void init_epaper() {

  draw_init(EPD_HT, EPD_WD, 1);
  draw_fonts_init();

  epd.invert(true);
  epd.init();

}

//This function is necessary for using the ePaper Display
void drv_paint() {
  epd.displayFullRev(draw_buffer);
}

void paint_epaper() {
  drawLogo(20, 180);
}

void mark_epaper() {
  drawVoid(100, 100);
}

void draw_epaper() {
  draw_paint();
}


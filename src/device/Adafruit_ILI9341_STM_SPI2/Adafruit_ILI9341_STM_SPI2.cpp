#if defined(STM32F1)
/*
  See rights and use declaration in License.h
  This library has been modified for the Maple Mini.
  Includes DMA transfers on DMA1 CH2 and CH3.
*/
#include <avr/pgmspace.h>
#include <limits.h>
#include <libmaple/dma.h>
#include "../../../include/device/Adafruit_ILI9341_STM_SPI2/Adafruit_ILI9341_STM_SPI2.h"
#include "pins_arduino.h"
#include "wiring_private.h"
#include <SPI.h> // Using library SPI in folder: D:\Documents\Arduino\hardware\STM32\STM32F1XX\libraries\SPI

SPIClass SPITWO(2);



// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
lamb::device::Adafruit_ILI9341_STM_SPI2::Adafruit_ILI9341_STM_SPI2(int8_t cs, int8_t dc, int8_t rst) : Adafruit_GFX(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT) {
 _cs   = cs;
 _dc   = dc;
 _rst  = rst;
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::spiwrite(uint16_t c) {
 SPITWO.write(c);
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::writecommand(uint8_t c) {
 *dcport &=  ~dcpinmask;
 *csport &= ~cspinmask;

 spiwrite(c);

 *csport |= cspinmask;
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::writedata(uint8_t c) {
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;

 spiwrite(c);

 *csport |= cspinmask;
}

// If the SPI library has transaction support, these functions
// establish settings and protect from interference from other
// libraries.  Otherwise, they simply do nothing.
#ifdef SPI_HAS_TRANSACTION
static inline void spi_begin(void) __attribute__((always_inline));
static inline void spi_begin(void) {
#ifdef __STM32F1__
 SPITWO.beginTransaction(SPISettings(36000000));
#else
 SPITWO.beginTransaction(SPISettings(8000000));
#endif
}
static inline void spi_end(void) __attribute__((always_inline));
static inline void spi_end(void) {
 SPITWO.endTransaction();
}
#else
#define spi_begin()
#define spi_end()
#endif

// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in PROGMEM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80


// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in PROGMEM byte array.
void lamb::device::Adafruit_ILI9341_STM_SPI2::commandList(uint8_t *addr) {
 return;
  
 uint8_t  numCommands, numArgs;
 uint16_t ms;

 numCommands = pgm_read_byte(addr++);   // Number of commands to follow
 while (numCommands--) {                // For each command...
  writecommand(pgm_read_byte(addr++)); //   Read, issue command
  numArgs  = pgm_read_byte(addr++);    //   Number of args to follow
  ms       = numArgs & DELAY;          //   If hibit set, delay follows args
  numArgs &= ~DELAY;                   //   Mask out delay bit
  while (numArgs--) {                  //   For each argument...
   writedata(pgm_read_byte(addr++));  //     Read, issue argument
  }

  if (ms) {
   ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
   if (ms == 255) ms = 500;    // If 255, delay for 500 ms
   delay(ms);
  }
 }
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::begin(void) {

 if (_rst > 0) {
  pinMode(_rst, OUTPUT);
  digitalWrite(_rst, LOW);
 }
	
 pinMode(_dc, OUTPUT);   
 pinMode(_cs, OUTPUT);

 csport    = portOutputRegister(digitalPinToPort(_cs));
 cspinmask = digitalPinToBitMask(_cs);
 dcport    = portOutputRegister(digitalPinToPort(_dc));
 dcpinmask = digitalPinToBitMask(_dc);

 SPITWO.beginTransaction(SPISettings(36000000));

 // toggle RST low to reset
 if (_rst > 0) {
  digitalWrite(_rst, HIGH);
  delay(5);
  digitalWrite(_rst, LOW);
  delay(20);
  digitalWrite(_rst, HIGH);
  delay(150);
 }

 spi_begin();

 writecommand(0xEF);
 writedata(0x03);
 writedata(0x80);
 writedata(0x02);
 	 
 writecommand(0xCF);
 writedata(0x00);
 writedata(0XC1);
 writedata(0X30);

 writecommand(0xED);
 writedata(0x64);
 writedata(0x03);
 writedata(0X12);
 writedata(0X81);

 writecommand(0xE8);
 writedata(0x85);
 writedata(0x00);
 writedata(0x78);

 writecommand(0xCB);
 writedata(0x39);
 writedata(0x2C);
 writedata(0x00);
 writedata(0x34);
 writedata(0x02);

 writecommand(0xF7);
 writedata(0x20);

 writecommand(0xEA);
 writedata(0x00);
 writedata(0x00);

 writecommand(ILI9341_PWCTR1);    //Power control
 writedata(0x23);   //VRH[5:0]

 writecommand(ILI9341_PWCTR2);    //Power control
 writedata(0x10);   //SAP[2:0];BT[3:0]

 writecommand(ILI9341_VMCTR1);    //VCM control
 writedata(0x3e); //�Աȶȵ���
 writedata(0x28);
 //return;
	 
 writecommand(ILI9341_VMCTR2);    //VCM control2
 writedata(0x86);  //--

 writecommand(ILI9341_MADCTL);    // Memory Access Control
 writedata(0x48);

 writecommand(ILI9341_PIXFMT);
 writedata(0x55);

 writecommand(ILI9341_FRMCTR1);
 writedata(0x00);
 writedata(0x18);

 writecommand(ILI9341_DFUNCTR);    // Display Function Control
 writedata(0x08);
 writedata(0x82);
 writedata(0x27);

 writecommand(0xF2);    // 3Gamma Function Disable
 writedata(0x00);

 writecommand(ILI9341_GAMMASET);    //Gamma curve selected
 writedata(0x01);

 writecommand(ILI9341_GMCTRP1);    //Set Gamma
 writedata(0x0F);
 writedata(0x31);
 writedata(0x2B);
 writedata(0x0C);
 writedata(0x0E);
 writedata(0x08);
 writedata(0x4E);
 writedata(0xF1);
 writedata(0x37);
 writedata(0x07);
 writedata(0x10);
 writedata(0x03);
 writedata(0x0E);
 writedata(0x09);
 writedata(0x00);

 writecommand(ILI9341_GMCTRN1);    //Set Gamma
 writedata(0x00);
 writedata(0x0E);
 writedata(0x14);
 writedata(0x03);
 writedata(0x11);
 writedata(0x07);
 writedata(0x31);
 writedata(0xC1);
 writedata(0x48);
 writedata(0x08);
 writedata(0x0F);
 writedata(0x0C);
 writedata(0x31);
 writedata(0x36);
 writedata(0x0F);
	 
 writecommand(ILI9341_SLPOUT);    //Exit Sleep

 spi_end();

 delay(120);
 
 spi_begin();

 writecommand(ILI9341_DISPON);    //Display on

 spi_end();
 
 SPITWO.setDataSize(SPI_CR1_DFF);
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::setAddrWindow(
 uint16_t x0,
 uint16_t y0,
 uint16_t x1,
 uint16_t y1
) {
 writecommand(ILI9341_CASET); // Column addr set
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;
 SPITWO.write(x0);
 SPITWO.write(x1);
  
 writecommand(ILI9341_PASET); // Row addr set
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;
 SPITWO.write(y0);
 SPITWO.write(y1);

 writecommand(ILI9341_RAMWR); // write to RAM
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::pushColor(uint16_t color) {
 spi_begin();
 
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;

 spiwrite(color);

 *csport |= cspinmask;

 spi_end();
}

void lamb::device::Adafruit_ILI9341_STM_SPI2::pushColors(void * colorBuffer, uint16_t nr_pixels, uint8_t async)
{
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;

 if (async==0) 
 {
  SPITWO.dmaSend(colorBuffer, nr_pixels, 1);
  *csport |= cspinmask;
 }
 else
 {
  SPITWO.dmaSendAsync(colorBuffer, nr_pixels, 1);
 }

}

void lamb::device::Adafruit_ILI9341_STM_SPI2::drawPixel(int16_t x, int16_t y, uint16_t color) {

 if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
  return;

 spi_begin();
 
 setAddrWindow(x, y, x + 1, y + 1);

 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;

 spiwrite(color);

 *csport |= cspinmask;

 spi_end();
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                                            uint16_t color) {

 // Rudimentary clipping
 if ((x >= _width) || (y >= _height || h < 1)) return;

 if ((y + h - 1) >= _height)
  h = _height - y;
 if (h < 2 ) {
  drawPixel(x, y, color);
  return;
 }

 //  if (hwSPI) spi_begin();

 setAddrWindow(x, y, x, y + h - 1);

 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;
  
#if defined (__STM32F1__)
 lineBuffer[0] = color;
 SPITWO.dmaSend(lineBuffer, h, 0);
#else
 uint8_t hi = color >> 8, lo = color;
 while (h--) {
  spiwrite(hi);
  spiwrite(lo);
 }
#endif
 *csport |= cspinmask;
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                                            uint16_t color) { 
 // Rudimentary clipping
 if ((x >= _width) || (y >= _height || w < 1))
  return;
 
 if ((x + w - 1) >= _width)  w = _width - x;
 
 if (w < 2 ) {
  drawPixel(x, y, color);
  return;
 }

//  if (hwSPI) spi_begin();
 
 setAddrWindow(x, y, x + w - 1, y);
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;

 lineBuffer[0] = color;
 SPITWO.dmaSend(lineBuffer, w, 0);

 *csport |= cspinmask;

// if (hwSPI) spi_end();
}

void lamb::device::Adafruit_ILI9341_STM_SPI2::fillScreen(uint16_t color) {
 setAddrWindow(0, 0, _width - 1, _height - 1);
 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;
 lineBuffer[0] = color;
 SPITWO.dmaSend(lineBuffer, (65535), 0);
 SPITWO.dmaSend(lineBuffer, ((_width * _height) - 65535), 0);
}

void lamb::device::Adafruit_ILI9341_STM_SPI2::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                                       uint16_t color) {

 // rudimentary clipping (drawChar w/big text requires this)
 if ((x >= _width) || (y >= _height || h < 1 || w < 1))
  return;

 if ((x + w - 1) >= _width)  w = _width  - x;

 if ((y + h - 1) >= _height) h = _height - y;

 if (w == 1 && h == 1) {
  drawPixel(x, y, color);
  return;
 }
  
 /* if (hwSPI) */ spi_begin();
 setAddrWindow(x, y, x + w - 1, y + h - 1);

 *dcport |=  dcpinmask;
 *csport &= ~cspinmask;

 lineBuffer[0] = color;
 
 if (w*h <= 65535) {
  SPITWO.dmaSend(lineBuffer, (w*h), 0);
 }
 else {
  SPITWO.dmaSend(lineBuffer, (65535), 0);
  SPITWO.dmaSend(lineBuffer, ((w*h) - 65535), 0);
 }

 *csport |= cspinmask;
 
 /* if (hwSPI) */ spi_end();
}

/*
 * Draw lines faster by calculating straight sections and drawing them with fastVline and fastHline.
 */
void lamb::device::Adafruit_ILI9341_STM_SPI2::drawLine(
 int16_t x0,
 int16_t y0,
 int16_t x1,
 int16_t y1,
 uint16_t color
) {
 if ((y0 < 0 && y1 <0) || (y0 > _height && y1 > _height)) return;
 if ((x0 < 0 && x1 <0) || (x0 > _width && x1 > _width)) return;
 if (x0 < 0) x0 = 0;
 if (x1 < 0) x1 = 0;
 if (y0 < 0) y0 = 0;
 if (y1 < 0) y1 = 0;

 if (y0 == y1) {
  if (x1 > x0) {
   drawFastHLine(x0, y0, x1 - x0 + 1, color);
  }
  else if (x1 < x0) {
   drawFastHLine(x1, y0, x0 - x1 + 1, color);
  }
  else {
   drawPixel(x0, y0, color);
  }
  
  return;
 }
 else if (x0 == x1) {
  if (y1 > y0) {
   drawFastVLine(x0, y0, y1 - y0 + 1, color);
  }
  else {
   drawFastVLine(x0, y1, y0 - y1 + 1, color);
  }
  
  return;
 }

 bool steep = abs(y1 - y0) > abs(x1 - x0);

 if (steep) {
  swap(x0, y0);
  swap(x1, y1);
 }
 
 if (x0 > x1) {
  swap(x0, x1);
  swap(y0, y1);
 }

 int16_t dx, dy;
 dx = x1 - x0;
 dy = abs(y1 - y0);

 int16_t err = dx / 2;
 int16_t ystep;

 if (y0 < y1) {
  ystep = 1;
 }
 else {
  ystep = -1;
 }

 int16_t xbegin = x0;

 lineBuffer[0] = color;

 *csport &= ~cspinmask;

 if (steep) {
  for (; x0 <= x1; x0++) {
   err -= dy;

   if (err < 0) {
    int16_t len = x0 - xbegin;

    if (len) {
     drawFastVLine (y0, xbegin, len + 1, color);
     //writeVLine_cont_noCS_noFill(y0, xbegin, len + 1);
    }
    else {
     drawPixel(y0, x0, color);
     //writePixel_cont_noCS(y0, x0, color);
    }
    xbegin = x0 + 1;
    y0 += ystep;
    err += dx;
   }
  }
  if (x0 > xbegin + 1) {
   //writeVLine_cont_noCS_noFill(y0, xbegin, x0 - xbegin);
   drawFastVLine(y0, xbegin, x0 - xbegin, color);
  }
 }
 else {
  for (; x0 <= x1; x0++) {
   err -= dy;
   if (err < 0) {
    int16_t len = x0 - xbegin;
    if (len) {
     drawFastHLine(xbegin, y0, len + 1, color);
     //writeHLine_cont_noCS_noFill(xbegin, y0, len + 1);
    }
    else {
     drawPixel(x0, y0, color);
     //writePixel_cont_noCS(x0, y0, color);
    }
    xbegin = x0 + 1;
    y0 += ystep;
    err += dx;
   }
  }
  if (x0 > xbegin + 1) {
   //writeHLine_cont_noCS_noFill(xbegin, y0, x0 - xbegin);
   drawFastHLine(xbegin, y0, x0 - xbegin, color);
  }
 }

 *csport |= cspinmask;
}

// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t lamb::device::Adafruit_ILI9341_STM_SPI2::color565(uint8_t r, uint8_t g, uint8_t b) {
 return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

void lamb::device::Adafruit_ILI9341_STM_SPI2::setRotation(uint8_t m) {
 /* if (hwSPI) */ spi_begin();
 /* if (hwSPI) */ SPITWO.setDataSize(0);
 writecommand(ILI9341_MADCTL);
 rotation = m % 4; // can't be higher than 3
 switch (rotation) {
 case 0:
  writedata(MADCTL_MX | MADCTL_BGR);
  _width  = ILI9341_TFTWIDTH;
  _height = ILI9341_TFTHEIGHT;
  break;
 case 1:
  writedata(MADCTL_MV | MADCTL_BGR);
  _width  = ILI9341_TFTHEIGHT;
  _height = ILI9341_TFTWIDTH;
  break;
 case 2:
  writedata(MADCTL_MY | MADCTL_BGR);
  _width  = ILI9341_TFTWIDTH;
  _height = ILI9341_TFTHEIGHT;
  break;
 case 3:
  writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
  _width  = ILI9341_TFTHEIGHT;
  _height = ILI9341_TFTWIDTH;
  break;
 }
 /* if (hwSPI) */ SPITWO.setDataSize(SPI_CR1_DFF);
 /* if (hwSPI) */ spi_end();
}


void lamb::device::Adafruit_ILI9341_STM_SPI2::invertDisplay(boolean i) {
 /* if (hwSPI) */ spi_begin();
 writecommand(i ? ILI9341_INVON : ILI9341_INVOFF);
 /* if (hwSPI) */ spi_end();
}

uint8_t lamb::device::Adafruit_ILI9341_STM_SPI2::spiread(void) {
 uint8_t r = 0;

 /* if (hwSPI) */ {
  r = SPITWO.transfer(0x00);
 }
 
 return r;
}

#endif

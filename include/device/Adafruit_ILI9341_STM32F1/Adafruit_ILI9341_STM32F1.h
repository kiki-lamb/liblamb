#if defined(STM32F1)
/*
  See rights and use declaration in License.h
  This library has been modified for the Maple Mini
*/

#ifndef LAMB_ADAFRUIT_ILI9341H_STM32F1
#define LAMB_ADAFRUIT_ILI9341H_STM32F1

#include <Adafruit_GFX_AS.h>
#include <SPI.h> // Using library SPI in folder: D:\Documents\Arduino\hardware\STM32\STM32F1XX\libraries\SPI

#ifndef swap
#define swap(a, b) { int16_t t = a; a = b; b = t; }
#endif

#define ILI9341_TFTWIDTH    240
#define ILI9341_TFTHEIGHT   320

#define ILI9341_NOP         0x00
#define ILI9341_SWRESET     0x01
#define ILI9341_RDDID       0x04
#define ILI9341_RDDST       0x09

#define ILI9341_SLPIN       0x10
#define ILI9341_SLPOUT      0x11
#define ILI9341_PTLON       0x12
#define ILI9341_NORON       0x13

#define ILI9341_RDMODE      0x0A
#define ILI9341_RDMADCTL    0x0B
#define ILI9341_RDPIXFMT    0x0C
#define ILI9341_RDIMGFMT    0x0A
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF      0x20
#define ILI9341_INVON       0x21
#define ILI9341_GAMMASET    0x26
#define ILI9341_DISPOFF     0x28
#define ILI9341_DISPON      0x29

#define ILI9341_CASET       0x2A
#define ILI9341_PASET       0x2B
#define ILI9341_RAMWR       0x2C
#define ILI9341_RAMRD       0x2E

#define ILI9341_PTLAR       0x30
#define ILI9341_MADCTL      0x36
#define ILI9341_PIXFMT      0x3A

#define ILI9341_FRMCTR1     0xB1
#define ILI9341_FRMCTR2     0xB2
#define ILI9341_FRMCTR3     0xB3
#define ILI9341_INVCTR      0xB4
#define ILI9341_DFUNCTR     0xB6

#define ILI9341_PWCTR1      0xC0
#define ILI9341_PWCTR2      0xC1
#define ILI9341_PWCTR3      0xC2
#define ILI9341_PWCTR4      0xC3
#define ILI9341_PWCTR5      0xC4
#define ILI9341_VMCTR1      0xC5
#define ILI9341_VMCTR2      0xC7

#define ILI9341_RDID1       0xDA
#define ILI9341_RDID2       0xDB
#define ILI9341_RDID3       0xDC
#define ILI9341_RDID4       0xDD

#define ILI9341_GMCTRP1     0xE0
#define ILI9341_GMCTRN1     0xE1

// #define ILI9341_PWCTR6   0xFC

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

namespace lamb {
 namespace device {
  class Adafruit_ILI9341_STM32F1 : public Adafruit_GFX {

  public:
   Adafruit_ILI9341_STM32F1(SPIClass & spi, int8_t _CS, int8_t _DC);      
   void     begin           (void);
   void     setAddrWindow   (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
   void     pushColor       (uint16_t color);
   void     pushColors      (void * colorBuffer, uint16_t nr_pixels, uint8_t async);
   void     fillScreen      (uint16_t color);
   void     drawLine        (int16_t x0, int16_t y0,int16_t x1, int16_t y1, uint16_t color);
   void     drawPixel       (int16_t x, int16_t y, uint16_t color);
   void     drawFastVLine   (int16_t x, int16_t y, int16_t h, uint16_t color);
   void     drawFastHLine   (int16_t x, int16_t y, int16_t w, uint16_t color);
   void     fillRect        (int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
   void     setRotation     (uint8_t r);
   void     invertDisplay   (boolean i);
   uint16_t color565        (uint8_t r, uint8_t g, uint8_t b);
   void     spiwrite        (uint16_t);
   void     writecommand    (uint8_t c);
   void     writedata       (uint8_t d);
   void     commandList     (uint8_t *addr);
   uint8_t  spiread         (void);
   
  private:
   SPIClass *        _spi;
   uint8_t           tabcolor;
   volatile uint32 * dcport;
   volatile uint32 * csport;
   
   uint32_t _cs;
   uint32_t _dc;
   uint32_t cspinmask;
   uint32_t dcpinmask;
   uint16_t lineBuffer[ILI9341_TFTHEIGHT]; // DMA buffer. 16bit color data per pixel

   inline void spi_begin(void) __attribute__((always_inline)) {
    _spi->beginTransaction(SPISettings(36000000));
   }
   
   inline void spi_end(void) __attribute__((always_inline)) {
    _spi->endTransaction();
   }
  };
 }
}
#endif
#endif

#ifndef WS2812B_H
#define WS2812B_H

#include <RGB.h>
#include "stdint.h"
#include <array>

namespace WSCONST{
  constexpr uint8_t WS2812B_MAX_LEDS = 255;
  constexpr uint8_t BITS_PER_WORD = 8;
  constexpr uint8_t WORDS_PER_LED = 3;
  constexpr uint8_t BITS_PER_LED = BITS_PER_WORD * WORDS_PER_LED;
  constexpr uint8_t RESET_LENGTH = 3;
  constexpr uint8_t ZERO_BITS = 0b11000000;
  constexpr uint8_t ONE_BITS = 0b11111100;
}

template<const int LENGTH>
class WS2812{
  private:
    // function pointer to the hardware SPI function
    void spi_transfer(uint8_t* data, uint8_t length); // could we use a bind function here?
  public:
    WS2812() {
      for (int i = 0; i < LENGTH; i++) {
        pixels[i] = RGB_t<uint8_t>(0, 0, 0);
      }
    }
    RGB_t<uint8_t> pixels[LENGTH];
    uint8_t bitsbuffer[LENGTH * WSCONST::BITS_PER_LED + 1 + WSCONST::RESET_LENGTH]; // we use 1 byte per bit
    void setPixel(int index, RGB_t<uint8_t> color) {
      pixels[index] = color;
    }
    void show() {
      uint8_t *buf = bitsbuffer; //first byte is zero to reset
      
      using namespace WSCONST;
      for (int currentled = 0; currentled < LENGTH; currentled++){

        for(int i = 0; i < 8; i++){
        	/*    if(pixels[currentled].g & (1 << i)){
	          *buf = ONE_BITS;
	        }
	        else{
	          *buf = ZERO_BITS;
	        }
	        buf++;
	      }
	      // red
	      for(int i = 0; i < 8; i++){
	        if(pixels[currentled].r & (1 << i)){
	          *buf = ONE_BITS;
	        }
	        else{
	          *buf = ZERO_BITS;
	        }
	        buf++;
	      }
	      // blue
	      for(int i = 0; i < 8; i++){
	        if(pixels[currentled].b & (1 << i)){
	          *buf = ONE_BITS;
	        }
	        else{
	          *buf = ZERO_BITS;
	        }
	        buf++;
	      }
	    }*/
          buf[currentled*24 + i + 0] = pixels[currentled].g & (1 << i) ? ONE_BITS : ZERO_BITS;
          buf[currentled*24 + i + 8] = pixels[currentled].r & (1 << i) ? ONE_BITS : ZERO_BITS;
          buf[currentled*24 + i +16] = pixels[currentled].b & (1 << i) ? ONE_BITS : ZERO_BITS;
          }
      }
    }
    void clear() {
      for (int i = 0; i < LENGTH; i++) {
        pixels[i] = RGB_t<uint8_t>(0, 0, 0);
      }
    }

};


#endif // WS2812B_H
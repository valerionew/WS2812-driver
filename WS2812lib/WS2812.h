#ifndef WS2812B_H
#define WS2812B_H

#include <RGB.h>
#include "stdint.h"
#include <array>
#include <functional>

namespace WSCONST{
  constexpr uint8_t WS2812B_MAX_LEDS = 255;
  constexpr uint8_t BITS_PER_WORD = 8;
  constexpr uint8_t WORDS_PER_LED = 3;
  constexpr uint8_t BITS_PER_LED = BITS_PER_WORD * WORDS_PER_LED;
  constexpr uint8_t RESET_LENGTH = 3;
  constexpr uint8_t ZERO_BITS = 0b10000000;
  constexpr uint8_t ONE_BITS  = 0b11111100;
}

template<const int LENGTH>
class WS2812{
  private:
    std::array<RGB_t<uint8_t>, LENGTH> pixels;
    volatile uint8_t bitsbuffer[LENGTH * WSCONST::BITS_PER_LED + 1 + WSCONST::RESET_LENGTH]; // we use 1 byte per bit

  // Object for SPI communication  
    std::function<void(uint8_t*, uint16_t)> spi_transfer;

  public:
    WS2812(std::function<void(uint8_t*, uint16_t)> spi_transfer) : spi_transfer(spi_transfer){
      for (int i = 0; i < LENGTH; i++) {
        pixels[i] = RGB_t<uint8_t>(0, 0, 0);
      }
    }
    void setPixel(const int index, const RGB_t<uint8_t> color) {
    	// it should really check that index is a valid index for the array
      pixels[index] = color;
    }
    void show() {
      uint8_t *buf = (uint8_t*) bitsbuffer; //first byte is zero to reset
      
      using namespace WSCONST;
      for (int currentled = 0; currentled < LENGTH; currentled++){

        for(int i = 0; i < 8; i++){
          buf[currentled*24 + i + 0] = pixels[currentled].g & (1 << i) ? ONE_BITS : ZERO_BITS;
          buf[currentled*24 + i + 8] = pixels[currentled].r & (1 << i) ? ONE_BITS : ZERO_BITS;
          buf[currentled*24 + i +16] = pixels[currentled].b & (1 << i) ? ONE_BITS : ZERO_BITS;
          }
      }
      uint8_t zero = 0;
      spi_transfer(&zero, 1); // clear the bit first
      spi_transfer((uint8_t*)bitsbuffer, LENGTH * BITS_PER_LED + 1 + RESET_LENGTH);

    }
    void setFrame(const std::array<RGB_t<uint8_t>, LENGTH> colors) {
        pixels = colors;
    }
    void clear() {
      for (int i = 0; i < LENGTH; i++) {
        pixels[i] = RGB_t<uint8_t>(0, 0, 0);
      }
    }

};


#endif // WS2812B_H

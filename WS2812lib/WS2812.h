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
    volatile uint8_t bitsbuffer[LENGTH * WSCONST::BITS_PER_LED + 1 + WSCONST::RESET_LENGTH]; // we use 1 byte per bit

  // Object for SPI communication  
    std::function<void(uint8_t*, uint16_t)> spi_transfer;


  public:
    WS2812(std::function<void(uint8_t*, uint16_t)> spi_transfer) : spi_transfer(spi_transfer){
      for (int i = 0; i < LENGTH; i++) {
        setPixel(i,(RGB_t<uint8_t>){0, 0, 0});
      }
    }
    void setPixel(const int index, const RGB_t<uint8_t> color) {
    	// it should really check that index is a valid index for the array

      using namespace WSCONST;
      for(int i = 0; i < 8; i++){
        bitsbuffer[index*24 + i + 0] = color.g & (1 << i) ? ONE_BITS : ZERO_BITS;
        bitsbuffer[index*24 + i + 8] = color.r & (1 << i) ? ONE_BITS : ZERO_BITS;
        bitsbuffer[index*24 + i +16] = color.b & (1 << i) ? ONE_BITS : ZERO_BITS;
      }
    }
    void show() {      
      using namespace WSCONST;

      /*uint8_t zeros[50];
      std::fill_n(zeros, 50, 0);
      spi_transfer(zeros, 1); // clear the bit first*/
      
      uint8_t zero = 0;
      spi_transfer(&zero, 1); // clear the bit first
      
      spi_transfer((uint8_t*)bitsbuffer, LENGTH * BITS_PER_LED + 1 + RESET_LENGTH);
      // to be tested
      // spi_transfer(zeros, 50); //reset

    }

    void clear() {
      for (int i = 0; i < LENGTH; i++) {
        setPixel(i,(RGB_t<uint8_t>){0, 0, 0});
      }
    }

};


#endif // WS2812B_H

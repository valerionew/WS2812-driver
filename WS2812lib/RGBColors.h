#ifndef RGBCOLORS_H
#define RGBCOLORS_H

#include <RGB.h>
#include <array>
#include <stdint.h>

namespace RGBColors{
  const RGB_t<uint8_t>	violet  ( 75,   0, 130);
  const RGB_t<uint8_t>	blue	  (  0,   0, 255);
  const RGB_t<uint8_t>	green	  (  0, 255,   0);
  const RGB_t<uint8_t>	yellow	(127, 255,   0);
  const RGB_t<uint8_t>	orange	(255,  50,   0);
  const RGB_t<uint8_t>	red		  (255,   0,   0);
  const RGB_t<uint8_t>	white	  (255, 255, 255);
  const RGB_t<uint8_t>	black	  (  0,   0,   0);
}

#endif // RGBCOLORS_H
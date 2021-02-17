#ifndef MANDELBROT_UTILS_H
#define MANDELBROT_UTILS_H

#include <cstdint>

// pack RGB as ARGB 32bit format
constexpr uint32_t pack_rgb(unsigned char r, unsigned char g, unsigned char b) {
    uint32_t ret = 0xff;    // let alpha channel 100%
    ret = ret << 8;
    ret = ret | r;
    ret = ret << 8;
    ret = ret | g;
    ret = ret << 8;
    ret = ret | b;
    return ret;
}

#endif //MANDELBROT_UTILS_H

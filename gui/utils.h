#ifndef MANDELBROT_UTILS_H
#define MANDELBROT_UTILS_H

#include <cstdint>

// pack RGB as ARGB 32bit format
constexpr std::uint32_t pack_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) noexcept {
    uint32_t ret = 0xff;    // let alpha channel 100%
    ret = ret << 8;
    ret = ret | r;
    ret = ret << 8;
    ret = ret | g;
    ret = ret << 8;
    ret = ret | b;
    return ret;
}

enum class argb : std::uint8_t {
    // offset
    alpha = 3,
    red   = 2,
    green = 1,
    blue  = 0,
};

template<argb Offset>
constexpr std::uint8_t pick(std::uint32_t color) noexcept {
    auto array = reinterpret_cast<unsigned char *>(&color);
    return array[static_cast<int>(Offset)];
}

#endif //MANDELBROT_UTILS_H

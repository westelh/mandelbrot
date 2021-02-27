#ifndef MANDELBROT_ANTI_ALIASING_H
#define MANDELBROT_ANTI_ALIASING_H

#include <cstdint>
#include <utility>
#include <span>
#include <functional>
#include "utils.h"

template<class Head, class... Tail>
constexpr auto sum(Head&& head, Tail&&... tail) noexcept {
    if constexpr (0 < sizeof...(tail)) {
        return head + sum(std::forward<Tail>(tail)...);
    } else {
        return head;
    }
}

template<class Float, class... Args>
constexpr Float average(Float&& least, Args&&... args) noexcept {
    return sum(std::forward<Float>(least), std::forward<Args>(args)...) / (sizeof...(args) + 1);
}

template<class... UINT32TColor>
std::uint32_t color_average(UINT32TColor&&... colors) noexcept {
    auto&& r = average(pick<argb::red>(std::forward<UINT32TColor>(colors))...);
    auto&& g = average(pick<argb::green>(std::forward<UINT32TColor>(colors))...);
    auto&& b = average(pick<argb::blue>(std::forward<UINT32TColor>(colors))...);
    return pack_rgb(r, g, b);
}

template<class DestContainer>
void average2x2(const std::span<const std::uint32_t> data, std::back_insert_iterator<DestContainer> dest, std::uint32_t dest_width) {
    const auto size_of_result = data.size() / 4;
    for (int i = 0; i < size_of_result; ++i) {
        dest = color_average(
                data[2 * i],
                data[2 * i + 1],
                data[2 * i + 2 * dest_width],
                data[2 * i + 2 * dest_width + 1]
        );
        dest++;
    }
}

#endif //MANDELBROT_ANTI_ALIASING_H

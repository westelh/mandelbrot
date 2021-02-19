#ifndef MANDELBROT_ANTI_ALIASING_H
#define MANDELBROT_ANTI_ALIASING_H

#include <cstdint>
#include <utility>
#include <span>
#include "utils.h"

constexpr auto sum() noexcept {
    return 0;
}

template<class Head, class... Tail>
constexpr auto sum(Head&& head, Tail&&... tail) noexcept(noexcept(head+sum())) {
    return head + sum(std::forward<Tail>(tail)...);
}

template<class Float, class... Args>
constexpr Float average(Float&& least, Args&&... args) noexcept(noexcept(sum())) {
    return sum(std::forward<Float>(least), std::forward<Args>(args)...) / (sizeof...(args) + 1);
}

// Method is a functor produces a new pixel from given pixels for anti aliasing.
template<class Method, class... Pixels>
constexpr std::uint32_t produce_by(Method method, Pixels... pixels) noexcept(noexcept(method(pixels...))) {
    return method(pixels...);
}

constexpr std::uint32_t average2x(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d) noexcept(noexcept(average(std::uint8_t{}, std::uint8_t{}))) {
    return pack_rgb(
                average(pick<argb::red>(a), pick<argb::red>(b), pick<argb::red>(c), pick<argb::red>(d)),
                average(pick<argb::green>(a), pick<argb::green>(b), pick<argb::green>(c), pick<argb::green>(d)),
                average(pick<argb::blue>(a), pick<argb::blue>(b), pick<argb::blue>(c), pick<argb::blue>(d))
            );
}

template<class Container, class Method>
void mix2x2(std::span<const std::uint32_t> data, std::back_insert_iterator<Container> dest, std::uint32_t dest_width, Method method) {
    const auto size_of_result = data.size() / 4;
    for (int i = 0; i < size_of_result; ++i) {
        dest = produce_by(method,
                           data[2 * i],
                           data[2 * i + 1],
                           data[2 * i + 2 * dest_width],
                           data[2 * i + 2 * dest_width + 1]
        );
        dest++;
    }
}

#endif //MANDELBROT_ANTI_ALIASING_H

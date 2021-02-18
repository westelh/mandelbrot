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

constexpr std::uint32_t average2x(std::uint32_t a, std::uint32_t b) noexcept(noexcept(average(std::uint8_t{}, std::uint8_t{}))) {
    return pack_rgb(
                average(pick<argb::red>(a), pick<argb::red>(b)),
                average(pick<argb::green>(a), pick<argb::green>(b)),
                average(pick<argb::blue>(a), pick<argb::blue>(b))
            );
}

template<unsigned int SampleCount, size_t DataExtent, size_t DestExtent, class Method>
void mix_for_every(const std::span<std::uint32_t, DataExtent> data, std::span<std::uint32_t, DestExtent> destination, Method method) {
    static_assert(SampleCount > 0, "SampleCount cannot be 0.");
    if constexpr (DestExtent != std::dynamic_extent) {
        static_assert(data.size() / SampleCount <= destination.size(), "Destination needs to be the same size of or larger than output");
    }

    constexpr auto size_after_mixing = data.size() / SampleCount;
    for (int i = 0; i < size_after_mixing; ++i) {
        destination[i] = produce_by(method, data[SampleCount*i], data[SampleCount*i+1]);
    }
}

#endif //MANDELBROT_ANTI_ALIASING_H

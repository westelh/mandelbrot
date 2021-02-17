#ifndef MANDELBROT_ANTI_ALIASING_H
#define MANDELBROT_ANTI_ALIASING_H

#include <cstdint>
#include <utility>

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

#endif //MANDELBROT_ANTI_ALIASING_H

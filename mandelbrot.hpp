#pragma once

#include <complex>
#include "bmp.hpp"

int calc_mandelbrot(const int n, std::complex<double> c);

int calc_julia(const int n, std::complex<double> z);

void mandelbrot_AA(const std::complex<double> center, const std::complex<double> range, const unsigned width, const unsigned height);

grid mandelbrot_bmp(const std::complex<double> center, const std::complex<double> range, const unsigned width, const unsigned height);

pixel gradation(const std::vector<pixel> waypoint, double p);

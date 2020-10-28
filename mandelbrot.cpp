#include "mandelbrot.hpp"
#include "bmp.hpp"
#include <limits>
#include <iostream>
#include <vector>
#include <math.h>

int calc_mandelbrot(const int n, std::complex<double> c){
	std::complex<double> z(0.0f, 0.0f);
	for (size_t i = 0; i < n; i++){
		z = std::pow(z, 2)+c;
		if (std::abs(z) == std::numeric_limits<double>::infinity()){
			return i;
		}
	}
	return n;
}

int calc_julia(const int n, std::complex<double> z){
	const std::complex<double> c(-0.21f, -0.65f);
	for (size_t i = 0; i < n; i++){
		z = std::pow(z, 2)+c;
		if (std::abs(z) == std::numeric_limits<double>::infinity()){
			return i;
		}
	}
	return n;
}

void mandelbrot_AA(const std::complex<double> center, const std::complex<double> range, const unsigned width, const unsigned height) {
	const std::complex<double> resolution(range.real()/width, range.imag()/height);
	const std::complex<double> cmpl(center.real()-range.real()/2, center.imag()-range.imag()/2);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			std::complex<double> hoge(cmpl.real()+j*resolution.real(), cmpl.imag()+i*resolution.imag());
			std::cout << (char)(calc_mandelbrot('~'-' ', hoge)+' ');
		}
		std::cout << std::endl;
	}
}

pixel gradation(const std::vector<pixel> waypoint, double p) {
	for (int i = 0; i < waypoint.size()-1; i++) {
		if (((double)(i+1)/(waypoint.size()-1)) > p) {
			double q = p - (double)i/(waypoint.size()-1);
			q /= (double)1/(waypoint.size()-1);
			pixel a;
			a.r = waypoint[i].r + (waypoint[i+1].r-waypoint[i].r)*q;
			a.g = waypoint[i].g + (waypoint[i+1].g-waypoint[i].g)*q;
			a.b = waypoint[i].b + (waypoint[i+1].b-waypoint[i].b)*q;
			return a;
		}
	}
	return waypoint[waypoint.size()-1];
}

grid mandelbrot_bmp(const std::complex<double> center, const std::complex<double> range, const unsigned width, const unsigned height) {
	grid data;
	data.resize(height);
	for (int i = 0; i < data.size(); i++) {
		data[i].resize(width);
	}
	// hassan
	std::vector<pixel> gradation_waypoint;
	gradation_waypoint.push_back(pixel(0x00,0x00,0x00));
	gradation_waypoint.push_back(pixel(0x00,0x00,0x80));
	gradation_waypoint.push_back(pixel(0x33,0xCC,0xCC));
	gradation_waypoint.push_back(pixel(0xFF,0xCC,0x00));
	gradation_waypoint.push_back(pixel(0xFF,0xFF,0xFF));
	gradation_waypoint.push_back(pixel(0x00,0x00,0x00));
	const std::complex<double> resolution(range.real()/width, range.imag()/height);
	const std::complex<double> start(center.real()-range.real()/2, center.imag()-range.imag()/2);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::complex<double> point(start.real()+j*resolution.real(), start.imag()+i*resolution.imag());
			int num = calc_mandelbrot(0xFF, point);
			data[i][j] = gradation(gradation_waypoint, (double)num/0xFF);
		}
	}
	return data;
}

#include <iostream>
#include <complex>
#include <limits>
#include "mandelbrot.hpp"
#include "bmp.hpp"

int main(){
	bmp_write file("mandelbrot.bmp");
	std::complex<double> center(-0.64f, 0.45f);
	std::complex<double> range((double)16/90, (double)9/90);
	grid data = mandelbrot_bmp(center, range, 1920*2, 1080*2);
	file.set_data(data);
	file.write();
	return 0;
}

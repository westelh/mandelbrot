#include <iostream>
#include <complex>
#include <limits>

int calc_mandel(const int n ,std::complex<double> c){
	std::complex<double> z(0.0f, 0.0f);
	for (size_t i = 0; i < n; i++){
		z = std::pow(z, 2)+c;
		if (std::abs(z) == std::numeric_limits<double>::infinity()){
			return i;
		}
	}
	return n;
}

void show_rect_mandel(const std::complex<double> center, const std::complex<double> range, const unsigned width, const unsigned height) {
	const std::complex<double> resolution(range.real()/width, range.imag()/height);
	std::complex<double> cmpl(center.real()-range.real()/2, center.imag()-range.imag()/2);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			std::complex<double> hoge(cmpl.real()+j*resolution.real(), cmpl.imag()+i*resolution.imag());
			std::cout << (char)(calc_mandel('~'-' ', hoge)+' ');
		}
		std::cout << std::endl;
	}
}

int main(const int argc, const char **argv){
	const int w = 120;
	const int h = 50;
	show_rect_mandel(std::complex<double>(0,0), std::complex<double>(3,3), w, h);
	return 0;
}

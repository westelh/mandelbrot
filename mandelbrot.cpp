#include "mandelbrot.hpp"
#include "bmp.hpp"
#include <limits>
#include <vector>
#include <cstdlib>
#include <future>
#include <chrono>
// #include <mpfr.h>
// #include <mpreal.h>

int calc_mandelbrot(const int n, complex_t c){
	complex_t z(0.0f, 0.0f);
	for (size_t i = 0; i < n; i++){
		z = std::pow(z, 2);
		z += c;
		if (abs(z) == std::numeric_limits<hogefloat_t>::infinity()) {
			return i;
		}
		// if (abs(z) > 2.0f) {
		// 	return i+10;
		// }
	}
	return n;
}

int calc_julia(const int n, complex_t z){
	complex_t c(-0.21f, -0.65f);
	for (size_t i = 0; i < n; i++){
		z = std::pow(z, 2)+c;
		if (abs(z) == std::numeric_limits<hogefloat_t>::infinity()){
			return i;
		}
	}
	return n;
}

void mandelbrot_AA(const complex_t center, const complex_t range, const unsigned width, const unsigned height) {
	const complex_t resolution(range.real()/width, range.imag()/height);
	const complex_t cmpl(center.real()-range.real()/2, center.imag()-range.imag()/2);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			complex_t hoge(cmpl.real()+j*resolution.real(), cmpl.imag()+i*resolution.imag());
			std::cout << (char)(calc_mandelbrot('~'-' ', hoge)+' ');
		}
		std::cout << std::endl;
	}
}

pixel gradation(const std::vector<pixel> waypoint, const double p) {
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
	return *waypoint.end();
}

int make_mandelbrot_thread(const complex_t start_all, const complex_t resolution, const int num_of_threads, const int offset, const std::vector<pixel> gradation_waypoint, const int height, const int width, grid& data) {
	const complex_t start = complex_t(start_all.real()+resolution.real()*offset, start_all.imag());
	for (int i = 0; i < width/num_of_threads; i++) {
		for (int j = 0; j < height; j++) {
			const complex_t point(start.real()+resolution.real()*num_of_threads*i, start.imag()+resolution.imag()*j);
			const int num = calc_mandelbrot(0xFF, point);
			data[i][j] = gradation(gradation_waypoint, (double)num/0xFF);
		}
	}
	return 0;
}

grid mandelbrot_bmp_multithread(const complex_t center, const complex_t range, const std::vector<pixel> gradation_waypoint, const unsigned width, const unsigned height, const int num_of_threads) {
	try {
		if ((width % num_of_threads) != 0) {
			throw std::runtime_error("num_of_threads(%d) must be a divisor of width(%d).\n");
		}
	}
	catch (std::exception &e){
		std::cerr << "Error: " << e.what() << '\n';
		std::abort();
	}

	const complex_t resolution(range.real()/width, range.imag()/height);
	const complex_t start(center.real()-range.real()/2, center.imag()-range.imag()/2);

	std::vector<grid> thread_data;
	thread_data.resize(num_of_threads);
	for (auto &a: thread_data) {
		a.resize(width/num_of_threads);
		for (auto &b: a) {
			b.resize(height);
		}
	}
	std::vector<std::future<int>> v;
	for (int i = 0; i < num_of_threads; i++) {
		v.push_back(std::async(std::launch::async, [=, &thread_data]{
			return make_mandelbrot_thread(start, resolution, num_of_threads, i, gradation_waypoint, height, width, std::ref(thread_data[i]));
		}));
	}
	for (int i = 0; i < v.size(); i++) {
		v[i].get();
	}

	grid data;
	data.resize(height);
	for (int i = 0; i < data.size(); i++) {
		data[i].resize(width);
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i][j] = thread_data[j%num_of_threads][j/num_of_threads][i];
		}
	}

	return data;
}

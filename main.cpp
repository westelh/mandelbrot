#include "mandelbrot.hpp"
#include "bmp.hpp"
#include <cstdlib>
#include <thread>

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		std::cerr << "Enter the file name after the executable file." << '\n';
		std::abort();
	}
	// diverge
	std::vector<pixel> gradation_waypoint;
	gradation_waypoint.push_back(pixel(0x00,0x00,0x00));
	gradation_waypoint.push_back(pixel(0x00,0x00,0x80));
	gradation_waypoint.push_back(pixel(0x33,0xCC,0xCC));
	gradation_waypoint.push_back(pixel(0xFF,0xCC,0x00));
	gradation_waypoint.push_back(pixel(0xFF,0xFF,0xFF));
	gradation_waypoint.push_back(pixel(0x00,0x00,0x00));
	// converge

	// mpfr::mpreal::set_default_prec(precision);
	bmp_write file(argv[1]);
	const unsigned width = 1920*2;
	const unsigned height = 1080*2;
	complex_t center(-0.6428f, 0.4507f);
	hogefloat_t width_range = (hogefloat_t)16/60;
	complex_t range(width_range, width_range*((hogefloat_t)height/width));
	grid data = mandelbrot_bmp_multithread(center, range, gradation_waypoint, width, height, std::thread::hardware_concurrency());
	file.set_data(data);
	file.write();
	return 0;
}

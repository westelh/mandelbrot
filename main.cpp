#include "mandelbrot.hpp"
#include "bmp.hpp"

int main(){
	// diverge
	std::vector<pixel> gradation_waypoint;
	gradation_waypoint.push_back(pixel(0x00,0x00,0x00));
	gradation_waypoint.push_back(pixel(0x00,0x00,0x80));
	gradation_waypoint.push_back(pixel(0x33,0xCC,0xCC));
	gradation_waypoint.push_back(pixel(0xFF,0xCC,0x00));
	gradation_waypoint.push_back(pixel(0xFF,0xFF,0xFF));
	gradation_waypoint.push_back(pixel(0x00,0x00,0x00));
	// converge

	mpfr::mpreal::set_default_prec(precision);
	bmp_write file("mandelbrot.bmp");
	complex_t center(-0.6428f, 0.4507f);
	complex_t range((hogefloat_t)16/60, (hogefloat_t)9/60);
	grid data = mandelbrot_bmp_multithread(center, range, gradation_waypoint, 1920*2, 1080*2, 16);
	file.set_data(data);
	file.write();
	return 0;
}

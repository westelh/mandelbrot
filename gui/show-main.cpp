#include <thread>
#include <stdexcept>
#include <array>
#include <gtkmm.h>
#include "mandelbrot.hpp"
#include "bmp_canvas.h"
#include "anti_aliasing.h"
#include "utils.h"

grid generate(size_t width, size_t height);

int main(int argc, char** argv) {
    // args
    const auto width = argc >= 2 ? std::stoi(argv[1]) : 720;
    const auto height = argc >= 3 ? std::stoi(argv[2]) : 480;

    // gui initialization
    Glib::ustring application_id{};
    auto fake_argc = 1; // hide command-line options from gtk
    auto app = Gtk::Application::create(fake_argc, argv, application_id);
    Glib::ustring title{"mandelbrot"};
    Gtk::Window window{};
    window.set_title(title);
    window.resize(width, height);

    // prepare master data
    const auto master = generate(width * 2, height * 2);

    // check master data
    if(master.empty()) {
        throw std::runtime_error("Failed to read master data. Data is empty.");
    }

    // aa utility takes linear bmp
    std::vector<std::uint32_t> linear_master{};
    grid_to_linear(master, std::back_inserter(linear_master));

    // aa
    std::vector<std::uint32_t> data{};
    average2x2(std::span(linear_master), std::back_inserter(data), width);

    // initialize canvas with a reference to the image
    size_t stride = Cairo::ImageSurface::format_stride_for_width(Cairo::FORMAT_ARGB32, width);
    bmp_canvas canvas{std::span(data), Cairo::FORMAT_ARGB32, static_cast<size_t>(width), static_cast<size_t>(height), stride};
    window.add(canvas);
    canvas.show();

    // main loop
    return app->run(window);
}

// TODO: Fix return of generate(). Return often contains strange stripes.
grid generate(size_t width, size_t height) {
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
    complex_t center(-0.6428f, 0.4507f);
    complex_t range((hogefloat_t)16/60, (hogefloat_t)9/60);
    grid data = mandelbrot_bmp_multithread(center, range, gradation_waypoint, width, height, std::thread::hardware_concurrency());
    return data;
}
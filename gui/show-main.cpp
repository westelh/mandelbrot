#include <thread>
#include <stdexcept>
#include <array>
#include <gtkmm.h>
#include "mandelbrot.hpp"
#include "bmp_canvas.h"
#include "anti_aliasing.h"
#include "utils.h"

grid generate();

int main(int argc, char** argv) {
    // read from file or generate()
    grid original = {};
    if (argc > 1) {
        // TODO: Reading from file fails. Glibc stops reading and spits error.
        auto reader = bmp_read(argv[1]); reader.read();
        original = reader.get_data();
    } else {
        original = generate();
    }

    auto height = original.size();
    const auto width = original.at(0).size();
    std::vector<std::uint32_t> original_converted{};
    grid_to_linear(original, std::back_inserter(original_converted));

    // gui initialization
    Glib::ustring application_id{};
    auto app = Gtk::Application::create(argc, argv, application_id);

    Glib::ustring title{"mandelbrot"};
    Gtk::Window window{};
    window.resize(width/2, height/2);
    window.set_title(title);

    std::vector<std::uint32_t> data{};
    mix2x2(std::span(original_converted), std::back_inserter(data), width / 2, average2x);

    size_t stride = Cairo::ImageSurface::format_stride_for_width(Cairo::FORMAT_ARGB32, width/2);
    bmp_canvas canvas{std::span(data), Cairo::FORMAT_ARGB32, width/2, height/2, stride};
    window.add(canvas);
    canvas.show();

    // main loop
    return app->run(window);
}

// TODO: Fix return of generate(). Return often contains strange stripes.
grid generate() {
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
    grid data = mandelbrot_bmp_multithread(center, range, gradation_waypoint, 1280*2, 720*2, std::thread::hardware_concurrency());
    return data;
}
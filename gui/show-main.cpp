#include <thread>
#include <stdexcept>
#include <gtkmm.h>
#include "mandelbrot.hpp"
#include "bmp_canvas.h"
#include "utils.h"

grid generate();

int main(int argc, char** argv) {
    // read from file or generate()
    grid img_to_show = {};
    if (argc > 1) {
        auto reader = bmp_read(argv[1]); reader.read();
        img_to_show = reader.get_data();
    } else {
        img_to_show = generate();
    }

    auto height = static_cast<int>(img_to_show.size());
    auto width = static_cast<int>(img_to_show.at(0).size());

    // gui initialization
    Glib::ustring application_id{};
    auto app = Gtk::Application::create(argc, argv, application_id);

    Glib::ustring title{"mandelbrot"};
    Gtk::Window window{};
    window.resize(width, height);
    window.set_title(title);

    bmp_canvas canvas{width, height};
    window.add(canvas);
    canvas.show();

    // bmp to canvas
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            // TODO: somehow the image flips, flip once more by (height-x-1)
            auto&& pixel = img_to_show.at(height-x-1).at(y);
            canvas.set_pixel_at(x, y, pack_rgb(pixel.r, pixel.g, pixel.b));
        }
    }

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
    grid data = mandelbrot_bmp_multithread(center, range, gradation_waypoint, 800, 600, std::thread::hardware_concurrency());
    return data;
}
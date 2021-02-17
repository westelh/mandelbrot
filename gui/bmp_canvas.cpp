#include <stdexcept>
#include "bmp_canvas.h"

namespace {
    constexpr auto format = Cairo::FORMAT_ARGB32;
}

bmp_canvas::bmp_canvas(int width, int height): width_m{width}, height_m{height}, data_m{} {
    // ARGB format needs pixel*4 size of array
    data_m.resize(width*height*4);
    std::fill(data_m.begin(), data_m.end(), 0xff);
}

bool bmp_canvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    auto stride = Cairo::ImageSurface::format_stride_for_width(format, width_m);
    if (stride < 0) throw std::logic_error("Got an invalid stride");
    auto img = Cairo::ImageSurface::create(data_m.data(), format, width_m, height_m, stride);
    cr->set_source(img, 0, 0);
    cr->paint();
    cr->show_page();
    return true;
}

std::uint32_t bmp_canvas::get_pixel_at(int x, int y) {
    return reinterpret_cast<std::uint32_t*>(data_m.data())[x*width_m+y];
}

void bmp_canvas::set_pixel_at(int x, int y, std::uint32_t pixel) {
    reinterpret_cast<std::uint32_t*>(data_m.data())[x*width_m+y] = pixel;
}


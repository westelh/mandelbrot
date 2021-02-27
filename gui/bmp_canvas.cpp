#include <stdexcept>
#include "bmp_canvas.h"

bmp_canvas::bmp_canvas(std::span<const std::uint32_t> data, Cairo::Format format, size_t width, size_t height,size_t stride) noexcept:
        data_m{data}, format_m{format}, width_m{width}, height_m{height}, stride_m{stride} {

}

bool bmp_canvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    auto img = Cairo::ImageSurface::create(const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data_m.data())), format_m, width_m, height_m, stride_m);
    cr->set_source(img, 0, 0);
    cr->paint();
    cr->show_page();
    return true;
}

#ifndef MANDELBROT_BMP_CANVAS_H
#define MANDELBROT_BMP_CANVAS_H

#include <cstdint>
#include <span>
#include <gtkmm.h>

class bmp_canvas : public Gtk::DrawingArea {
    std::span<std::uint32_t> data_m;
    Cairo::Format format_m;
    size_t width_m{};
    size_t height_m{};
    size_t stride_m{};

public:
    template<size_t Extent>
    bmp_canvas(std::span<std::uint32_t, Extent> data, Cairo::Format format, size_t width, size_t height, size_t stride):
    data_m{data}, format_m{format}, width_m{width}, height_m{height}, stride_m{stride} {
        if constexpr (data.extent != std::dynamic_extent) {
            static_assert(stride * width < data.extent);
        }
    }

    ~bmp_canvas()  override = default;

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif //MANDELBROT_BMP_CANVAS_H

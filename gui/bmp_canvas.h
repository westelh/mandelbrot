#ifndef MANDELBROT_BMP_CANVAS_H
#define MANDELBROT_BMP_CANVAS_H

#include <cstdint>
#include <span>
#include <gtkmm.h>

class bmp_canvas : public Gtk::DrawingArea {
    const std::span<const std::uint32_t> data_m;
    const Cairo::Format format_m;
    const size_t width_m{};
    const size_t height_m{};
    const size_t stride_m{};

public:
    bmp_canvas(std::span<const std::uint32_t> data, Cairo::Format format, size_t width, size_t height, size_t stride) noexcept;
    ~bmp_canvas()  override = default;

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif //MANDELBROT_BMP_CANVAS_H

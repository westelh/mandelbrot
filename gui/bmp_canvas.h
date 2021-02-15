#ifndef MANDELBROT_BMP_CANVAS_H
#define MANDELBROT_BMP_CANVAS_H

#include <cstdint>
#include <vector>
#include <gtkmm.h>

class bmp_canvas : public Gtk::DrawingArea {
public:
    using bmp_type = std::vector<unsigned char>;

    bmp_canvas(int width, int height);
    ~bmp_canvas()  override = default;

    std::uint32_t get_pixel_at(int x, int y);

    void set_pixel_at(int x, int y, std::uint32_t);

    // pack RGB as ARGB 32bit format
    static uint32_t pack_rgb(unsigned char r, unsigned char g, unsigned char b) noexcept;

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    int width_m;
    int height_m;

    // bmp to draw
    bmp_type data_m;
};

#endif //MANDELBROT_BMP_CANVAS_H

#ifndef COLOR_RGB_H
#define COLOR_RGB_H

struct ColorRGB {
public:
    int red;
    int green;
    int blue;

    explicit ColorRGB(
        int red = 0xFF,
        int green = 0xFF,
        int blue = 0xFF
    );

    ~ColorRGB() = default;

    ColorRGB operator*(int x) const;
    ColorRGB operator+(const ColorRGB& that) const;
    ColorRGB operator-(const ColorRGB& that) const;
    int operator%(const ColorRGB& that) const;
};

#endif // COLOR_RGB_H

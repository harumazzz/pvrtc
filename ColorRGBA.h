#ifndef COLOR_RGBA_H
#define COLOR_RGBA_H

struct ColorRGBA {
public:
    int red;
    int green;
    int blue;
    int alpha;

    explicit ColorRGBA(
        int red = 0xFF,
        int green = 0xFF,
        int blue = 0xFF,
        int alpha = 0xFF
    );

    ~ColorRGBA() = default;

    ColorRGBA operator*(int x) const;
    ColorRGBA operator+(const ColorRGBA& that) const;
    ColorRGBA operator-(const ColorRGBA& that) const;
    int operator%(const ColorRGBA& that) const;
};

#endif // COLOR_RGBA_H

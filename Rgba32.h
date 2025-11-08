#ifndef RGBA32_H
#define RGBA32_H

#include <cstdint>

struct Rgba32 {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

    explicit Rgba32(
        uint8_t red = 0xFF,
        uint8_t green = 0xFF,
        uint8_t blue = 0xFF,
        uint8_t alpha = 0xFF
    );

    ~Rgba32() = default;
};

#endif // RGBA32_H

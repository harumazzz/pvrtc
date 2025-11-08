#pragma once
#include <vector>
#include <cstdint>

#include "Rgba32.h"

namespace PVRTC
{
    void calculate_bounding_box(
        const std::vector<uint8_t>& colors,
        int width,
        int blockX,
        int blockY,
        Rgba32& min,
        Rgba32& max
    );
}

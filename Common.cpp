#include "Common.h"

namespace PVRTC
{
    void calculate_bounding_box(
        const std::vector<uint8_t>& colors,
        const int width,
        const int blockX,
        const int blockY,
        Rgba32& min,
        Rgba32& max
    )
    {
        uint8_t maxr = 0, maxg = 0, maxb = 0, maxa = 0;
        uint8_t minr = 255, ming = 255, minb = 255, mina = 255;
        auto begin_index = (blockY << 2) * width + (blockX << 2);
        for (int i = 0; i < 4; ++i)
        {
            auto nindex = begin_index + i * width;
            for (int j = 0; j < 4; ++j)
            {
                auto index = nindex + j;
                auto r = colors[index * 4 + 0];
                auto g = colors[index * 4 + 1];
                auto b = colors[index * 4 + 2];
                auto a = colors[index * 4 + 3];

                maxr = std::max(maxr, r);
                maxg = std::max(maxg, g);
                maxb = std::max(maxb, b);
                maxa = std::max(maxa, a);

                minr = std::min(minr, r);
                ming = std::min(ming, g);
                minb = std::min(minb, b);
                mina = std::min(mina, a);
            }
        }
        min = Rgba32(minr, ming, minb, mina);
        max = Rgba32(maxr, maxg, maxb, maxa);
    }

}
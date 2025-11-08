#include "Morton.h"

namespace PVRTC
{
    auto rotate_right(const uint32_t value, int shift) noexcept -> uint32_t
    {
        if ((shift &= 31) == 0)
            return value;
        return value >> shift | value << (32 - shift);
    }

    auto get_morton_number(const int x, const int y) noexcept -> int
    {
        return MORTON_TABLE[x >> 8] << 17
             | MORTON_TABLE[y >> 8] << 16
             | MORTON_TABLE[x & 0xFF] << 1
             | MORTON_TABLE[y & 0xFF];
    }
}

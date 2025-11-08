#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "ColorRGB.h"
#include "ColorRGBA.h"
#include "Rgba32.h"

namespace PVRTC
{
    struct Packet
    {
        uint64_t PvrTcWord;

        static constexpr std::array<std::array<uint8_t, 4>, 16> BILINEAR_FACTORS{{
            {{4, 4, 4, 4}},
            {{2, 6, 2, 6}},
            {{8, 0, 8, 0}},
            {{6, 2, 6, 2}},
            {{2, 2, 6, 6}},
            {{1, 3, 3, 9}},
            {{4, 0, 12, 0}},
            {{3, 1, 9, 3}},
            {{8, 8, 0, 0}},
            {{4, 12, 0, 0}},
            {{16, 0, 0, 0}},
            {{12, 4, 0, 0}},
            {{6, 6, 2, 2}},
            {{3, 9, 1, 3}},
            {{12, 0, 4, 0}},
            {{9, 3, 3, 1}},
        }};

        static constexpr std::array<uint8_t, 32> WEIGHTS{
            8, 0, 8, 0, 5, 3, 5, 3, 3, 5, 3, 5,
            0, 8, 0, 8, 8, 0, 8, 0, 4, 4, 4, 4,
            4, 4, 0, 0, 0, 8, 0, 8};

        explicit Packet();

        explicit Packet(uint64_t PvrTcWord);

        ~Packet() = default;

        uint32_t get_modulation_data() const;

        void set_modulation_data(uint32_t value);

        bool get_use_punch_through_alpha() const;

        void set_use_punch_through_alpha(bool value);

        int get_alpha() const;

        void set_alpha(int value);

        bool get_color_alpha_is_opaque() const;

        void set_color_alpha_is_opaque(bool value);

        int get_blue() const;

        void set_blue(int value);

        bool get_color_blue_is_opaque() const;

        void set_color_blue_is_opaque(bool value);

        ColorRGBA get_color_alpha_color_rgba() const;

        ColorRGBA get_color_blue_color_rgba() const;

        ColorRGB get_color_alpha_color_rgb() const;

        ColorRGB get_color_blue_color_rgb() const;

        void set_color_alpha_color_rgba(const Rgba32 &color);

        void set_color_blue_color_rgba(const Rgba32 &color);

        void set_color_alpha_color_rgb(const Rgba32 &color);

        void set_color_blue_color_rgb(const Rgba32 &color);
    };
}

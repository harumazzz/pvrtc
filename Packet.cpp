#include "Packet.h"

namespace PVRTC {

    Packet::Packet()
       : PvrTcWord(0)
    {
    }

    Packet::Packet(const uint64_t PvrTcWord)
        : PvrTcWord(PvrTcWord)
    {
    }

    uint32_t Packet::get_modulation_data() const {
        return static_cast<uint32_t>(PvrTcWord & 0xffffffff);
    }

    void Packet::set_modulation_data(uint32_t value)
    {
        PvrTcWord |= value;
    }

    bool Packet::get_use_punch_through_alpha() const {
        return (PvrTcWord >> 32 & 0b1) == 1;
    }

    void Packet::set_use_punch_through_alpha(bool value)
    {
        PvrTcWord |= (value ? uint64_t{1} : uint64_t{0}) << 32;
    }

    int Packet::get_alpha() const {
        return static_cast<int>(PvrTcWord >> 33 & 0b11111111111111);
    }

    void Packet::set_alpha(int value)
    {
        PvrTcWord |= static_cast<uint64_t>(value & 0b11111111111111) << 33;
    }

    bool Packet::get_color_alpha_is_opaque() const {
        return (PvrTcWord >> 47 & 0b1) == 1;
    }

    void Packet::set_color_alpha_is_opaque(bool value)
    {
        PvrTcWord |= (value ? uint64_t{1} : uint64_t{0}) << 47;
    }

    int Packet::get_blue() const {
        return static_cast<int>(PvrTcWord >> 48 & 0b111111111111111);
    }

    void Packet::set_blue(int value)
    {
        PvrTcWord |= static_cast<uint64_t>(value & 0b111111111111111) << 48;
    }

    bool Packet::get_color_blue_is_opaque() const {
        return PvrTcWord >> 63 == 1;
    }

    void Packet::set_color_blue_is_opaque(bool value)
    {
        PvrTcWord |= (value ? uint64_t{1} : uint64_t{0}) << 63;
    }

    ColorRGBA Packet::get_color_alpha_color_rgba() const {
        const auto color_alpha = get_alpha();
        if (get_color_alpha_is_opaque())
        {
            const auto r = color_alpha >> 9;
            const auto g = color_alpha >> 4 & 0x1f;
            const auto b = color_alpha & 0xf;
            return ColorRGBA(
                static_cast<uint8_t>(r << 3 | r >> 2),
                static_cast<uint8_t>(g << 3 | g >> 2),
                static_cast<uint8_t>(b << 4 | b));
        }
        const auto a = color_alpha >> 11 & 0x7;
        const auto r = color_alpha >> 7 & 0xf;
        const auto g = color_alpha >> 3 & 0xf;
        const auto b = color_alpha & 0x7;
        return ColorRGBA(
            static_cast<uint8_t>(r << 4 | r),
            static_cast<uint8_t>(g << 4 | g),
            static_cast<uint8_t>(b << 5 | b << 2 | b >> 1),
            static_cast<uint8_t>(a << 5 | a << 2 | a >> 1));
    }

    ColorRGBA Packet::get_color_blue_color_rgba() const {
        const auto color_blue = get_blue();
        if (get_color_blue_is_opaque())
        {
            const auto r = color_blue >> 10;
            const auto g = color_blue >> 5 & 0x1f;
            const auto b = color_blue & 0x1f;
            return ColorRGBA(
                static_cast<uint8_t>(r << 3 | r >> 2),
                static_cast<uint8_t>(g << 3 | g >> 2),
                static_cast<uint8_t>(b << 3 | b >> 2));
        }
        const auto a = color_blue >> 12 & 0x7;
        const auto r = color_blue >> 8 & 0xf;
        const auto g = color_blue >> 4 & 0xf;
        const auto b = color_blue & 0xf;
        return ColorRGBA(
            static_cast<uint8_t>((r << 4) | r),
            static_cast<uint8_t>((g << 4) | g),
            static_cast<uint8_t>((b << 4) | b),
            static_cast<uint8_t>((a << 5) | (a << 2) | (a >> 1)));
    }

    ColorRGB Packet::get_color_alpha_color_rgb() const {
        const auto color_alpha = get_alpha();
        if (get_color_alpha_is_opaque())
        {
            const auto r = color_alpha >> 9;
            const auto g = color_alpha >> 4 & 0x1f;
            const auto b = color_alpha & 0xf;
            return ColorRGB(
                static_cast<uint8_t>(r << 3 | r >> 2),
                static_cast<uint8_t>(g << 3 | g >> 2),
                static_cast<uint8_t>(b << 4 | b));
        }
        const auto r = (color_alpha >> 7) & 0xf;
        const auto g = (color_alpha >> 3) & 0xf;
        const auto b = color_alpha & 0x7;
        return ColorRGB(
            static_cast<uint8_t>(r << 4 | r),
            static_cast<uint8_t>(g << 4 | g),
            static_cast<uint8_t>(b << 5 | b << 2 | b >> 1));
    }

    ColorRGB Packet::get_color_blue_color_rgb() const {
        const auto color_blue = get_blue();
        if (get_color_blue_is_opaque())
        {
            const auto r = color_blue >> 10;
            const auto g = color_blue >> 5 & 0x1f;
            const auto b = color_blue & 0x1f;
            return ColorRGB(
                static_cast<uint8_t>(r << 3 | r >> 2),
                static_cast<uint8_t>(g << 3 | g >> 2),
                static_cast<uint8_t>(b << 3 | b >> 2));
        }
        const auto r = color_blue >> 8 & 0xf;
        const auto g = color_blue >> 4 & 0xf;
        const auto b = color_blue & 0xf;
        return ColorRGB(
            static_cast<uint8_t>((r << 4) | r),
            static_cast<uint8_t>((g << 4) | g),
            static_cast<uint8_t>((b << 4) | b));
    }


}
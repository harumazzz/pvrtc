#include "ColorRGB.h"

ColorRGB::ColorRGB(int red, int green, int blue)
    : red(red), green(green), blue(blue)
{
}

ColorRGB ColorRGB::operator*(int x) const {
    return ColorRGB{red * x, green * x, blue * x};
}

ColorRGB ColorRGB::operator+(const ColorRGB& that) const {
    return ColorRGB{red + that.red, green + that.green, blue + that.blue};
}

ColorRGB ColorRGB::operator-(const ColorRGB& that) const {
    return ColorRGB{red - that.red, green - that.green, blue - that.blue};
}

int ColorRGB::operator%(const ColorRGB& that) const {
    return red * that.red + green * that.green + blue * that.blue;
}

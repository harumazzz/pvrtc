#include "ColorRGBA.h"

ColorRGBA::ColorRGBA(int red, int green, int blue, int alpha)
    : red(red), green(green), blue(blue), alpha(alpha)
{
}

ColorRGBA ColorRGBA::operator*(int x) const {
    return ColorRGBA{red * x, green * x, blue * x, alpha * x};
}

ColorRGBA ColorRGBA::operator+(const ColorRGBA& that) const {
    return ColorRGBA{red + that.red, green + that.green, blue + that.blue, alpha + that.alpha};
}

ColorRGBA ColorRGBA::operator-(const ColorRGBA& that) const {
    return ColorRGBA{red - that.red, green - that.green, blue - that.blue, alpha - that.alpha};
}

int ColorRGBA::operator%(const ColorRGBA& that) const {
    return red * that.red + green * that.green + blue * that.blue + alpha * that.alpha;
}

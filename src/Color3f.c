#include "Color3f.h"

Color4f ColorRGBA(float r, float g, float b, float alpha) {
    Color4f c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.alpha = alpha;
    return c;
}

Color4f ColorGrey(float grey) {
    return ColorRGBA(grey, grey, grey,1);
}

Color4f AddColors(Color4f lhs, Color4f rhs) {
    return ColorRGBA(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b,1);
}

Color4f SubColors(Color4f lhs, Color4f rhs) {
    return ColorRGBA(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b,1);
}

Color4f MultColors(Color4f lhs, Color4f rhs) {
    return ColorRGBA(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b,1);
}

Color4f DivColors(Color4f lhs, Color4f rhs) {
    return ColorRGBA(lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b,1);
}

Color4f MultColor(Color4f c, float a) {
    return ColorRGBA(c.r * a, c.g * a, c.b * a,1);
}

Color4f DivColor(Color4f c, float a) {
    return ColorRGBA(c.r / a, c.g / a, c.b / a,1);
}

Color4f BLACK = { 0, 0, 0 }, WHITE = { 1, 1, 1 }, RED = { 1, 0, 0 }, GREEN = {
        0, 1, 0 }, BLUE = { 0, 0, 1 };

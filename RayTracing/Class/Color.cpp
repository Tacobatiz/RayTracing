#include "Color.h"
#include <algorithm>
#include <cstdio>

Color::Color() : r(0), g(0), b(0) {}

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}

Color Color::operator*(double scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator+(const Color& c) const {
    return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator*(const Color& c) const {
    return Color(r * c.r, g * c.g, b * c.b);
}

void Color::clamp() {
    r = std::min(1.0, std::max(0.0, r));
    g = std::min(1.0, std::max(0.0, g));
    b = std::min(1.0, std::max(0.0, b));
}

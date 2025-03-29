#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color {
public:
    double r, g, b;

    Color();
    Color(double r, double g, double b);

    Color operator*(double scalar) const;
    Color operator+(const Color& c) const;
    Color operator*(const Color& c) const;

    void clamp();
};

#endif // COLOR_H
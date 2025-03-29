#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"
#include "Color.h"

class Light {
public:
    Vector3D position;
    Color color;
    double intensity;

    Light(const Vector3D& position, const Color& color, double intensity);
};

#endif // LIGHT_H
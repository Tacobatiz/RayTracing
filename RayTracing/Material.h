
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material {
public:
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    double reflectivity;

    Material();
    Material(const Color& color, double ambient, double diffuse,
        double specular, double shininess, double reflectivity);
};

#endif // MATERIAL_H
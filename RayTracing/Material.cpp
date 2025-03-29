#include "Material.h"

Material::Material()
    : color(Color()), ambient(0.1), diffuse(0.7), specular(0.2),
    shininess(50), reflectivity(0) {}

Material::Material(const Color& color, double ambient, double diffuse,
    double specular, double shininess, double reflectivity)
    : color(color), ambient(ambient), diffuse(diffuse), specular(specular),
    shininess(shininess), reflectivity(reflectivity) {}
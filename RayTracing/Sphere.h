#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
public:
    Vector3D center;
    double radius;

    Sphere(const Vector3D& center, double radius, const Material& material);

    double intersect(const Vector3D& origin, const Vector3D& direction) const override;
    Vector3D getNormal(const Vector3D& point) const override;
};

#endif // SPHERE_H
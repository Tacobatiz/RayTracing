#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
public:
    Vector3D normal;
    double distance;

    Plane(const Vector3D& normal, double distance, const Material& material);

    double intersect(const Vector3D& origin, const Vector3D& direction) const override;
    Vector3D getNormal(const Vector3D& point) const override;
};

#endif // PLANE_H
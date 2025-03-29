#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3D.h"
#include "Material.h"

class Object {
public:
    Material material;

    Object();
    Object(const Material& material);

    virtual double intersect(const Vector3D& origin, const Vector3D& direction) const = 0;
    virtual Vector3D getNormal(const Vector3D& point) const = 0;
    virtual ~Object();
};

#endif // OBJECT_H
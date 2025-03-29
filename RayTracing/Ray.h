#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"

class Ray {
public:
    Vector3D origin;
    Vector3D direction;

    Ray(const Vector3D& origin, const Vector3D& direction);
};

#endif // RAY_H
#include "Plane.h"
#include <cmath>
#include <limits>

const double INF = std::numeric_limits<double>::infinity();

Plane::Plane(const Vector3D& normal, double distance, const Material& material)
    : Object(material), normal(normal.normalize()), distance(distance) {}

double Plane::intersect(const Vector3D& origin, const Vector3D& direction) const {
    double denominator = direction.dot(normal);
    if (std::abs(denominator) < 0.0001) return INF;

    double t = (distance - origin.dot(normal)) / denominator;
    if (t > 0) return t;

    return INF;
}

Vector3D Plane::getNormal(const Vector3D& point) const {
    return normal;
}
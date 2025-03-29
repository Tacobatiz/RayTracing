#include "Sphere.h"
#include <cmath>
#include <limits>

const double INF = std::numeric_limits<double>::infinity();

Sphere::Sphere(const Vector3D& center, double radius, const Material& material)
    : Object(material), center(center), radius(radius) {}

double Sphere::intersect(const Vector3D& origin, const Vector3D& direction) const {
    Vector3D oc = origin - center;

    double a = direction.dot(direction);
    double b = 2.0 * oc.dot(direction);
    double c = oc.dot(oc) - radius * radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return INF;

    double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b - std::sqrt(discriminant)) / (2.0 * a);

    if (t1 < 0 && t2 < 0) return INF;
    if (t1 < 0) return t2;
    if (t2 < 0) return t1;

    return std::min(t1, t2);
}

Vector3D Sphere::getNormal(const Vector3D& point) const {
    return (point - center).normalize();
}
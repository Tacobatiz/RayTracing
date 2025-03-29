#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

Vector3D::Vector3D() : v{ 0,0,0 } { }

double Vector3D::getX() const {
    return v[0];
}

double Vector3D::getY() const {
    return v[1];
}

double Vector3D::getZ() const {
    return v[2];
}

std::ostream& operator<<(std::ostream& out, const Vector3D& obj) {
    out << "<" << obj.v[0] << "," << obj.v[1] << "," << obj.v[2] << ">";
    return out;
}

Vector3D operator*(double scalar, Vector3D obj) {
    Vector3D tmp;
    tmp.v[0] = scalar * obj.v[0];
    tmp.v[1] = scalar * obj.v[1];
    tmp.v[2] = scalar * obj.v[2];
    return tmp;
}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(v[0] * scalar, v[1] * scalar, v[2] * scalar);
}

Vector3D Vector3D::operator/(double scalar) const {
    if (scalar == 0) return *this;
    return Vector3D(v[0] / scalar, v[1] / scalar, v[2] / scalar);
}

double Vector3D::dot(const Vector3D& other) const {
    return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vector3D Vector3D::cross(const Vector3D& other) const {
    return Vector3D(
        v[1] * other.v[2] - v[2] * other.v[1],
        v[2] * other.v[0] - v[0] * other.v[2],
        v[0] * other.v[1] - v[1] * other.v[0]
    );
}

double Vector3D::length() const {
    return std::sqrt(dot(*this));
}

Vector3D Vector3D::normalize() const {
    double len = length();
    if (len == 0) return *this;
    return *this / len;
}

Vector3D Vector3D::reflect(const Vector3D& normal) const {
    return *this - normal * 2 * dot(normal);
}
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3D {
public:
    Vector3D(double x, double y, double z);
    Vector3D();

    double getX() const;
    double getY() const;
    double getZ() const;

    Vector3D operator+(const Vector3D& v) const;
    Vector3D operator-(const Vector3D& v) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;

    double dot(const Vector3D& v) const;
    Vector3D cross(const Vector3D& v) const;
    double length() const;
    Vector3D normalize() const;
    Vector3D reflect(const Vector3D& normal) const;

    friend std::ostream& operator<<(std::ostream& out, const Vector3D& obj);
    friend Vector3D operator*(double scalar, Vector3D obj);

private:
    double v[3];
};

#endif // VECTOR3D_H
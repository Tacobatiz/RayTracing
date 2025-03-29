#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"

class Scene {
public:
    std::vector<Object*> objects;
    std::vector<Light> lights;
    Color ambient_light;
    int max_reflections;

    Scene();
    ~Scene();

    void addSphere(const Vector3D& center, double radius, const Material& material);
    void addPlane(const Vector3D& normal, double distance, const Material& material);
    void addLight(const Vector3D& position, const Color& color, double intensity);
};

#endif // SCENE_H
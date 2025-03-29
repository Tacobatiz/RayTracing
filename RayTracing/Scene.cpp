#include "Scene.h"
#include <random>

Scene::Scene() : ambient_light(Color(0.1, 0.1, 0.1)), max_reflections(3) {}

Scene::~Scene() {
    for (auto obj : objects) {
        delete obj;
    }
}

void Scene::addSphere(const Vector3D& center, double radius, const Material& material) {
    objects.push_back(new Sphere(center, radius, material));
}

void Scene::addPlane(const Vector3D& normal, double distance, const Material& material) {
    objects.push_back(new Plane(normal, distance, material));
}

void Scene::addLight(const Vector3D& position, const Color& color, double intensity) {
    lights.push_back(Light(position, color, intensity));
}

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Vector3D.h"
#include "Color.h"
#include "Scene.h"
#include "Ray.h"
#include <string>

class Raytracer {
private:
    int width, height;
    double viewport_width, viewport_height;
    double viewport_distance;
    Vector3D camera_position;

public:
    Raytracer(int width, int height, double viewport_width, double viewport_height,
        double viewport_distance, const Vector3D& camera_position);

    Vector3D canvasToViewport(int x, int y) const;
    bool isInShadow(const Vector3D& point, const Light& light, const Scene& scene) const;
    Color computeLighting(const Vector3D& point, const Vector3D& normal, const Vector3D& view_direction,
        const Material& material, const Scene& scene) const;
    Color traceRay(const Ray& ray, const Scene& scene, int reflection_depth = 0) const;
    void render(const Scene& scene, const std::string& filename) const;
    void renderAnimation(const Scene& scene, const std::string& base_filename, int frames) const;
};

#endif // RAYTRACER_H
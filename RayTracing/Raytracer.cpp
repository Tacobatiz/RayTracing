#include "Raytracer.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double INF = std::numeric_limits<double>::infinity();

Raytracer::Raytracer(int width, int height, double viewport_width, double viewport_height,
    double viewport_distance, const Vector3D& camera_position)
    : width(width), height(height), viewport_width(viewport_width), viewport_height(viewport_height),
    viewport_distance(viewport_distance), camera_position(camera_position) {}

Vector3D Raytracer::canvasToViewport(int x, int y) const {
    return Vector3D(
        x * viewport_width / width,
        y * viewport_height / height,
        viewport_distance
    );
}

bool Raytracer::isInShadow(const Vector3D& point, const Light& light, const Scene& scene) const {
    Vector3D light_dir = (light.position - point).normalize();
    double light_distance = (light.position - point).length();

    Ray shadow_ray(point, light_dir);

    for (const auto& obj : scene.objects) {
        double t = obj->intersect(shadow_ray.origin, shadow_ray.direction);
        if (t > 0.001 && t < light_distance) {
            return true;  // Object blocks the light
        }
    }

    return false;  // No objects block the light
}

Color Raytracer::computeLighting(const Vector3D& point, const Vector3D& normal, const Vector3D& view_direction,
    const Material& material, const Scene& scene) const {
    Color result = scene.ambient_light * material.ambient * material.color;  // Ambient light

    for (const auto& light : scene.lights) {
        // Check if the point is in shadow
        if (isInShadow(point, light, scene)) {
            continue;
        }

        Vector3D light_dir = (light.position - point).normalize();
        double light_intensity = light.intensity;

        // Diffuse reflection
        double diffuse_factor = std::max(0.0, normal.dot(light_dir));
        if (diffuse_factor > 0) {
            result = result + light.color * material.color * material.diffuse * diffuse_factor * light_intensity;
        }

        // Specular reflection
        if (material.specular > 0) {
            Vector3D reflection = light_dir.reflect(normal);
            double specular_factor = std::max(0.0, reflection.dot(view_direction));
            if (specular_factor > 0) {
                specular_factor = std::pow(specular_factor, material.shininess);
                result = result + light.color * material.specular * specular_factor * light_intensity;
            }
        }
    }

    result.clamp();
    return result;
}

Color Raytracer::traceRay(const Ray& ray, const Scene& scene, int reflection_depth) const {
    if (reflection_depth > scene.max_reflections) {
        return Color(0, 0, 0);  // Black for too many reflections
    }

    double closest_t = INF;
    const Object* closest_object = nullptr;

    // Find closest intersection
    for (const auto& obj : scene.objects) {
        double t = obj->intersect(ray.origin, ray.direction);
        if (t > 0.001 && t < closest_t) {  // 0.001 to avoid self-intersection
            closest_t = t;
            closest_object = obj;
        }
    }


    if (closest_object == nullptr) {
        return Color(0, 0, 0);
    }

    // Compute intersection point and normal
    Vector3D intersection_point = ray.origin + ray.direction * closest_t;
    Vector3D normal = closest_object->getNormal(intersection_point);

    // Make sure normal points toward the camera
    if (normal.dot(ray.direction) > 0) {
        normal = normal * -1;
    }

    // Get the color at the intersection point
    Color color = computeLighting(intersection_point, normal, ray.direction * -1,
        closest_object->material, scene);

    // Handle reflections
    double reflectivity = closest_object->material.reflectivity;
    if (reflectivity > 0 && reflection_depth < scene.max_reflections) {
        Vector3D reflection_dir = ray.direction.reflect(normal);
        Ray reflection_ray(intersection_point, reflection_dir);

        Color reflection_color = traceRay(reflection_ray, scene, reflection_depth + 1);
        color = color * (1 - reflectivity) + reflection_color * reflectivity;
    }

    color.clamp();
    return color;
}

void Raytracer::render(const Scene& scene, const std::string& filename) const {
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    // PPM header
    file << "P6\n" << width << " " << height << "\n255\n";

    // Render each pixel
    for (int y = height / 2; y > -height / 2; --y) {
        for (int x = -width / 2; x < width / 2; ++x) {
            Vector3D direction = canvasToViewport(x, y);
            Ray ray(camera_position, direction);

            Color color = traceRay(ray, scene);

            // Write color to file
            unsigned char r = static_cast<unsigned char>(255.99 * color.r);
            unsigned char g = static_cast<unsigned char>(255.99 * color.g);
            unsigned char b = static_cast<unsigned char>(255.99 * color.b);

            file.write(reinterpret_cast<char*>(&r), 1);
            file.write(reinterpret_cast<char*>(&g), 1);
            file.write(reinterpret_cast<char*>(&b), 1);
        }
    }

    file.close();
    std::cout << "Rendered " << filename << std::endl;
}

void Raytracer::renderAnimation(const Scene& scene, const std::string& base_filename, int frames) const {
    std::vector<Vector3D> originalSpherePositions;
    std::vector<Sphere*> spheres;

    // Collect objects and their original positions
    for (size_t i = 0; i < scene.objects.size(); ++i) {
        Sphere* sphere = dynamic_cast<Sphere*>(scene.objects[i]);
        if (sphere) {
            spheres.push_back(sphere);
            originalSpherePositions.push_back(sphere->center);
        }
    }

    // Render each frame
    for (int frame = 0; frame < frames; ++frame) {
        for (size_t i = 0; i < spheres.size(); ++i) {
            double angle = 2 * M_PI * frame / frames;
            double radius = 0.2;
            Vector3D offset(radius * cos(angle), radius * sin(angle), 0);
            spheres[i]->center = originalSpherePositions[i] + offset;
        }

        std::string filename = base_filename + "_" + std::to_string(frame) + ".ppm";
        render(scene, filename);
    }
    for (size_t i = 0; i < spheres.size(); ++i) {
        spheres[i]->center = originalSpherePositions[i];
    }
}
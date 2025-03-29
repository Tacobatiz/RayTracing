#include <iostream>
#include "Vector3D.h"
#include "Color.h"
#include "Material.h"
#include "Scene.h"
#include "Raytracer.h"
#include <string>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
int main() {
    int width = 800;
    int height = 600;
    int frameCount = 210;

    Material redMaterial(Color(1.0, 0.0, 0.0), 0.2, 0.8, 0.3, 50, 0.0);
    Material greenMaterial(Color(0.0, 1.0, 0.0), 0.2, 0.8, 0.3, 50, 0.2);
    Material blueMaterial(Color(0.0, 0.0, 1.0), 0.1, 0.6, 0.7, 150, 0.5);
    Material yellowMaterial(Color(1.0, 1.0, 0.0), 0.2, 0.8, 0.1, 10, 0.1);
    Material purpleMaterial(Color(0.8, 0.2, 0.8), 0.2, 0.7, 0.4, 30, 0.2);



    Vector3D camera_position(0, 0, -5);
    Raytracer raytracer(width, height, 1, 0.75, 1, camera_position);
    for (int frame = 0; frame < frameCount; frame++) {
        Scene scene;

        double t = 2.0 * M_PI * frame / frameCount;
        double redX = 2.0 * sin(t);
        double redZ = 3.0 + cos(t);
        double greenY = sin(t) * 0.5;
        double blueRadius = 0.75 + 0.25 * sin(t);

        scene.addSphere(Vector3D(0, -5001, 0), 5000, yellowMaterial);
        scene.addSphere(Vector3D(redX, -1, redZ), 1.0, redMaterial);
        scene.addSphere(Vector3D(-2, greenY, 4), 1.0, greenMaterial);
        scene.addSphere(Vector3D(2, 0, 4), blueRadius, blueMaterial);

        double planeSpeed = 0.10;
        double planeAngle = t * planeSpeed;
        Vector3D planeNormal(cos(planeAngle), 0, sin(planeAngle));
        double planeDistance = 4.0;

        scene.addPlane(planeNormal, planeDistance, purpleMaterial);

        scene.addLight(Vector3D(0, 5, 0), Color(1.0, 1.0, 1.0), 0.7);
        scene.addLight(Vector3D(0, 0, -5), Color(1.0, 1.0, 1.0), 0.6);


        std::string frameFilename = "frame_" + std::to_string(frame + 1) + ".ppm";
        std::cout << "Rendering frame " << (frame + 1) << " of " << frameCount << std::endl;
        raytracer.render(scene, frameFilename);
    }
    std::cout << "Animation rendering complete!" << std::endl;
    return 0;
}
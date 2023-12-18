// Scene method definitions

#include "Scene.hpp"
#include "PointLight.hpp"
#include "RGBColor.hpp"
#include "Point3.hpp"
#include "Sphere.hpp"
#include "Material.hpp"
#include "Matte.hpp"
#include "Pinhole.hpp"
#include "Vector3.hpp"
#include "Film.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

#include <iostream>

namespace RT {
// A future iteration of the tracer will read data in from a file (probably XML). For now,
// I will hard-code simple values just to get the tracer up and running.
void Scene::init() {
    std::cout << "Initializing lights..." << "\n";
    // Add light to scene:
    PointLight light(RGBColor(1.0, 1.0,  1.0), Point3(0.0, -1.0, 0.0));
    lightContainer.push_back(light);
    std::cout << "Lights loaded." << "\n";

    // Add shape to scene:
    std::cout << "Initializing scene geometry..." << "\n";
    Material* mat = new Matte(RGBColor(1.0, 1.0, 1.0), RGBColor(0.0, 0.5, 0.0));
    Sphere ball(Point3(0.0, 0.0, 5.0), 1.0, mat);
    shapeContainer.push_back(ball);
    std::cout << "Scene geometry loaded." << "\n";

    // Add camera to scene:
    pCamera = new Pinhole(Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, 1.0), 5.0, 300, 400,
                          -1.5, 1.5, -2.0, 2.0);

    pFilm = new Film;
}

void Scene::renderScene() {
    std::cout << "Rendering scene..." << "\n";
    // For each pixel in the viewport:
    for (int i = 0; i < pCamera->hres; < ++i;) {
        for (int j = 0; j < pCamera->vres < ++j;) {
            // Create the ray to be fired into the scene:
            Ray r = pCamera->createRay(i, j);
            // Transform the ray to world coordinates:
            r = pCamera->cameraToWorld * r;
            HitRecord* hitrec = new HitRecord;

            // Test ray intersection with each object in the scene:
            for (auto& shape : shapeContainer) {
                shape->hit(r, hitrec);
            }

            // Compute color for this pixel:
            RGBColor radiance;
            for (auto& light : lightContainer) {
                radiance += hitrec->mat.shade(hitrec, light);
            }

            // Add computed pixel color to bitmap:
            pFilm->addToBitmap(radiance);
        }
    }
    std::cout << "Scene successfully rendered." << "\n";
}
} // namespace RT

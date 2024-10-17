//
// Created by steph on 9/22/2024.
//

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H
#include "sphere.h"
#include <iostream>

using namespace std;

// should render the scene
void render() {
    int imageWidth = 800;
    int imageHeight = 600;
    Sphere sphere(float3(0, 0, -1), 0.5f);

    // Loop over each pixel
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            float u = float(x) / static_cast<float>(imageWidth);
            float v = float(y) / static_cast<float>(imageHeight);
            Ray ray(float3(0, 0, 0), float3(u, v, -1));

            float t;
            if (sphere.intersect(ray, t)) {
                std::cout << "Hit sphere at t = " << t << std::endl;
            }
        }
    }
}

#endif //RAY_TRACING_SCENE_H

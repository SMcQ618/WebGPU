//
// Created by steph on 9/22/2024.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "ray.h"
#include <cmath>

class Sphere {
public:
    float3 center;
    float radius;

    Sphere(const float3& c, float r) : center(c), radius(r) {}

    // Ray-sphere intersection
    bool intersect(const Ray& ray, float& t) const {
        float3 oc = ray.origin - center;
        float a = dot(ray.direction, ray.direction);
        float b = 2.0f * dot(oc, ray.direction);
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            t = (-b - sqrt(discriminant)) / (2.0f * a);
            return true;
        }
        return false;
    }
};

#endif //RAY_TRACING_SPHERE_H

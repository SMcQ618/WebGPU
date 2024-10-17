//
// Created by steph on 9/22/2024.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

// Simple 3D vector struct for positions and directions
struct float3 {
    float x, y, z;

    float3() : x(0), y(0), z(0) {} ; //have the x, y , and z
    float3(float x, float y, float z) : x(x), y(y), z(z) {}

    float3 operator-(const float3& b) const {
        return float3(x - b.x, y - b.y, z - b.z);
    }
};

// structure holding the origin and direction of the ray
struct Ray {
    float3 origin;
    float3 direction;

    Ray(const float3& o, const float3& d) : origin(o), direction(d) {}
};

// Helper functions for dot product
// inline should tell the compiler to reduce the overhead funciton call
inline float dot(const float3& a, const float3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

#endif //RAY_TRACING_RAY_H

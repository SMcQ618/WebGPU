#version 450

// File was meant to be a improved ray structure
// the maxiumun recursion depth for the rays
const int MAX_DEPTH = 5;
// a value to prevent intersection from a ray on itself
const float EPSILON = 0.001;

//Structure of the Ray with its origin and direction
struct Ray {
    vec3 origin; // starting point of the ray
    vec3 direction;
};

// Structure for a Sphere
struct Sphere {
  vec3 center;
  f32 radius;
  vec3 color;
};

// Structure for the intersection
struct Intersection {
    // this will be the point of intersection
    vec3 ipoint;
    // normal surface at the intersection point
    vec3 normal;
    // Distance from the ray origin to teh intersection
    float distance;
};

struct HitRecord {
    // some intersection point
    vec3 position;
    vec3 normal; // normal relative to the surface
    float t; // distance along the path (will rename to something beter)
    int SID; // ID for shading
};

// will be used as the description for the ray
struct Descript {
    vec3 albedo;      // Diffuse color
    float metallic;   // Metalness factor
    float roughness;  // Surface roughness
    float refrIndex;  // Refractive index
};

layout(set = 0, binding = 0) uniform Camera {
    mat4 viewMatrix;
    mat4 projectMatrix;
    vec3 cameraPosi;
} camera;

layout(set = 0, binding = 1) uniform Scene {
    vec3 lightPosition;
    vec3 lightColor;
} scene;
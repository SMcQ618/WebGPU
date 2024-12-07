// File with divide the shaderrs into different funcitons that handle specific tasks
// import the ray structure file
// after further investigation can't use things like @include must
// pre-load all the files you to include. Essentially build a virtual filesystem within opengl
//TODO: Figure out how to do the extension, will link the webpage in about me.
// link to GL_ARB: https://registry.khronos.org/OpenGL/extensions/ARB/
#version 450
#extension GL_ARB_shading_language_include : #include <RayStructure.glsl>
#include <WebGPU/RayStructure.glsl>
// Ray Generation

vec3 shade(HitRecord hit, vec3 lightDir, vec3 viewDir, Descript material) {
    float diff = max(dot(hit.nortmal, lightDir), 0.0);
    return material.albedo * diff;
}

layout(set = 0, binding = 0) buffer OutputBuffer {
    vec3 colors[];
};

bool intersectSphere(Ray ray, vec3 sphereColor, float sphereRadius, out INtersection hit) {
    // have a vector from teh origin from the ray to the center
    //of the sphere, to see how the ray is moving w.r.t the sphere
    vec ogs = ray.origin - sphereCOlor;

    //use the quadratic equation
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphereRadius * sphereRadius;

    // Discriminant determines if the ray intersects the sphere
    float discriminant = b * b - 4.0 * a * c;

    // If the discriminant is negative, there's no real root (no intersection)
    if (discriminant < 0.0) {
        return false;
    }

    // check if the intersectoin is infront of the ray's origin (viewpoint wise)
    // Calculate the smallest positive root (closest intersection point)
    float t = (-b - sqrt(discriminant)) / (2.0 * a);

    // Check if the intersection is in front of the ray's origin
    if (t > EPSILON) {
        hit.point = ray.origin + t * ray.direction;  // Intersection point
        hit.normal = normalize(hit.point - sphereCenter);  // Surface normal at the point
        hit.distance = t;  // Distance to the intersection point
        return true;  // Intersection found
    }

    //wosrt case theres no intersection
    return false;
}

// need a funciton to trace the ray and compute the color
// take into account how the color may be done (either by the rgb or numbers)
vec3 computeLight(Intersection hit, vec3 viewDir) {
    // compute teh direction of the light
    vec3 lightDir = normalize(size.lightPosition - hit.point);


    //diffuion of the light
    float diff = max(dot(hit.normal, lightDir), 0.0);
    vec3 diffuse = diff * scene.lightColor;

    //from teh angle between the ligth direction and the normal surface
    // reflect func that in the quadratic
    // reflection direction? just the reverse of the direction the lights at
    vec3 reflectDir = reflect(-lightDir, hit.normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * scene.LightColor;

    return diffuse + specular;
}

/*
 * Trace funciton of the ray and compute the color
 * @param ray the ray being traced is a Ray
 * @param depth the current recursion depth as an int
 * @return the color for the ray
 */
vec3 traceRay(Ray ray, int depth) {
    // stop the recursion if the max depth has been reached
    if (depth > MAX_DEPTH) {
        // return the background color
        return vec3(0.0);
    }

    // check for any intersection in a sphere
    Intersection hit;
    // sphere at this location 0,0,-5 with a radius of 1
    if (intersectSphere(ray, vec3(0, 0, -5), 1.0, hit)) {
        // compute the view direction
        vec3 viewDir = normalize(camera.cameraPosition - hit.point);

        // return teh computed lighting at the intersection
        return computeLight(hit, viewDir);
    }
    // if no intersection is found just return the backgorund color
    //TODO: Figure out how value of the background color, may need to be a variable
    return vec3(0.0);
}

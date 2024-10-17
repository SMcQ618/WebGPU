//
// Created by steph on 10/10/2024.
//
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

// vector3 class for the 3d cords
class Vec3 {
  public:
    float x, y, z;

    // constructor
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // have a vector addition
    Vec3 operator+(const Vec3& v) const {
      return Vec3(x + v.x, y + v.y, z + v.z);
    }

    // have a subtraction
    Vec3 operator-(const Vec3& v) const {
      return Vec3(x - v.x, y - v.y, z - v.z);
    }
    // multiplication scalor wise
    Vec3 operator*(float s) const {
      return Vec3(x * s, y * s, z * s);
    }

    // dot product
    float dot(const Vec3&  s) const {
      return x * s.x + y * s.y + z * s.z;
    }

    // normal
    Vec3 normal() const {
      float mag = sqrt(x * x + y * y + z * z);
      return Vec3(x / mag, y / mag, z / mag);
    }
  };


  // Ray class to define different rays with origins and directions
  class Ray {
    public:
      Vec3 origin, direction;

      Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

      // get a point form the ray at the first param t
      Vec3 at(float t) const {
        return origin + direction * t;
      }
  };

class Sphere {
  public:
    Vec3 center;
    float radius;
    Vec3 color;

  // constructor
  Sphere(const Vec3& center, float radius, const Vec3& color) : center(center), radius(radius), color(color) {}

  // method to check that the ray intersects with the sphere
  bool hit(const Ray& ray, float t_min, float t_max, float& t) const
  {
    Vec3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0 * ray.direction.dot(oc);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;

    // check
    if (discriminant > 0)
    {
      float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
      if (t1 > t_min && t1 < t_max) {
        t = t1;
        return true;
      }
      float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
      if (t2 > t_min && t2 < t_max) {
        t = t2;
        return true;
      }
    }
    return false;
  }
};

// calculae the color of the ray
Vec3 ray_col(const Ray& ray, const vector<Sphere>& spheres) {
  float t_min = 0.001;
  float t_max = 10000.0;
  float closest_t = t_max;
  Vec3 hit_color(0, 0, 0);  // Background color (black)

  for (const Sphere& sphere : spheres) {
    float t;
    if (sphere.hit(ray, t_min, t_max, t) && t < closest_t) {
      closest_t = t;
      hit_color = sphere.color;
    }
  }

  return hit_color;
}

// render an image??
void render_image(const string& filename, const vector<Vec3>& framebuffer, int width, int height) {
  ofstream file(filename);

  for (const Vec3& color: framebuffer) {
    int r = static_cast<int>(color.x * 255);
    int g = static_cast<int>(color.y * 255);
    int b = static_cast<int>(color.z * 255);
    file << r << ' ' << g << ' ' << b << endl;
  }
  file.close();
}


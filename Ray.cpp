#include "Ray.h"

Ray::Ray()
    : origin(),
      end(),
      samples(32) {
}

Ray::Ray(const Vector3 &_origin, const Vector3 &_end, const int &_samples)
    : origin(_origin),
      end(_end),
      samples(_samples) {
    if (_samples <= 0)
        throw RayMarchingException("Ray samples must be positive.");
}

Ray::Ray(const Ray &other)
    : origin(other.origin),
      end(other.end),
      samples(other.samples) {
}

Ray & Ray::operator=(const Ray &other) {
    if (this == &other)
        return *this;
    origin = other.origin;
    end = other.end;
    samples = other.samples;
    return *this;
}

Ray::~Ray() = default;

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    os << "Origin: " << ray.origin << "\n"
       << "End: " << ray.end << "\n"
       << "Samples: " << ray.samples;
    return os;
}

Vector3 Ray::RayCast(int k) {
    return (end * k + origin * (samples - k)) / samples;
}

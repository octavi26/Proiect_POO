#include "Camera.h"

Camera::Camera()
    : position(0, 0, -5),
      fov(10.0f),
      columns(16),
      lines(9),
      size(10.0f),
      samples(32),
      maxDistance(20.0f) {
}

Camera::Camera(const Vector3 &_position, float _fov, int _lines, float _size, int _columns, float _maxDistance, int _samples)
    : position(_position),
      fov(_fov),
      columns(_columns),
      lines(_lines),
      size(_size),
      samples(_samples),
      maxDistance(_maxDistance) {
    if (_columns <= 0 || _lines <= 0 || _size <= 0)
        throw CameraConfigurationException("Invalid camera dimensions or size.");
    if (_samples <= 0)
        throw RayMarchingException("Ray samples must be positive.");
}

Camera::Camera(const Camera &other)
    : position(other.position),
      fov(other.fov),
      columns(other.columns),
      lines(other.lines),
      size(other.size),
      samples(other.samples),
      maxDistance(other.maxDistance) {
}

Camera & Camera::operator=(const Camera &other) {
    if (this == &other)
        return *this;
    position = other.position;
    fov = other.fov;
    columns = other.columns;
    lines = other.lines;
    size = other.size;
    samples = other.samples;
    maxDistance = other.maxDistance;
    return *this;
}

Camera::~Camera() = default;

std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    os << "Position: " << camera.position << "\n"
       << "FOV: " << camera.fov << "\n"
       << "Columns: " << camera.columns << "\n"
       << "Lines: " << camera.lines << "\n"
       << "Size: " << camera.size << "\n"
       << "Samples: " << camera.samples << "\n"
       << "Max distance: " << camera.maxDistance;
    return os;
}

void Camera::SetRatio(int _columns, int _lines) {
    lines = _lines;
    columns = _columns;
}

void Camera::Move(Vector3 transform) {
    position = position + transform;
}

float Camera::Value(int x, int y, const std::vector<std::shared_ptr<Shape>>& shapes, Light light) {
    Vector3 startPosition = position;
    Vector3 endPosition = position + Vector3(-size / 2, -size * lines / columns / 2, fov) + Vector3(size * x / columns, size * y / lines, 0);
    Ray ray(startPosition, endPosition, samples);

    for (int k = 0; k < samples; ++k)
        for (auto shape : shapes) {
            if (shape->Inside(ray.RayCast(k)))
                return light.Value(ray.RayCast(k - 1));
        }

    return 0;
}

#include "Vector3.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {}

Vector3::Vector3(const Vector3& other)
    : x(other.x), y(other.y), z(other.z) {}

Vector3& Vector3::operator=(const Vector3& other) {
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector3& position) {
    os << "(" << position.x << ", " << position.y << ", " << position.z << ")";
    return os;
}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const float& other) const {
    return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const float& other) const {
    return Vector3(x / other, y / other, z / other);
}

float Vector3::GetX() { return x; }
float Vector3::GetY() { return y; }
float Vector3::GetZ() { return z; }

float Vector3::Magnitude() {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::CubedMagnitude() {
    return x * x + y * y + z * z;
}

Vector3 Vector3::RotateX(float angle) {
    angle = angle * pi / 180.0f;
    Vector3 newRotation(x, std::cos(angle) * y - std::sin(angle) * z,
                        std::sin(angle) * y + std::cos(angle) * z);
    x = newRotation.x;
    y = newRotation.y;
    z = newRotation.z;
    return *this;
}

Vector3 Vector3::RotateY(float angle) {
    angle = angle * pi / 180.0f;
    Vector3 newRotation(std::cos(angle) * x + std::sin(angle) * z,
                        y,
                        -std::sin(angle) * x + std::cos(angle) * z);
    x = newRotation.x;
    y = newRotation.y;
    z = newRotation.z;
    return *this;
}

Vector3 Vector3::RotateZ(float angle) {
    angle = angle * pi / 180.0f;
    Vector3 newRotation(std::cos(angle) * x - std::sin(angle) * y,
                        std::sin(angle) * x + std::cos(angle) * y,
                        z);
    x = newRotation.x;
    y = newRotation.y;
    z = newRotation.z;
    return *this;
}

Vector3 Vector3::Rotate(Vector3 rotation) {
    Vector3 newRotation(x, y, z);
    newRotation.RotateZ(rotation.z);
    newRotation.RotateY(rotation.y);
    newRotation.RotateX(rotation.x);
    x = newRotation.x;
    y = newRotation.y;
    z = newRotation.z;
    return *this;
}

Vector3 Vector3::Scale(Vector3 scale) {
    x /= scale.x;
    y /= scale.y;
    z /= scale.z;
    return *this;
}

Vector3 Vector3::Move(Vector3 position) {
    x -= position.x;
    y -= position.y;
    z -= position.z;
    return *this;
}

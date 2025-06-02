#include "Light.h"

Light::Light()
    : position(),
      power(1) {
}

Light::Light(const Vector3 &_position, const float &_power)
    : position(_position),
      power(_power) {
}

Light::Light(const Light &other)
    : position(other.position),
      power(other.power) {
}

Light & Light::operator=(const Light &other) {
    if (this == &other)
        return *this;
    position = other.position;
    power = other.power;
    return *this;
}

Light::~Light() = default;

std::ostream& operator<<(std::ostream& os, const Light& light) {
    os << "Position: " << light.position << "\n"
       << "Power: " << light.power;
    return os;
}

float Light::Value(Vector3 point) {
    float light = power - (position - point).Magnitude();
    if (light > power) return 1;
    if (light < 0) return 0;
    return light / power;
}

// Vector3 Light::getPosition() {
//     return position;
// }

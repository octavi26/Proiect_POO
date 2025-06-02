#include "Torus.h"
#include <iostream>

Torus::Torus() : thickness(0) {}

Torus::Torus(const Vector3& position, const Vector3& scale, const Vector3& rotation, const float& thickness)
    : Shape(position, scale, rotation), thickness(thickness) {}

std::shared_ptr<Shape> Torus::clone() const {
    return std::make_shared<Torus>(*this);
}

Torus::Torus(const Torus& other)
    : Shape(other), thickness(other.thickness) {}

Torus& Torus::operator=(const Torus& other) {
    if (this == &other)
        return *this;
    Shape::operator=(other);
    thickness = other.thickness;
    return *this;
}

bool Torus::accept(InsideVisitor& visitor, Vector3 point) const {
    return visitor.visit(*this, point);
}

void Torus::afisare(std::ostream& os) const {
    Shape::afisare(os);
    os << "\nThickness: " << thickness << "\n";
}

float Torus::getThickness() const {
    return thickness;
}

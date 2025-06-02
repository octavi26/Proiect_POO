#include "Sphere.h"
#include "exceptions.hpp"  // presupun că ai această excepție

void Sphere::afisare(std::ostream& os) const {
    Shape::afisare(os);
}

Sphere::Sphere() : Shape() {}

Sphere::Sphere(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation)
    : Shape(_position, _scale, _rotation) {
    if (scale.Magnitude() <= 0)
        throw ShapeConstructionException("Sphere radius must be positive.");
}

Sphere::Sphere(const Sphere &other) : Shape(other) {}

Sphere& Sphere::operator=(const Sphere &other) {
    if (this == &other) return *this;
    Shape::operator=(other);
    return *this;
}

std::shared_ptr<Shape> Sphere::clone() const {
    return std::make_shared<Sphere>(*this);
}

bool Sphere::accept(InsideVisitor& visitor, Vector3 point) const {
    return visitor.visit(*this, point);
}

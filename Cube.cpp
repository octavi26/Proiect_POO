#include "Cube.h"

void Cube::afisare(std::ostream& os) const {
    Shape::afisare(os);
}

Cube::Cube() : Shape() {}

Cube::Cube(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation)
    : Shape(_position, _scale, _rotation) {}

Cube::Cube(const Cube &other) : Shape(other) {}

Cube& Cube::operator=(const Cube &other) {
    if (this == &other) return *this;
    Shape::operator=(other);
    return *this;
}

std::shared_ptr<Shape> Cube::clone() const {
    return std::make_shared<Cube>(*this);
}

bool Cube::accept(InsideVisitor& visitor, Vector3 point) const {
    return visitor.visit(*this, point);
}

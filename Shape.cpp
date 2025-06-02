#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"
#include "Torus.h"
#include <cmath>

// Shape definitions
Shape::Shape() : position(), scale(1,1,1), rotation() {}
Shape::Shape(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation)
    : position(_position), scale(_scale), rotation(_rotation) {}
Shape::Shape(const Shape &other) : position(other.position), scale(other.scale), rotation(other.rotation) {}

Shape& Shape::operator=(const Shape &other) {
    if (this == &other) return *this;
    position = other.position;
    scale = other.scale;
    rotation = other.rotation;
    return *this;
}

void Shape::afisare(std::ostream& os) const {
    os << "Position: " << position << "\nScale: " << scale << "\nRotation: " << rotation;
}

std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    shape.afisare(os);
    return os;
}

Vector3 Shape::Translate(Vector3 point) const {
    return point.Move(position).Scale(scale).Rotate(rotation);
}

void Shape::Rotate(Vector3 rotate) {
    rotation = rotation + rotate;
}

// ConcreteInsideVisitor implementation as nested class in Inside
bool Shape::Inside(Vector3 point) {
    class ConcreteInsideVisitor : public InsideVisitor {
    public:
        bool visit(const Sphere& sphere, Vector3 point) const override {
            point = sphere.Translate(point);
            return point.CubedMagnitude() <= 1;
        }
        bool visit(const Cube& cube, Vector3 point) const override {
            point = cube.Translate(point);
            return point.GetX() >= -0.5 && point.GetX() <= 0.5 &&
                   point.GetY() >= -0.5 && point.GetY() <= 0.5 &&
                   point.GetZ() >= -0.5 && point.GetZ() <= 0.5;
        }
        bool visit(const Torus& torus, Vector3 point) const override {
            point = torus.Translate(point);
            Vector3 point2(point.GetX(), point.GetY(), 0);
            float angle = atan2(point.GetY(), point.GetX());
            Vector3 pointOnSphere(cos(angle), sin(angle), 0);
            return (point - pointOnSphere).Magnitude() <= torus.getThickness();
        }
    };

    ConcreteInsideVisitor visitor;
    return accept(visitor, point);
}

// CompositeShape implementations
CompositeShape::CompositeShape() = default;

CompositeShape::CompositeShape(const CompositeShape& other) : Shape(other) {
    for (const auto& child : other.children) {
        children.push_back(child->clone());
    }
}

CompositeShape& CompositeShape::operator=(const CompositeShape& other) {
    if (this == &other) return *this;
    children.clear();
    Shape::operator=(other);
    for (const auto& child : other.children) {
        children.push_back(child->clone());
    }
    return *this;
}

void CompositeShape::addChild(std::shared_ptr<Shape> shape) {
    children.push_back(shape);
}

void CompositeShape::afisare(std::ostream& os) const {
    Shape::afisare(os);
    for (const auto& child : children) {
        os << "\nChild Shape:\n" << *child;
    }
}

std::shared_ptr<Shape> CompositeShape::clone() const {
    std::shared_ptr<CompositeShape> copy(new CompositeShape(*this));
    return copy;
}

bool CompositeShape::accept(InsideVisitor& visitor, Vector3 point) const {
    Vector3 transformedPoint = this->Translate(point);
    for (const auto& child : children) {
        if (child->accept(visitor, transformedPoint))
            return true;
    }
    return false;
}

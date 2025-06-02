#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Vector3.h"

class Sphere;
class Cube;
class Torus;

class InsideVisitor {
public:
    virtual bool visit(const Sphere& sphere, Vector3 point) const = 0;
    virtual bool visit(const Cube& cube, Vector3 point) const = 0;
    virtual bool visit(const Torus& torus, Vector3 point) const = 0;
    virtual ~InsideVisitor() = default;
};

class Shape {
protected:
    Vector3 position, scale, rotation;
    virtual void afisare(std::ostream& os) const;

public:
    Shape();
    Shape(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation);
    Shape(const Shape &other);
    Shape & operator=(const Shape &other);
    virtual ~Shape() = default;

    virtual std::shared_ptr<Shape> clone() const = 0;
    virtual bool accept(InsideVisitor& visitor, Vector3 point) const = 0;
    bool Inside(Vector3 point);
    Vector3 Translate(Vector3 point) const;
    void Rotate(Vector3 rotate);

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape);
};

class CompositeShape : public Shape {
private:
    std::vector<std::shared_ptr<Shape>> children;
    void afisare(std::ostream& os) const override;

public:
    CompositeShape();
    CompositeShape(const CompositeShape& other);
    CompositeShape& operator=(const CompositeShape& other);
    ~CompositeShape() override = default;

    void addChild(std::shared_ptr<Shape> shape);
    std::shared_ptr<Shape> clone() const override;
    bool accept(InsideVisitor& visitor, Vector3 point) const override;
};

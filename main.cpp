#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include <complex>

#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////


class Vector3 {
private:
    float x;
    float y;
    float z;
    const float pi = 3.14159265358979323846f;

public:
    Vector3() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Vector3(float _x, float _y, float _z)
        : x(_x),
          y(_y),
          z(_z) {
    }

    Vector3(const Vector3 &other)
        : x(other.x),
          y(other.y),
          z(other.z) {
    }

    Vector3 & operator=(const Vector3 &other) {
        if (this == &other)
            return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    ~Vector3() = default;

    friend std::ostream& operator<<(std::ostream& os, const Vector3& position) {
        os << "(" << position.x << ", " << position.y << ", " << position.z << ")";
        return os;
    }

    Vector3 operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const float &other) const {
        return Vector3(x * other, y * other, z * other);
    }

    Vector3 operator/(const float &other) const {
        return Vector3(x / other, y / other, z / other);
    }

    /// My functions

    // float Magnitude() {
    //     return std::sqrt(x * x + y * y + z * z);
    // }

    float SquaredMagnitude() {
        return x * x + y * y + z * z;
    }

    // Vector3 Normalize() {
    //     float magnitude = Magnitude();
    //     return Vector3(x / magnitude, y / magnitude, z / magnitude);
    // }
    //
    // Vector3 Rad2Deg() {
    //     return Vector3(x * 180.0f / pi, y * 180.0f / pi, z * 180.0f / pi);
    // }
    //
    // Vector3 Deg2Rad() {
    //     return Vector3(x * pi / 180.0f, y * pi / 180.0f, z * pi / 180.0f);
    // }

    Vector3 RotateX(float angle) {
        angle = angle * pi / 180.0f;
        Vector3 newRotation(x, cos(angle) * y - sin(angle) * z, sin(angle) * y + cos(angle) * z);
        x = newRotation.x;
        y = newRotation.y;
        z = newRotation.z;
        return *this;
    }

    Vector3 RotateY(float angle) {
        angle = angle * pi / 180.0f;
        Vector3 newRotation(cos(angle) * x + sin(angle) * z, y, -sin(angle) * x + cos(angle) * z);
        x = newRotation.x;
        y = newRotation.y;
        z = newRotation.z;
        return *this;
    }

    Vector3 RotateZ(float angle) {
        angle = angle * pi / 180.0f;
        Vector3 newRotation(cos(angle) * x - sin(angle) * y, sin(angle) * x + cos(angle) * y, z);
        x = newRotation.x;
        y = newRotation.y;
        z = newRotation.z;
        return *this;
    }

    Vector3 Rotate( Vector3 rotation ) {
        Vector3 newRotation(x, y, z);
        newRotation.RotateZ(-rotation.z).RotateY(-rotation.y).RotateX(-rotation.x);
        x = newRotation.x;
        y = newRotation.y;
        z = newRotation.z;
        return *this;
    }

    Vector3 Scale( Vector3 scale ) {
        x /= scale.x;
        y /= scale.y;
        z /= scale.z;
        return *this;
    }

    Vector3 Move( Vector3 position ) {
        x -= position.x;
        y -= position.y;
        z -= position.z;
        return *this;
    }
};

class Shape {
private:
    Vector3 position;
    Vector3 scale;
    Vector3 rotation;

public:
    Shape()
        : position(),
          scale(1, 1, 1),
          rotation() {
    }

    Shape(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation)
        : position(_position),
          scale(_scale),
          rotation(_rotation) {
    }

    Shape(const Shape &other)
        : position(other.position),
          scale(other.scale),
          rotation(other.rotation) {
    }

    Shape & operator=(const Shape &other) {
        if (this == &other)
            return *this;
        position = other.position;
        scale = other.scale;
        rotation = other.rotation;
        return *this;
    }

    ~Shape() = default;

    friend std::ostream& operator<<(std::ostream& os, const Shape& transform) {
        os << "Position: " << transform.position << "\n"
           << "Scale: " << transform.scale << "\n"
           << "Rotation: " << transform.rotation;
        return os;
    }

    /// My functions
    Vector3 Translate(Vector3 point) {
        return point.Move(position).Scale(scale).Rotate(rotation);
    }

    bool Inside(Vector3 point) {
        return point.SquaredMagnitude() != 0;
    }
};

class Circle : public Shape {
public:
    Circle() {
    }
    Circle(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation)
        : Shape(_position, _scale, _rotation) {
    }
    Circle(const Circle &other)
        : Shape(other) {
    }
    Circle & operator=(const Circle &other) {
        if (this == &other)
            return *this;
        Shape::operator=(other);
        return *this;
    }
    bool Inside(Vector3 point) {
        point = Translate(point);
        return point.SquaredMagnitude() <= 1;
    }
};

int main() {
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////
    SomeClass *c = getC();
    std::cout << c << "\n";
    delete c;
    ////////////////////////////////////////////////////////////////////////

    Vector3 v{1, .25f, .45f};
    Circle circle{Vector3{1, 0, 0}, Vector3{1, 1, 1} * 2,Vector3{0, 0, 0}};
    std::cout << v << "\n";
    std::cout << circle.Inside(v) << "\n";

    /*

    sf::RenderWindow window;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    /// window.setVerticalSyncEnabled(true);                                ///
    window.setFramerateLimit(60);                                           ///
    ///////////////////////////////////////////////////////////////////////////

    while(window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if(e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if(shouldExit) {
            window.close();
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }

    */

    return 0;
}

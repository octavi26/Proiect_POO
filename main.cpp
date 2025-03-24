#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
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


class Position {
private:
    float x;
    float y;
    float z;

public:
    Position() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Position(float _x, float _y, float _z)
        : x(_x),
          y(_y),
          z(_z) {
    }

    Position(const Position &other)
        : x(other.x),
          y(other.y),
          z(other.z) {
    }

    Position & operator=(const Position &other) {
        if (this == &other)
            return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    ~Position() = default;
};

class Scale {
private:
    float x;
    float y;
    float z;

public:
    Scale() {
        x = 1.0f;
        y = 1.0f;
        z = 1.0f;
    }

    Scale(float _x, float _y, float _z)
        : x(_x),
          y(_y),
          z(_z) {
    }

    Scale(const Scale &other)
        : x(other.x),
          y(other.y),
          z(other.z) {
    }

    Scale & operator=(const Scale &other) {
        if (this == &other)
            return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    ~Scale() = default;
};

class Rotation {
private:
    float x;
    float y;
    float z;
    const float pi = 3.14159265358979323846f;

public:
    Rotation() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Rotation(float _x, float _y, float _z)
        : x(_x),
          y(_y),
          z(_z) {
    }

    Rotation(const Rotation &other)
        : x(other.x),
          y(other.y),
          z(other.z) {
    }

    Rotation & operator=(const Rotation &other) {
        if (this == &other)
            return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    ~Rotation() = default;
};

class Transform {
private:
    Position position;
    Scale scale;
    Rotation rotation;

public:
    Transform() {
        position = Position();
        scale = Scale();
        rotation = Rotation();
    }

    Transform(const Position &_position, const Scale &_scale, const Rotation &_rotation)
        : position(_position),
          scale(_scale),
          rotation(_rotation) {
    }

    Transform(const Transform &other)
        : position(other.position),
          scale(other.scale),
          rotation(other.rotation) {
    }

    Transform & operator=(const Transform &other) {
        if (this == &other)
            return *this;
        position = other.position;
        scale = other.scale;
        rotation = other.rotation;
        return *this;
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

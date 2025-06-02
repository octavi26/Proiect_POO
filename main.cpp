#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <math.h>

#include <SFML/Graphics.hpp>

#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"
#include "Torus.h"
#include "BoundingBox.h"
//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include <complex>

#include "env_fixes.h"                                              //
#include "exceptions.hpp"
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
///            Sincer, impresionant de bine tinand                 ///
///             cont ca am facut totul intr-o zi.                  ///
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

const int render_width = 128 * 1.2, render_height = 128 * 1.2;  // Low resolution render
const int window_width = 1024, window_height = 1024; // High-resolution window


int main() {
    #ifdef _OPENMP
    omp_set_num_threads(omp_get_max_threads());
    #endif
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////
    SomeClass *c = getC();
    std::cout << c << "\n";
    delete c;
    ////////////////////////////////////////////////////////////////////////

    Camera camera;
    Light light;
    std::vector<std::shared_ptr<Shape>> shapes;
    try {
        camera = Camera{Vector3{0, 0, -5}, 10.0f, 9, 16.0f, 16, 20.0f, 128};
        camera.SetRatio(render_width, render_height);

        light = Light{Vector3(1, -1, -1) * 10, 19};

        std::shared_ptr<Shape> torus1(new Torus(Vector3(0, 0, 0), Vector3(1, 1, 1) * 1.9f, Vector3(30, 0, 45), .2f));
        std::shared_ptr<Shape> torus2(new Torus(Vector3(0, 0, 0), Vector3(1, 1, 1) * 1.9f, Vector3(60, 0, 90), .2f));

        std::shared_ptr<CompositeShape> compositeTorus(new CompositeShape());
        compositeTorus->addChild(torus1);
        compositeTorus->addChild(torus2);

        std::shared_ptr<Shape> cube(new Cube(Vector3(0, 0, 0), Vector3(1, 1, 1) * 1.2f, Vector3(45, 45, 45)));
        std::shared_ptr<Shape> floor(new Cube(Vector3(0, 1.7f, 0), Vector3(100, 1, 100) * 1.0f, Vector3(0, 0, 0)));
        std::shared_ptr<Shape> sphere(new Sphere(Vector3(0, 0, 0), Vector3(1, 1, 1) * .75f, Vector3(45, 45, 45)));

        std::shared_ptr<Shape> compositeTorus2 = compositeTorus->clone(), cube2 = cube->clone(), floor2 = floor->clone(), sphere2 = sphere->clone();

        shapes.push_back(compositeTorus2);
        shapes.push_back(cube2);
        shapes.push_back(floor2);
        shapes.push_back(sphere2);

        BoundingBox<Sphere> bb_sphere(dynamic_cast<const Sphere &>(*sphere), Vector3(-1, -1, -1), Vector3(1, 1, 1));
        BoundingBox<Cube> bb_cube(dynamic_cast<const Cube &>(*cube), Vector3(-1, -1, -1), Vector3(1, 1, 1));

        Vector3 point(0.5, 0.2, 0.1);
    } catch (const CameraConfigurationException& e) {
        std::cerr << "Config error: " << e.what() << '\n';
    } catch (const RenderException& e) {
        std::cerr << "Render error: " << e.what() << '\n';
    }

    std::cout << *shapes[0];

    Vector3 step = Vector3(2, 7.5f, -1) * 1.5f;
    Vector3 CameraStep(0, 0, .15f);

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Render", sf::Style::Default);

    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    window.setVerticalSyncEnabled(true);                                    ///
    /// window.setFramerateLimit(60);                                       ///
    ///////////////////////////////////////////////////////////////////////////

    sf::Texture texture;
    texture.create(render_width, render_height);
    sf::Sprite sprite(texture);

    std::vector<sf::Uint8> pixels(render_width * render_height * 4); // RGBA buffer

    /// Initial scaling and centering
    float scaleX = static_cast<float>(window_width) / render_width;
    float scaleY = static_cast<float>(window_height) / render_height;
    float scale = std::min(scaleX, scaleY);

    sprite.setScale(scale, scale);
    sprite.setPosition(
        (window_width - render_width * scale) / 2,
        (window_height - render_height * scale) / 2
    );

    while (window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized: {  // Handle window resize
                int new_width = e.size.width;
                int new_height = e.size.height;

                scaleX = static_cast<float>(new_width) / render_width;
                scaleY = static_cast<float>(new_height) / render_height;
                scale = std::min(scaleX, scaleY);

                sprite.setScale(scale, scale);
                sprite.setPosition(
                    (new_width - render_width * scale) / 2,
                    (new_height - render_height * scale) / 2
                );

                std::cout << "New width: " << new_width << ", New height: " << new_height << '\n';
                break;
            }
            case sf::Event::KeyPressed:
                // std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if (e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                if (e.key.code == sf::Keyboard::W)
                    camera.Move(CameraStep);
                if (e.key.code == sf::Keyboard::S)
                    camera.Move(CameraStep * -1);
                break;
            default:
                break;
            }
        }
        if (shouldExit) {
            window.close();
            break;
        }

        using namespace std::chrono_literals;
        // std::this_thread::sleep_for(10ms);

        for (auto shape : shapes) {
            // Rotate all toruses
            std::shared_ptr<Torus> tor = std::dynamic_pointer_cast<Torus>(shape);
            if (tor) {
                tor->Rotate(step);
            }
        }
        shapes[0]->Rotate(step * 1.0f);
        shapes[1]->Rotate(step * -1.7f);

        /// Calculating Light Levels
        #ifdef _OPENMP
        #pragma omp parallel for collapse(2)
        for (int y = 0; y < render_height; y++) {
            for (int x = 0; x < render_width; x++) {
                int index = (y * render_width + x) * 4; // RGBA index
                float value = camera.Value(x, y, shapes, light);
                sf::Uint8 intensity = static_cast<sf::Uint8>(value * 255);

                pixels[index] = intensity;
                pixels[index + 1] = intensity;
                pixels[index + 2] = intensity;
                pixels[index + 3] = 255;
            }
        }
        #endif

        /// Adjusting the Contrast
        sf::Uint8 min_intensity = 255, max_intensity = 0;
        for (int i = 0; i < render_width * render_height * 4; i += 4) {
            if (pixels[i] < min_intensity) min_intensity = pixels[i];
            if (pixels[i] > max_intensity) max_intensity = pixels[i];
        }

        for (int i = 0; i < render_width * render_height * 4; i += 4) {
            sf::Uint8 old_intensity = pixels[i];

            if (old_intensity == 0) continue;

            sf::Uint8 new_intensity = static_cast<sf::Uint8>(
                ((old_intensity - min_intensity) / static_cast<float>(max_intensity - min_intensity)) * 255
            );

            // pixels[i] = pixels[i + 1] = pixels[i + 2] = sin(new_intensity * 255 / 255) * 128 + 128;
            pixels[i] = pixels[i + 1] = pixels[i + 2] = new_intensity;
            pixels[i + 3] = 255;
        }

        texture.update(pixels.data());

        /// Render
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

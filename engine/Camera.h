#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera();

public:
    bool update(float dt);

public:
    sf::View& getView() { return view; }
    sf::FloatRect getCameraRect() const;

private:
    sf::View view;

private:
    const float moveSpeed = 400.f;
    const float zoomSpeed = 0.5f;
};


#endif

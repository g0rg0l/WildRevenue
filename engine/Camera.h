#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Camera
{
public:
    Camera();

public:
    void update(float dt, sf::FloatRect player_bounds);

public:
    sf::View& getView() { return view; }
    sf::FloatRect getCameraRect() const;

private:
    sf::View view;

private:
    const float zoomSpeed = 0.5f;
};


#endif

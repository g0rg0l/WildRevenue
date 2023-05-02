#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Camera
{
public:
    void reset(sf::Vector2u window_size);
    void update(float dt, sf::FloatRect player_bounds);

public:
    sf::View& getView() { return view; }
    sf::FloatRect getCameraRect() const;

private:
    sf::View view;
    const float view_scale = 4.5;
    const float move_speed = 2.5;
};


#endif

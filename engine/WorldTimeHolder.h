#ifndef UNTITLED_WORLDTIMEHOLDER_H
#define UNTITLED_WORLDTIMEHOLDER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class WorldTimeHolder
{
public:
    WorldTimeHolder() = default;
    ~WorldTimeHolder() = default;

public:
    void update(float dt);
    void update_color(float dt);
    sf::Color get_world_color() const;

private:
    sf::Clock clock;
    bool isDay = true;
    sf::Vector3f world_color = {255, 255, 255};

private:
    const float day_duration_in_seconds = 1 * 60;
    const float night_duration_in_seconds = 7.5 * 60;
    const sf::Vector3f night_color = {0, 75, 95};
    const sf::Vector3f day_color = {255, 255, 255};
};


#endif

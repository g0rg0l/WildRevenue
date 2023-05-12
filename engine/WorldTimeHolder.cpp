#include "WorldTimeHolder.h"

void WorldTimeHolder::update(float dt)
{
    if (isDay && clock.getElapsedTime().asSeconds() >= day_duration_in_seconds)
    {
        isDay = false;
        clock.restart();
    }
    if (!isDay && clock.getElapsedTime().asSeconds() >= night_duration_in_seconds)
    {
        isDay = true;
        clock.restart();
    }

    update_color(dt);
}

void WorldTimeHolder::update_color(float dt)
{
    if (isDay && clock.getElapsedTime().asSeconds() >= day_duration_in_seconds / 2)
    {
        world_color.x -= fabsf(day_color.x - night_color.x) / (day_duration_in_seconds/2) * dt;
        world_color.y -= fabsf(day_color.y - night_color.y) / (day_duration_in_seconds/2) * dt;
        world_color.z -= fabsf(day_color.z - night_color.z) / (day_duration_in_seconds/2) * dt;
    }
    if (!isDay && clock.getElapsedTime().asSeconds() >= night_duration_in_seconds / 2)
    {
        world_color.x += fabsf(day_color.x - night_color.x) / (night_duration_in_seconds/2) * dt;
        world_color.y += fabsf(day_color.y - night_color.y) / (night_duration_in_seconds/2) * dt;
        world_color.z += fabsf(day_color.z - night_color.z) / (night_duration_in_seconds/2) * dt;
    }
}

sf::Color WorldTimeHolder::get_world_color() const
{
    return {(sf::Uint8) world_color.x,
            (sf::Uint8) world_color.y,
            (sf::Uint8) world_color.z
    };
}

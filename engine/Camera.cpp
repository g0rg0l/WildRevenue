#include "Camera.h"

void Camera::reset(sf::Vector2u window_size)
{
    view.reset(sf::FloatRect(
            0, 0,
            (float) window_size.x / view_scale, (float) window_size.y / view_scale)
        );
}

void Camera::update(float dt, sf::FloatRect player_bounds)
{
    sf::Vector2f player_center(
            player_bounds.left + player_bounds.width / 2,
            player_bounds.top + player_bounds.height / 2
            );

    view.move((player_center - view.getCenter()) * dt * move_speed);
}

sf::FloatRect Camera::getCameraRect() const
{
    auto rect = view.getInverseTransform().transformRect(
            {sf::FloatRect{-1, -1, 2, 2}}
    );

    return rect;
}

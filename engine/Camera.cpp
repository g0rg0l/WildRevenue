#include "Camera.h"
#include <iostream>

void Camera::reset(sf::Vector2u window_size)
{
    sf::Vector2f view_scale = {
            window_size.x * default_view_scale / 1920,
            window_size.y * default_view_scale / 1080
    };

    view.reset(sf::FloatRect(
            0, 0,
            (float) window_size.x / view_scale.x, (float) window_size.y / view_scale.y)
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

sf::Vector2f Camera::getCameraPosition() const
{
    auto size = view.getSize();
    auto center = view.getCenter();

    return {
        center.x - size.x / 2,
        center.y - size.y / 2
    };
}

sf::Vector2f Camera::getMousePosition() const
{
    auto videoMode = sf::VideoMode::getDesktopMode();
    auto globalMousePosition = sf::Mouse::getPosition();
    auto rect = getCameraRect();

    sf::Vector2f coefficient = {
            (float) globalMousePosition.x / (float) videoMode.width,
            (float) globalMousePosition.y / (float) videoMode.height
    };

    return {
        rect.left + rect.width * coefficient.x,
        rect.top + rect.height * coefficient.y
    };
}

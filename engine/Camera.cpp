#include "Camera.h"

Camera::Camera()
{
    view.reset(sf::FloatRect(0, 0, 1920, 1080));
}

void Camera::update(float dt, sf::FloatRect player_bounds)
{
    float factor = 1.f;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        factor += zoomSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        factor -= zoomSpeed * dt;


    view.zoom(factor);

    sf::Vector2f player_center(player_bounds.left + player_bounds.width / 2,
                               player_bounds.top + player_bounds.height / 2);

    view.move((player_center - view.getCenter()) * dt * 2.5f);
}

sf::FloatRect Camera::getCameraRect() const
{
    auto rect = view.getInverseTransform().transformRect(
            {sf::FloatRect{-1, -1, 2, 2}}
    );

    return rect;
}

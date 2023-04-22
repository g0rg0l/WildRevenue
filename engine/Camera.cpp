#include "Camera.h"

Camera::Camera()
{
    view.reset(sf::FloatRect(0, 0, 800, 600));
}

bool Camera::update(float dt)
{
    bool flag = false;
    sf::Vector2f offset(0, 0);
    float factor = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { offset.y -= moveSpeed * dt; flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { offset.y += moveSpeed * dt; flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { offset.x -= moveSpeed * dt; flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { offset.x += moveSpeed * dt; flag = true; }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { factor += zoomSpeed * dt; flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { factor -= zoomSpeed * dt; flag = true; }

    if (flag)
    {
        view.move(offset);
        view.zoom(factor);
    }

    return flag;
}

sf::FloatRect Camera::getCameraRect() const
{
    auto rect = view.getInverseTransform().transformRect(
            {sf::FloatRect{-1, -1, 2, 2}}
    );

    return rect;
}

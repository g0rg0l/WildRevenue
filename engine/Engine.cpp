#include "Engine.h"

Engine::Engine()
{
    window.create(sf::VideoMode::getDesktopMode(),"untitled");
    camera.reset(window.getSize());
    renderTexture.create(window.getSize().x, window.getSize().y);
}

int Engine::run_engine()
{
    map.load();

    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        entityHolder.update_entity(dt, map.decor.wallBounds);
        camera.update(dt, entityHolder.get_player_bounds());
        map.clip(camera.getCameraRect());

        check_events();
        draw();
    }

    return 0;
}

void Engine::check_events()
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Engine::draw()
{
    renderTexture.setView(camera.getView());
    renderTexture.clear();
    renderTexture.draw(map.terrain);
    renderTexture.draw(map.decor);
    renderTexture.draw(entityHolder);
    renderTexture.draw(map.trees);
    renderTexture.display();

    sf::Sprite renderSprite;
    renderSprite.setTexture(renderTexture.getTexture());
    window.clear();
    window.draw(renderSprite);
    window.display();
}

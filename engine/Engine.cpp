#include "Engine.h"

Engine::Engine()
{
    window.create(sf::VideoMode::getDesktopMode(),
                  "untitled"
    );
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
    window.setView(camera.getView());

    window.clear();
    window.draw(map.terrain);
    window.draw(map.decor);
    window.draw(entityHolder);
    window.draw(map.trees);
    window.display();
}

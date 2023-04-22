#include "Engine.h"

Engine::Engine()
{
    window.create(sf::VideoMode(1920, 1080), "untitled");
}

int Engine::run_engine()
{
    map.load();

    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        camera.update(dt);
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
    window.draw(map);
    window.display();
}

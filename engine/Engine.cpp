#include "Engine.h"

Engine::Engine()
{
    window.create(sf::VideoMode::getDesktopMode(), "untitled", sf::Style::Fullscreen);
    camera.reset(window.getSize());
    worldRenderTexture.create(window.getSize().x, window.getSize().y);
    menuRenderTexture.create(window.getSize().x, window.getSize().y);
    menusHolder.create(entityHolder.get_player_inventory());
}

int Engine::run_engine()
{
    map.load();

    while(window.isOpen())
    {
        dt = clock.restart().asSeconds();

        worldTimeHolder.update(dt);
        entityHolder.update_entity(dt, map.decor.wallBounds);
        camera.update(dt, entityHolder.get_player_bounds());
        map.clip(camera.getCameraRect());

        check_events();
        menusHolder.update(camera.getCameraPosition(),
                           camera.getMousePosition());
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


    EventWatcher& eventWatcher = EventWatcher::getInstance();

    if (eventWatcher.isKeyBoardKeyTriggered(sf::Keyboard::I))
        menusHolder.executeInventory();
}

void Engine::draw()
{
    /* Отрисовка World */
    worldRenderTexture.setView(camera.getView());
    worldRenderTexture.clear();
    worldRenderTexture.draw(map.terrain);
    worldRenderTexture.draw(map.decor);
    worldRenderTexture.draw(entityHolder);
    worldRenderTexture.draw(map.trees);
    worldRenderTexture.display();

    menuRenderTexture.setView(camera.getView());
    menuRenderTexture.clear(sf::Color::Transparent);
    menuRenderTexture.draw(menusHolder);
    menuRenderTexture.display();

    sf::Sprite worldRenderSprite;
    worldRenderSprite.setColor(worldTimeHolder.get_world_color());
    worldRenderSprite.setTexture(worldRenderTexture.getTexture());

    sf::Sprite menuRenderSprite;
    menuRenderSprite.setTexture(menuRenderTexture.getTexture());

    window.clear();
    window.draw(worldRenderSprite);
    window.draw(menuRenderSprite);
    window.display();
}
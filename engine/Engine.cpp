#include "Engine.h"

Engine::Engine()
{
    window.create(sf::VideoMode::getDesktopMode(), "untitled", sf::Style::Fullscreen);
    camera.reset(window.getSize());
    worldRenderTexture.create(window.getSize().x, window.getSize().y);
    menuRenderTexture.create(window.getSize().x, window.getSize().y);
    inventory_menu.create(&player.inventory);
}

int Engine::run_engine()
{
    map.load();

    while(window.isOpen())
    {
        dt = clock.restart().asSeconds();
        worldTimeHolder.update(dt);

        player.update(dt, get_all_hitboxes());

        entityHolder.update();
        camera.update(dt, player.get_bounds());
        map.clip(camera.getCameraRect());

        check_events();

        inventory_menu.update(camera.getCameraPosition(), camera.getMousePosition());

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

        if (event.type == sf::Event::MouseWheelScrolled)
            inventory_menu.transfuseItems(event.mouseWheelScroll.delta, camera.getMousePosition());
    }


    EventWatcher& eventWatcher = EventWatcher::getInstance();

    if (eventWatcher.isKeyBoardKeyTriggered(sf::Keyboard::I))
        inventory_menu.execute();
    if (eventWatcher.isKeyBoardKeyPressed(sf::Keyboard::E))
        entityHolder.entity_collect_check(&player);
}

void Engine::draw()
{
    worldRenderTexture.setView(camera.getView());
    worldRenderTexture.clear();
    worldRenderTexture.draw(map.terrain);
    worldRenderTexture.draw(map.decor);
    structureHolder.drawBottom(worldRenderTexture);
    worldRenderTexture.draw(entityHolder);
    worldRenderTexture.draw(player);
    worldRenderTexture.draw(map.trees);
    structureHolder.drawUpper(worldRenderTexture);
    worldRenderTexture.display();

    menuRenderTexture.setView(camera.getView());
    menuRenderTexture.clear(sf::Color::Transparent);
    menuRenderTexture.draw(inventory_menu);
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

std::vector<sf::FloatRect> Engine::get_all_hitboxes()
{
    std::vector<sf::FloatRect> hitboxes;
    hitboxes.reserve(
            map.decor.wallBounds.size() +
            structureHolder.hitboxes.size()
    );

    hitboxes.insert(hitboxes.end(), map.decor.wallBounds.begin(), map.decor.wallBounds.end());
    hitboxes.insert(hitboxes.end(), structureHolder.hitboxes.begin(), structureHolder.hitboxes.end());

    return hitboxes;
}

#include "InventoryMenu.h"

/* Инициализация */
InventoryMenu::InventoryMenu()
{
    TextureHolder& textureHolder = TextureHolder::getInstance();

    textureHolder.loadFromFile("../menus/src/inventory/background.png", "inventory_background");
}

/* адание параметров экрана*/
void InventoryMenu::create(Inventory* playerInv)
{
    /* params */
    player_inventory = playerInv;

    TextureHolder& textureHolder = TextureHolder::getInstance();

    /* background */
    auto backgroundTexture = textureHolder.getResource("inventory_background");
    background.setTexture(*backgroundTexture);
}


void InventoryMenu::update(sf::Vector2f camera_position, sf::Vector2f mousePosition)
{

    if (isOppening)
    {
        if (clock.getElapsedTime().asSeconds() >= open_close_time)
        {
            isOppening = false;
            isOpen = true;
        }
    }
    if (isClosing)
    {
        if (clock.getElapsedTime().asSeconds() >= open_close_time)
        {
            isClosing = false;
            isOpen = false;
        }
    }

    if (isOpen && !isClosing && !isOppening)
    {
        itemStatesUpdate(mousePosition);
        agreeMenuUpdate(mousePosition);
    }

    if (isOppening || isClosing || isOpen)
    {
        updatePositions(camera_position);
        itemUpdate();
        hoverUpdate(mousePosition);
    }
}

void InventoryMenu::updatePositions(sf::Vector2f camera_position)
{
    if (isOpen)
    {
        /* background */
        background.setPosition(background_position + camera_position );

        /* icons */
        for (auto& icon : icons)
            icon.setPosition(camera_position);

        /* states icon */
        itemStates.setPosition(camera_position);

        /* agree menu */
        agreeMenu.setPosition(camera_position);
    }

    if (isOppening)
    {
        float coef = clock.getElapsedTime().asSeconds() / open_close_time;

        /* background */
        sf::Vector2f outPosition = {background_position.x, background_position.y + 100};
        sf::Vector2f offset = {0, 100 * coef};
        background.setPosition(outPosition + camera_position - offset);

        /* icons */
        for (auto& icon : icons)
            icon.setPosition(sf::Vector2f(0, 100) + camera_position - offset);

        /* states icon */
        itemStates.setPosition(camera_position);

        /* agree menu */
        agreeMenu.setPosition(camera_position);
    }
    if (isClosing)
    {
        float coef = clock.getElapsedTime().asSeconds() / open_close_time;

        /* background */
        sf::Vector2f offset = {0, 100 * coef};
        background.setPosition(background_position + camera_position + offset);

        /* icons */
        for (auto& icon : icons)
            icon.setPosition(camera_position + offset);

        /* states icon */
        itemStates.setPosition(camera_position);

        /* agree menu */
        agreeMenu.setPosition(camera_position);
    }
}

void InventoryMenu::hoverUpdate(sf::Vector2f mousePosition)
{
    for (auto& icon : icons)
    {
        auto iconBounds = icon.getGlobalBounds();

        if (iconBounds.contains(mousePosition)) icon.makeHover();
        else icon.makeIdle();
    }
}

void InventoryMenu::itemStatesUpdate(sf::Vector2f mousePosition)
{
    EventWatcher& eventWatcher = EventWatcher::getInstance();

    if (eventWatcher.isMouseButtonTriggered(sf::Mouse::Left))
    {
        for (int i = 0; i < icons.size(); ++i)
        {
            auto iconBounds = icons[i].getGlobalBounds();

            if (iconBounds.contains(mousePosition) && !icons[i].isEmpty())
            {
                itemStates.open(i);
                agreeMenu.close();

                return;
            }
        }

        if (itemStates.isRemoveClicked(mousePosition))
            agreeMenu.open();

        if (agreeMenu.isYesClicked(mousePosition))
        {
            agreeMenu.close();
            deleteSelectedItem(itemStates.get_selected_item_id());
        }
        if (agreeMenu.isNoClicked(mousePosition))
            agreeMenu.close();

        itemStates.close();
    }

    itemStates.hoverUpdate(mousePosition);
}

void InventoryMenu::agreeMenuUpdate(sf::Vector2f mousePosition)
{
    /* тут же будем проверять нажатия на кнопки */
    if (agreeMenu.isActive)
    {
        EventWatcher& eventWatcher = EventWatcher::getInstance();

        if (eventWatcher.isKeyBoardKeyTriggered(sf::Keyboard::Escape))
            agreeMenu.close();

        if (eventWatcher.isKeyBoardKeyTriggered(sf::Keyboard::Enter))
        {
            agreeMenu.close();
            deleteSelectedItem(itemStates.get_selected_item_id());
        }
    }

    agreeMenu.hoverUpdate(mousePosition);
}

void InventoryMenu::itemUpdate()
{
    auto item_ids = player_inventory->get_id_vector();
    auto item_counts = player_inventory->get_count_vector();

    for (int i = 0; i < icons.size(); ++i)
    {
        icons[i].setItemId(item_ids[i]);
        icons[i].setItemCount(item_counts[i]);
    }
}

void InventoryMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (isOpen || isOppening || isClosing)
    {
        target.draw(background, states);

        for (auto& icon : icons)
            target.draw(icon, states);

        target.draw(itemStates, states);
        target.draw(agreeMenu, states);
    }
}

void InventoryMenu::execute()
{
    if (!isOpen && !isOppening)
    {
        clock.restart();
        isOppening = true;
    }
    if (isOpen && !isClosing)
    {
        clock.restart();
        isClosing = true;
        itemStates.close();
        agreeMenu.close();
    }
}

void InventoryMenu::deleteSelectedItem(int id)
{
    player_inventory->pop(id);
}

void InventoryMenu::transfuseItems(float delta, sf::Vector2f mousePosition)
{
    if (isOpen)
    {
        for (int i = 0; i < icons.size(); ++i)
        {
            auto iconBounds = icons[i].getGlobalBounds();

            if (iconBounds.contains(mousePosition))
            {
                agreeMenu.close();
                itemStates.close();

                player_inventory->transfuse(i, delta);
                break;
            }
        }
    }
}



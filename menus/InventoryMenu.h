#ifndef UNTITLED_INVENTORYMENU_H
#define UNTITLED_INVENTORYMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../inventory/Inventory.h"
#include "../engine/TextureHolder.h"
#include "../engine/EventWatcher.h"


class InventoryIconWithItem : public sf::Drawable
{
public:
    explicit InventoryIconWithItem(sf::Vector2f position) : defaultIconPosition(position)
    {
        TextureHolder& textureHolder = TextureHolder::getInstance();
        textureHolder.loadFromFile("../menus/src/inventory/icon.png", "inventory_icon");
        textureHolder.loadFromFile("../menus/src/inventory/empty.png", "empty_item");

        auto iconTexture = textureHolder.getResource("inventory_icon");
        icon.setTexture(*iconTexture);
        icon.setTextureRect(sf::IntRect(0, 0, 26, 28));

        auto itemTexture = textureHolder.getResource("empty_item");
        item.setTexture(*itemTexture);

        FontHolder& fontHolder = FontHolder::getInstance();
        fontHolder.loadFromFile("../menus/src/inventory/small_pixel.ttf", "inventory_font");

        auto font = fontHolder.getResource("inventory_font");
        item_count.setFont(*font);
        item_count.setCharacterSize(8);
        item_count.setFillColor(sf::Color(60, 60, 60));
        auto& fontTexture = const_cast<sf::Texture&>(font->getTexture(8));
        fontTexture.setSmooth(false);
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(icon, states);
        target.draw(item, states);
        target.draw(item_count, states);
    }

public:
    void setItemId(const std::string& id)
    {
        itemID = id;

        TextureHolder& textureHolder = TextureHolder::getInstance();
        sf::Texture* texture;

        if (!itemID.empty()) texture = textureHolder.getResource(id);
        else texture = textureHolder.getResource("empty_item");

        item.setTexture(*texture);
    }
    void setItemCount(int count)
    {
        if (!itemID.empty()) item_count.setString(std::to_string(count));
        else item_count.setString("");
    }
    void makeHover() { icon.setTextureRect(sf::IntRect(26, 0, 26, 28)); }
    void makeIdle() { icon.setTextureRect(sf::IntRect(0, 0, 26, 28)); }

    void setPosition(sf::Vector2f newPos)
    {
        icon.setPosition(newPos + defaultIconPosition);

        auto iconBounds = icon.getGlobalBounds();
        auto itemBounds = item.getGlobalBounds();
        sf::Vector2f iconCenter = {iconBounds.left + iconBounds.width / 2, iconBounds.top + iconBounds.height / 2};
        sf::Vector2f itemCenteredPosition = {
                iconCenter.x - itemBounds.width / 2,
                iconCenter.y - itemBounds.height / 2
        };

        item.setPosition(itemCenteredPosition);

        sf::Vector2f itemCountPosition = {
                iconCenter.x + iconBounds.width / 8,
                iconCenter.y + iconBounds.height / 8
        };
        item_count.setPosition(itemCountPosition);
    }
    sf::FloatRect getGlobalBounds() const { return icon.getGlobalBounds(); }
    bool isEmpty() { return itemID.empty(); }

private:
    sf::Vector2f defaultIconPosition;
    sf::Sprite icon;

    sf::Sprite item;
    std::string itemID;

    sf::Text item_count;
};


class InventoryItemStates : public sf::Drawable
{
public:
    InventoryItemStates()
    {
        TextureHolder& textureHolder = TextureHolder::getInstance();

        textureHolder.loadFromFile("../menus/src/inventory/remove_item_button.png", "inventory_remove_item");
        textureHolder.loadFromFile("../menus/src/inventory/show_item_info_button.png", "inventory_show_item_info");

        auto removeItemIconTexture = textureHolder.getResource("inventory_remove_item");
        removeItemIcon.setTexture(*removeItemIconTexture);
        removeItemIcon.setTextureRect(sf::IntRect(0, 0, 22, 24));

        auto showInfoIconTexture = textureHolder.getResource("inventory_show_item_info");
        showInfoIcon.setTexture(*showInfoIconTexture);
        showInfoIcon.setTextureRect(sf::IntRect(0, 0, 22, 24));
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if (isActive)
        {
            target.draw(removeItemIcon, states);
            target.draw(showInfoIcon, states);
        }
    }
public:
    void open(int item_id)
    {
        itemID = item_id;
        isActive = true;
    }
    void close() { isActive = false; }
    void setPosition(sf::Vector2f cameraPos)
    {
        if (isActive)
        {
            sf::Vector2f defaultPosition = leftTopPositions[itemID];
            sf::Vector2f showPosition = defaultPosition;
            sf::Vector2f removePosition = {
                    showPosition.x + showInfoIcon.getGlobalBounds().width + 1,
                    showPosition.y
            };

            showInfoIcon.setPosition(cameraPos + showPosition);
            removeItemIcon.setPosition(cameraPos + removePosition);
        }
    }
    void hoverUpdate(sf::Vector2f mousePosition)
    {
        if (isActive)
        {
            auto showInfoBounds = showInfoIcon.getGlobalBounds();
            auto removeItemBounds = removeItemIcon.getGlobalBounds();

            if (showInfoBounds.contains(mousePosition))
                showInfoIcon.setTextureRect(sf::IntRect(22, 0, 22, 24));
            else
                showInfoIcon.setTextureRect(sf::IntRect(0, 0, 22, 24));

            if (removeItemBounds.contains(mousePosition))
                removeItemIcon.setTextureRect(sf::IntRect(22, 0, 22, 24));
            else
                removeItemIcon.setTextureRect(sf::IntRect(0, 0, 22, 24));
        }
    }
    bool isRemoveClicked(sf::Vector2f mousePosition)
    {
        auto removeItemBounds = removeItemIcon.getGlobalBounds();
        return isActive && removeItemBounds.contains(mousePosition);
    }
    bool isShowInfoClicked(sf::Vector2f mousePosition)
    {
        auto showInfoBounds = showInfoIcon.getGlobalBounds();
        return isActive && showInfoBounds.contains(mousePosition);
    }

    int get_selected_item_id() const { return itemID; }

private:
    sf::Sprite removeItemIcon;
    sf::Sprite showInfoIcon;
    const std::vector<sf::Vector2f> leftTopPositions = {
            {135, 169},
            {163, 169},
            {191, 169},
            {219, 169},
            {247, 169}
    };

    int itemID;

public:
    bool isActive = false;
};


class AgreeMenu : public sf::Drawable
{
public:
    AgreeMenu()
    {
        TextureHolder& textureHolder = TextureHolder::getInstance();
        textureHolder.loadFromFile("../menus/src/inventory/agree_background.png", "agree_background");
        textureHolder.loadFromFile("../menus/src/inventory/yes_button.png", "yes_button");
        textureHolder.loadFromFile("../menus/src/inventory/no_button.png", "no_button");

        auto texture = textureHolder.getResource("agree_background");
        agree_background.setTexture(*texture);

        texture = textureHolder.getResource("yes_button");
        yes_button.setTexture(*texture);
        yes_button.setTextureRect(sf::IntRect(0, 0, 18, 20));

        texture = textureHolder.getResource("no_button");
        no_button.setTexture(*texture);
        no_button.setTextureRect(sf::IntRect(0, 0, 18, 20));

        FontHolder& fontHolder = FontHolder::getInstance();
        fontHolder.loadFromFile("../menus/src/inventory/Ticketing.ttf", "text_font");

        auto font = fontHolder.getResource("text_font");
        text.setFont(*font);
        text.setCharacterSize(8);
        text.setFillColor(sf::Color(60, 60, 60));
        auto& fontTexture = const_cast<sf::Texture&>(font->getTexture(8));
        fontTexture.setSmooth(false);
        text.setString("Are you sure to delete\n\t\tthis item?");
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if (isActive)
        {
            target.draw(agree_background, states);
            target.draw(yes_button, states);
            target.draw(no_button, states);
            target.draw(text, states);
        }
    }

public:
    void open() { isActive = true; }
    void close() { isActive = false; }

    void setPosition(sf::Vector2f camera_pos)
    {
        if (isActive)
        {
            agree_background.setPosition(agree_background_position + camera_pos);
            yes_button.setPosition(yes_button_position + camera_pos);
            no_button.setPosition(no_button_position + camera_pos);

            auto backgroundBouds = agree_background.getGlobalBounds();
            auto textBounds = text.getGlobalBounds();
            sf::Vector2f backgroundCenter = {
                    backgroundBouds.left + backgroundBouds.width / 2,
                    backgroundBouds.top + backgroundBouds.height / 2
            };
            sf::Vector2f textPosition = {
                    backgroundCenter.x - textBounds.width / 2,
                    backgroundCenter.y - (1.25f * textBounds.height)
            };
            text.setPosition(textPosition);
        }
    }
    void hoverUpdate(sf::Vector2f mousePosition)
    {
        if (isActive)
        {
            auto bounds = yes_button.getGlobalBounds();
            if (bounds.contains(mousePosition))
                yes_button.setTextureRect(sf::IntRect(18, 0, 18, 20));
            else
                yes_button.setTextureRect(sf::IntRect(0, 0, 18, 20));

            bounds = no_button.getGlobalBounds();
            if (bounds.contains(mousePosition))
                no_button.setTextureRect(sf::IntRect(18, 0, 18, 20));
            else
                no_button.setTextureRect(sf::IntRect(0, 0, 18, 20));
        }
    }
    bool isYesClicked(sf::Vector2f mousePosition)
    {
        auto bounds = yes_button.getGlobalBounds();
        return isActive && bounds.contains(mousePosition);
    }
    bool isNoClicked(sf::Vector2f mousePosition)
    {
        auto bounds = no_button.getGlobalBounds();
        return isActive && bounds.contains(mousePosition);
    }

private:
    sf::Sprite agree_background;
    sf::Sprite yes_button;
    sf::Sprite no_button;
    sf::Text text;

    const sf::Vector2f agree_background_position = {129, 60};
    const sf::Vector2f yes_button_position = {176, 90};
    const sf::Vector2f no_button_position = {234, 90};

public:
    bool isActive = false;
};


class InventoryMenu : public sf::Drawable
{
public:
    InventoryMenu();
    void create(Inventory* playerInv);

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Vector2f camera_position, sf::Vector2f mousePosition);
    void execute();

public:
    void updatePositions(sf::Vector2f camera_position);
    void hoverUpdate(sf::Vector2f mousePosition);
    void itemUpdate();
    void itemStatesUpdate(sf::Vector2f mousePosition);
    void agreeMenuUpdate(sf::Vector2f mousePosition);
    void transfuseItems(float delta, sf::Vector2f mousePosition);

public:
    void deleteSelectedItem(int id);

private:
    Inventory* player_inventory = nullptr;

private:
    sf::Clock clock;
    bool isOppening = false;
    bool isClosing = false;
    bool isOpen = false;
    const float open_close_time = 0.2;

private:
    sf::Sprite background;
    std::vector<InventoryIconWithItem> icons =
            {InventoryIconWithItem({144, 204}),
            InventoryIconWithItem({172, 204}),
            InventoryIconWithItem({200, 204}),
            InventoryIconWithItem({228, 204}),
            InventoryIconWithItem({256, 204})};

    InventoryItemStates itemStates;
    AgreeMenu agreeMenu;

    sf::Vector2f background_position = {100, 194};
};


#endif

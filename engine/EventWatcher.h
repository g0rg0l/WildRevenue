#ifndef UNTITLED_EVENTWATCHER_H
#define UNTITLED_EVENTWATCHER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class EventWatcher
{
private:
    EventWatcher() = default;

public:
    static EventWatcher& getInstance()
    {
        static EventWatcher eventWatcher;
        return eventWatcher;
    }

public:
    bool isKeyBoardKeyTriggered(sf::Keyboard::Key key)
    {
        bool& trigger = keyboard_triggers_map[key];

        if (sf::Keyboard::isKeyPressed(key))
        {
            if (!trigger) return (trigger = true);
        }
        else return (trigger = false);

        return false;
    }

    bool isMouseButtonTriggered(sf::Mouse::Button button)
    {
        bool& trigger = mouse_button_triggers_map[button];

        if (sf::Mouse::isButtonPressed(button))
        {
            if (!trigger) return (trigger = true);
        }
        else  return (trigger = false);

        return false;
    }

private:
    std::unordered_map<sf::Keyboard::Key, bool> keyboard_triggers_map;
    std::unordered_map<sf::Mouse::Button, bool> mouse_button_triggers_map;
};

#endif


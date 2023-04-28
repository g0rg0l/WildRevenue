#ifndef UNTITLED_ENTITYHOLDER_H
#define UNTITLED_ENTITYHOLDER_H

#include <SFML/Graphics.hpp>

#include "player/Player.h"

class EntityHolder : public sf::Drawable
{
public: /* --------- Инициализация/деструктурирование --------- */
    EntityHolder();
    ~EntityHolder() override;

public: /* --------- Отрисовка хранимых объектов --------- */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public: /* --------- Обновление хранимых объектов --------- */
    void update_entity(float dt, const std::vector<sf::FloatRect>& wallBounds);

public:
    sf::FloatRect get_player_bounds() const;

private:
    Player* player;

};


#endif

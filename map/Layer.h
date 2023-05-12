#ifndef UNTITLED_LAYER_H
#define UNTITLED_LAYER_H

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Tileset.h"
#include "../engine/TextureHolder.h"

class Layer : public sf::Drawable
{
public:
    Layer() = default;

    void setInfo(std::string  name, int width, int height)
    {
        layerName = std::move(name);
        size = {width, height};
    }

    void loadWallBounds()
    {
        for (int i = 0; i < size.x; ++i)
            for (int j = 0; j < size.y; ++j)
            {
                int id = data[i + j * size.x];

                if (tileset->isWall(id))
                {
                    sf::Vector2f pos(i * tileset->tile_sizes.x, j * tileset->tile_sizes.y);

                    wallBounds.push_back(sf::FloatRect(
                            pos.x, pos.y,
                            tileset->tile_sizes.x, tileset->tile_sizes.y
                            ));
                }
            }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        sf::VertexArray vertexArray(sf::Quads,
                                    (right_bottom.x - left_top.x + 1) * (right_bottom.y - left_top.y + 1) * 4);

        for (int i = left_top.x, i_ = 0; i < right_bottom.x; ++i, i_++)
        {
            for (int j = left_top.y, j_ = 0; j < right_bottom.y; ++j, j_++)
            {
                int id = data[i + j * size.x];

                /* Координаты тек. вертекса */
                sf::Vertex* quad = &vertexArray[(i_ + j_ * (right_bottom.x - left_top.x + 1)) * 4];

                quad[0].position = sf::Vector2f(i * tileset->tile_sizes.x, j * tileset->tile_sizes.y);
                quad[1].position = sf::Vector2f( (i + 1) * tileset->tile_sizes.x, j * tileset->tile_sizes.y);
                quad[2].position = sf::Vector2f((i + 1) * tileset->tile_sizes.x, (j + 1) * tileset->tile_sizes.y);
                quad[3].position = sf::Vector2f(i * tileset->tile_sizes.x, (j + 1) * tileset->tile_sizes.y);

                if (id != -1)
                {
                    /* Текстурные координаты */
                    sf::Vector2f texLeftTop = textureCords[id];

                    quad[0].texCoords = sf::Vector2f(texLeftTop.x, texLeftTop.y);
                    quad[1].texCoords = sf::Vector2f(texLeftTop.x + tileset->tile_sizes.x, texLeftTop.y);
                    quad[2].texCoords = sf::Vector2f(texLeftTop.x + tileset->tile_sizes.x, texLeftTop.y + tileset->tile_sizes.y);
                    quad[3].texCoords = sf::Vector2f(texLeftTop.x, texLeftTop.y + tileset->tile_sizes.y);
                }
            }
        }

        TextureHolder& textureHolder = TextureHolder::getInstance();
        auto texture = textureHolder.getResource(layerName);

        target.draw(vertexArray, texture);
    }

public:
    sf::Vector2i get_size() const { return size;}
    void clip(sf::Vector2i lt, sf::Vector2i rb)
    {
        left_top = lt;
        right_bottom = rb;
    }
    void add_data(int id) { data.push_back(id); }
    void add_tile(int id, sf::Vector2f cords) { textureCords[id] = cords; }
    void linkTileset(Tileset* tilesetToLink)
    {
        /* Линковка */
        tileset = tilesetToLink;

        /* Загрузка изображения тайлсета */
        TextureHolder& textureHolder = TextureHolder::getInstance();
        textureHolder.loadFromFile("../map/src/" + tileset->tilesetImageSource,
                                   layerName);
    }

public:
    mutable std::vector<int> data;
    mutable std::unordered_map<int, sf::Vector2f> textureCords;
    std::vector<sf::FloatRect> wallBounds;

private:
    std::string layerName;
    sf::Vector2i size;
    sf::Vector2i left_top;
    sf::Vector2i right_bottom;

    Tileset* tileset;
};

#endif

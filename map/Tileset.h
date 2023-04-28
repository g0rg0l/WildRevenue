#ifndef UNTITLED_TILESET_H
#define UNTITLED_TILESET_H

#include <SFML/Graphics.hpp>
#include "rapidxml/rapidxml_utils.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>

class Tileset
{
public:
    Tileset(std::string  path, int firstgid) : firstgid(firstgid), tilesetSource(std::move(path)) {  }

public:
    void load()
    {
        /* Чтение .tsx файла */
        std::ifstream layerFile("../map/tilesets/" + tilesetSource);
        if (!layerFile)
        {
            std::cout << "unable to read" << tilesetSource << " file" << std::endl;
            exit(-1);
        }

        /* Парсинг в rapidXML */
        rapidxml::xml_document<> layerDoc;
        std::vector<char> layerBuffer((std::istreambuf_iterator<char>(layerFile)), std::istreambuf_iterator<char>());
        layerBuffer.push_back('\0');
        layerDoc.parse<0>(&layerBuffer[0]);

        auto root = layerDoc.first_node("tileset");

        /* Считывание атрибутов тайлсета */
        tilesetName = root->first_attribute("name")->value();
        tile_sizes = {
                std::stof(root->first_attribute("tilewidth")->value()),
                std::stof(root->first_attribute("tileheight")->value())
        };
        columns = std::stoi(root->first_attribute("columns")->value());
        tilesetImageSource = root->first_node("image")->first_attribute("source")->value();

        /* парсинг id стен */
        if (tilesetName == "decor")
        {
            auto cur_node = root->first_node("tile");
            while(cur_node)
            {
                std::string type = cur_node->first_attribute("type")->value();
                if (type == "wall")
                {
                    int id = std::stoi(cur_node->first_attribute("id")->value());
                    walls_ids.push_back(id);
                }

                cur_node = cur_node->next_sibling("tile");
            }
        }
    }

public:
    bool isWall(int id) const
    {
        return std::find(
                std::begin(walls_ids),
                std::end(walls_ids),
                id) != std::end(walls_ids);
    }

public:
    std::string tilesetName;
    std::string tilesetSource;
    std::string tilesetImageSource;
    int firstgid;
    int columns;
    sf::Vector2f tile_sizes;
    std::vector<int> walls_ids;
};

#endif

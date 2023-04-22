#ifndef UNTITLED_TILESET_H
#define UNTITLED_TILESET_H

#include <SFML/Graphics.hpp>
#include "rapidxml/rapidxml_utils.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

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
    }

public:
    std::string tilesetName;
    std::string tilesetSource;
    std::string tilesetImageSource;
    int firstgid;
    int columns;
    sf::Vector2f tile_sizes;
};

#endif

#ifndef UNTITLED_TEXTUREHOLDER_H
#define UNTITLED_TEXTUREHOLDER_H

#include "SFML/Graphics.hpp"
#include <map>
#include <string>


class TextureHolder
{

private:
    std::map<std::string, sf::Texture*> resourcesMap;

public:
    /////////////////////////////////// Конструкторы и деконструкторы ///////////////////////////////////
    TextureHolder() = default;
    ~TextureHolder()
    {
        for (auto &resource : resourcesMap)
        {
            delete resource.second;
        }
    }

    /////////////////////////////////// Получение глобального textureholder'а ///////////////////////////////////
    static TextureHolder& getInstance()
    {
        static TextureHolder textureHolder;

        return textureHolder;
    }

    /////////////////////////////////// Работа с TextureHolder'ом ///////////////////////////////////
    void loadFromFile(const std::string &fileName, const std::string &key) // Загрузка в TextureHolder текстуры
    {
        sf::Texture* &resource = resourcesMap[key];

        if (resource == nullptr)
        {
            resource = new sf::Texture;

            if (!resource->loadFromFile(fileName))
            {
                delete resource;
            }
        }
    }

    sf::Texture* getResource(const std::string &key) // Получение их TextureHolder'а текстуры
    {
        auto pairResourceIterator = resourcesMap.find(key);

        if (pairResourceIterator == resourcesMap.end())
        {
            return nullptr;
        }

        return pairResourceIterator->second;
    }
};


#endif

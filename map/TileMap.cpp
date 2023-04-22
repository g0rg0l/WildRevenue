#include "TileMap.h"

bool TileMap::load()
{
    /* Чтение .tmx файла */
    std::ifstream mapFile("../map/map.tmx");
    if (!mapFile)
    {
        std::cout << "unable to read map.tmx file" << std::endl;
        exit(-1);
    }

    /* Парсинг в rapidXML */
    rapidxml::xml_document<> mapDoc;
    std::vector<char> mapBuffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
    mapBuffer.push_back('\0');
    mapDoc.parse<0>(&mapBuffer[0]);

    auto root = mapDoc.first_node("map");

    /* Парсинг тайлсетов карты */
    auto node = root->first_node("tileset");
    while (node)
    {
        int tileset_firstgid = std::stoi(node->first_attribute("firstgid")->value());
        std::string tileset_path = node->first_attribute("source")->value();

        Tileset tileset(tileset_path, tileset_firstgid);
        tileset.load();
        tilesets.push_back(tileset);

        node = node->next_sibling("tileset");
    }

    /* Парсинг слоёв карты */
    node = root->first_node("layer");
    while (node)
    {
        std::string name = node->first_attribute("name")->value();
        int width = std::stoi(node->first_attribute("width")->value());
        int height = std::stoi(node->first_attribute("height")->value());

        Layer layer(name, width, height);

        /* getting layer's data */
        std::string layer_data = node->first_node("data")->value();
        std::stringstream ss(layer_data);
        int map_id;
        char ch;

        while(ss >> map_id)
        {
            ss >> ch;

            if (map_id == 0)
            {
                layer.add_data(-1);
                continue;
            }

            for (int j = tilesets.size() - 1; j >= 0; --j)
            {
                int tileset_firstgid = tilesets[j].firstgid;
                if (map_id >= tileset_firstgid)
                {
                    int layer_id = map_id - tileset_firstgid;
                    sf::Vector2f tex_cords = {
                            (layer_id % tilesets[j].columns) * tilesets[j].tile_sizes.x,
                            (layer_id / tilesets[j].columns) * tilesets[j].tile_sizes.y
                    };

                    layer.add_tile(layer_id, tex_cords);
                    layer.add_data(layer_id);

                    break;
                }
            }
        }

        /* Линковка тайлсета к слою карты */
        for (auto& tileset : tilesets)
            if (tileset.tilesetName == name)
            {
                layer.linkTileset(&tileset);
                break;
            }

        layers.push_back(layer);
        node = node->next_sibling("layer");
    }
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& layer : layers)
        layer.draw(target, states);
}

void TileMap::clip(sf::FloatRect viewRect)
{
    auto tileSizes = tilesets[0].tile_sizes;
    auto mapSizes = layers[0].get_size();

    int left = (int) std::max(0.f, int(std::lroundf(viewRect.left)) / tileSizes.y);
    int top = (int) std::max(0.f, int(std::lroundf(viewRect.top)) / tileSizes.y);
    int right = (int) std::min((float) mapSizes.x, int(std::lroundf(viewRect.left + viewRect.width)) / tileSizes.x + 1);
    int bottom = (int) std::min((float) mapSizes.y, int(std::lroundf(viewRect.top + viewRect.height)) / tileSizes.x + 1);

    right = right < 0 ? 0 : right;
    bottom = bottom < 0 ? 0 : bottom;
    left = left > 128 ? 128 : left;
    top = top > 128 ? 128 : top;

    for (auto& layer : layers)
        layer.clip({left, top}, {right, bottom});
}

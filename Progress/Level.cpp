
#include "Level.h"

Level::Level(Player* player, std::vector<Enemy*> &enemies)
    : player(player), enemies(enemies) {}

Level::~Level() {}

Level::tilemap_t Level::GetMapFromFile(const char* path)
{
    std::ifstream file;
    file.open(path);

    std::vector<std::string> charMap;

    unsigned int numberOfLines = GetNumberOfLines(path);

    for(int i = 0; i < numberOfLines; i++)
        charMap.push_back("");

    if (file.is_open())
    {
        for (int i = 0; i < numberOfLines; i++)
        {
            std::getline(file, charMap[i]);
        }
        file.close();
    }
    return charMap;
}

unsigned int Level::GetNumberOfLines(const char* path)
{
    unsigned int number_of_lines = 0;

    FILE* infile = fopen(path, "r");

    int ch;

    while (EOF != (ch = getc(infile)))
    {
        if ('\n' == ch)
            ++number_of_lines;
    }
    fclose(infile);
    return number_of_lines;
}

Level::tileset_t Level::GetTileSetFromFile(const char *path)
{
    std::ifstream file;
    file.open(path);

    unsigned int numberOfLines = GetNumberOfLines(path);

    std::list<char> collisionTiles;
    std::map<char, std::string> tileSet;

    if (file.is_open())
    {
        for (int i = 0; i < numberOfLines; i++)
        {
            std::string str;
            std::getline(file, str);

            char setFirst;

            if (str[0] == 'c')
            {
                setFirst = str[2];
                collisionTiles.push_back(setFirst);
            }
            else
                setFirst = str[0];

            std::string setSecond = str;

            if (str[0] == 'c')
                setSecond.erase(setSecond.begin(), setSecond.begin() + 4);
            else
                setSecond.erase(setSecond.begin(), setSecond.begin() + 2);


            tileSet.emplace(setFirst, setSecond);
        }
        file.close();
    }
    return tileset_t(collisionTiles, tileSet);
}

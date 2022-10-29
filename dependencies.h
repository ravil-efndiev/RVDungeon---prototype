
#ifndef RPG_DEPENDENCIES_H
#define RPG_DEPENDENCIES_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <stack>
#include <vector>
#include <unistd.h>
#include <list>
#include <map>
#include <cmath>
#include <fstream>
#include <dirent.h>

enum class MoveDirections
{
    right, left,
    up, down
};

class GLB
{
public:
    template<typename T>
    static void Sort(std::vector<T> vector)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            for (int j = i + 1; j < vector.size(); j++)
            {
                if (vector[i] > vector[j])
                    std::swap(vector[i], vector[j]);
            }
        }
    }
};

#endif //RPG_DEPENDENCIES_H

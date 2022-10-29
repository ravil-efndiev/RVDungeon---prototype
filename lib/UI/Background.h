
#ifndef UNTITLED7_BACKGROUND_H
#define UNTITLED7_BACKGROUND_H

#include <SFML/Graphics.hpp>

namespace gui
{
    class Background
    {
    private:
        sf::RectangleShape shape;
        sf::Sprite sprite;
        std::string type;

    public:
        Background(sf::Color color, sf::RenderWindow* window);
        Background(sf::Texture texture);

        virtual ~Background();

        void Render(sf::RenderTarget* target);
    };
}

#endif //UNTITLED7_BACKGROUND_H

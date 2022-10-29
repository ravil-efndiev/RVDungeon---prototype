
#ifndef UNTITLED7_LABEL_H
#define UNTITLED7_LABEL_H

#include <string>
#include <SFML/Graphics.hpp>

namespace gui
{
    class Label
    {
    private:
        sf::Text text;
        sf::Font font;

    public:
        Label(std::string string, sf::Color color, sf::Vector2f scale, sf::Vector2f position, std::string fontPath);

        virtual ~Label();

        void Render(sf::RenderTarget *target);
    };
}

#endif //UNTITLED7_LABEL_H

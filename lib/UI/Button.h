
#ifndef UNTITLED4_BUTTON_H
#define UNTITLED4_BUTTON_H

#include <SFML/Graphics.hpp>

namespace gui
{
    class Button
    {
    private:
        sf::Vector2f size;
        sf::RectangleShape shape;
        sf::Font font;
        std::string text;
        sf::Text displayText;
        sf::Color fillColor;
        sf::Vector2f mouse;
        sf::Vector2f mouseWorldPos;

        void (*Action)();

        bool Clicked();

    public:

        Button(sf::RectangleShape shape, std::string text, sf::Color fillColor, sf::Color textColor, sf::Vector2f size,
               sf::Vector2f position);

        virtual ~Button() {}

        void Update(sf::RenderWindow *window);
        void Render(sf::RenderTarget *target);

        void SetPosition(float x, float y);

        void BindOnClick(void (*action)());
    };
}

#endif


#include "Background.h"

using namespace gui;

Background::Background(sf::Color color, sf::RenderWindow* window)
{
    shape.setFillColor(color);
    shape.setSize(sf::Vector2f(window->getSize()));
    type = "rect_shape";
}

Background::Background(sf::Texture texture)
{
    sprite.setTexture(texture);
    type = "sprite";
}

Background::~Background() {}

void Background::Render(sf::RenderTarget *target)
{
    if (type == "rect_shape")
        target->draw(shape);
    else if (type == "sprite")
        target->draw(sprite);
}

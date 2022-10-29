
#include "Label.h"

using namespace gui;

Label::Label(std::string string, sf::Color color, sf::Vector2f scale, sf::Vector2f position, std::string fontPath)
{
    text.setString(string);
    text.setScale(scale);
    text.setFillColor(color);
    text.setPosition(position);

    font.loadFromFile(fontPath);
    text.setFont(font);
}

Label::~Label()
{

}

void Label::Render(sf::RenderTarget *target)
{
    target->draw(text);
}


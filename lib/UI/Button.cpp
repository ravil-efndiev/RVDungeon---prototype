
#include "Button.h"

using namespace gui;

Button::Button(sf::RectangleShape shape, std::string text, sf::Color fillColor, sf::Color textColor, sf::Vector2f size, sf::Vector2f position)
{
    this->shape = shape;
    this->text = text;
    this->fillColor = fillColor;
    this->size = size;

    displayText.setString(this->text);
    this->shape.setSize(this->size);
    this->shape.setFillColor(this->fillColor);

    SetPosition(position.x, position.y);
    font.loadFromFile("resources/Roboto-Regular.ttf");
    displayText.setFont(font);
    displayText.setFillColor(textColor);
}

void Button::Update(sf::RenderWindow* window)
{
    mouse = sf::Vector2f(sf::Mouse::getPosition(*window));
    mouseWorldPos = window->mapPixelToCoords(sf::Vector2i(mouse));

    displayText.setPosition(sf::Vector2f(shape.getPosition().x + size.x / 3, shape.getPosition().y + size.y / 3));

    if (Clicked() && Action != NULL)
        Action();
}

void Button::Render(sf::RenderTarget *target)
{
    target->draw(shape);
    target->draw(displayText);
}


void Button::SetPosition(float x, float y)
{
    shape.setPosition(x, y);
}

bool Button::Clicked()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) && shape.getGlobalBounds().contains(sf::Vector2f(mouseWorldPos));
}

void Button::BindOnClick(void (*action)())
{
    Action = action;
}

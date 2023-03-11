#include "Button.hpp"
Button::Button(std::string str, sf::Color textColor, sf::Font &font,sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    text.setFont(font);
    text.setString(str);
    text.setColor(textColor);
    text.setCharacterSize(buttonSize.y / 3);

    button.setOutlineThickness(6);
    button.setOutlineColor(sf::Color::Black);
    button.setSize(buttonSize);
    button.setFillColor(backgroundColor);
}

void Button::setTextFont(sf::Font &font)
{
    text.setFont(font);
}

void Button::setBackColor(sf::Color color)
{
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
    text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos)
{
    button.setPosition(pos);

    float xPos = pos.x + (button.getGlobalBounds().width - text.getLocalBounds().width) / 2.2;
    float yPos = pos.y + text.getLocalBounds().height;

    text.setPosition({xPos, yPos});
}

void Button::drawButton(sf::RenderWindow &window)
{
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOnButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    sf::Vector2f buttonPos = button.getPosition();

    sf::Vector2f buttonSize = button.getSize();
    // lon hon hoac bang can trai/tren va nho hon hoac bang can trai/duoi
    return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
}

bool Button::hoverChangeColor(sf::Event &ev, sf::RenderWindow &window)
{
    if (this->isMouseOnButton(window))
    {
        this->setBackColor(sf::Color(50, 60, 70));
        return true;
    }
    else
        this->setBackColor(sf::Color::White);
    return false;
}

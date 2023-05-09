#include "ArrNode.hpp"

ArrNode::ArrNode(std::string str, sf::Color numColor, sf::Font &font, float size, sf::Color backgroundColor)
{
    numbers.setFont(font);
    numbers.setString(str);
    numbers.setColor(numColor);
    numbers.setCharacterSize(2 * size / 3);

    rect.setOutlineThickness(4.f);
    rect.setOutlineColor(sf::Color::Black);
    rect.setSize({size, size});
    rect.setFillColor(backgroundColor);
}

void ArrNode::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos);

    float xPos = pos.x + (rect.getGlobalBounds().width - numbers.getLocalBounds().width) / 3.0;
    float yPos = pos.y + numbers.getLocalBounds().height / 2.5;

    numbers.setPosition({xPos, yPos});
}

void ArrNode::draw(sf::RenderWindow &window)
{
    window.draw(rect);
    window.draw(numbers);
}

sf::Vector2f ArrNode::getCenter()
{
    sf::Vector2f curPos = rect.getPosition();
    float size = rect.getLocalBounds().width;
    return {curPos.x + size, curPos.y + size};
}

void ArrNode::setString(std::string str)
{
    numbers.setString(str);
    this->setPosition(this->getPosition());
}

std::string ArrNode::getString()
{
    return numbers.getString();
}

sf::Vector2f ArrNode::getPosition()
{
    return rect.getPosition();
}

void ArrNode::setSize(float size)
{
    sf::Vector2f currCen = this->getCenter();
    rect.setSize({size, size});
    numbers.setCharacterSize(2 * size / 3);

    this->setPosition({currCen.x - size, currCen.y - size});
}

float ArrNode::getSize()
{
    return rect.getLocalBounds().width;
}

void ArrNode::setBackgroundColor(const sf::Color &color)
{
    rect.setFillColor(color);
}
#include "LLNode.hpp"

LLNode::LLNode(std::string str, sf::Color numColor, sf::Font &font, float radius, sf::Color backgroundColor)
{
    numbers.setFont(font);
    numbers.setString(str);
    numbers.setColor(numColor);
    numbers.setCharacterSize(2 * radius / 3);

    circle.setOutlineThickness(4.f);
    circle.setOutlineColor(sf::Color::Black);
    circle.setRadius(radius);
    circle.setFillColor(backgroundColor);
}

void LLNode::setPosition(sf::Vector2f pos)
{
    circle.setPosition(pos);

    float xPos = pos.x + (2 * circle.getRadius() - numbers.getLocalBounds().width) / 2.2;
    float yPos = pos.y + numbers.getLocalBounds().height;

    numbers.setPosition({xPos, yPos});
}

void LLNode::draw(sf::RenderWindow &window)
{
    window.draw(circle);
    window.draw(numbers);
}

sf::Vector2f LLNode::getCenter()
{
    sf::Vector2f curPos = circle.getPosition();
    float radius = circle.getRadius();
    return {curPos.x + radius, curPos.y + radius};
}
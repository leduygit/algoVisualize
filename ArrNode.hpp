#ifndef _ArrNode_h_
#define _ArrNode_h_
#include "ArrowLine.hpp"
class ArrNode
{
public:
    ArrNode(){};
    ArrNode(std::string str, sf::Color numColor, sf::Font &font, float size, sf::Color backgroundColor);
    void setPosition(sf::Vector2f pos);
    void setString(std::string str);
    void draw(sf::RenderWindow &window);
    std::string getString();
    sf::Vector2f getCenter();
    sf::Vector2f getPosition();
    void setSize(float size);
    float getSize();
    void setBackgroundColor(const sf::Color &color);

private:
    sf::RectangleShape rect;
    sf::Text numbers;
};
#endif
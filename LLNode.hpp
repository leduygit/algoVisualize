#ifndef _LLNODE_h_
#define _LLNODE_h_
#include "ArrowLine.hpp"
class LLNode
{
public:
    LLNode(){};
    LLNode(std::string str, sf::Color numColor, sf::Font &font, float radius, sf::Color backgroundColor);
    void setPosition(sf::Vector2f pos);
    void setString(std::string str);
    void draw(sf::RenderWindow &window);
    std::string getString();
    sf::Vector2f getCenter();
    sf::Vector2f getPosition();
    void setRadius(float radius);
    float getRadius();

private:
    sf::CircleShape circle;
    sf::Text numbers;
};
#endif
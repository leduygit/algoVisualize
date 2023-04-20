#ifndef _highlight_h_
#define _highlight_h_
#include <SFML/Graphics.hpp>
#include "Image.hpp"

class Highlight
{
private:
    Image codeImage;
    sf::RectangleShape highlight;
public:
    Highlight(std::string file = "", const sf::Color &color = sf::Color(255, 255, 255, 150));
    void loadTexture(std::string file = "");
    void setLine(int line);
    void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f pos);
};

#endif
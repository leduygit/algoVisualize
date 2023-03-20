#ifndef _arrowLine_h
#define _arrowLine_h
#include <SFML/Graphics.hpp>
#include <math.h>

class arrowLine
{
private:
    sf::RectangleShape body;
    sf::VertexArray arrow;
    int currRotation;
    int arrowHeight;
public:
    arrowLine(sf::Vector2f bodySize, int _arrowHeight);
    void setPosition(sf::Vector2f bodyPosition);
    void setArrowPosition();
    void setRotation();
};

#endif
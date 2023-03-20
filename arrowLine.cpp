#include "arrowLine.hpp"

arrowLine::arrowLine(sf::Vector2f bodysize, int _arrowHeight)
{
    this->arrow = sf::VertexArray(sf::Lines, 3);
    this->body.setSize(bodysize);
    this->arrowHeight = _arrowHeight;
    for (int i = 0; i < 3; ++i)
        this->arrow[i].color = sf::Color::Black;
    this->body.setFillColor(sf::Color::Black);
    currRotation = 0;
}


void arrowLine::setArrowPosition()
{
    sf::Vector2f bodyOrigin = this->body.getPosition();
    int bodyHeight = this->body.getSize().y;
    int bodyWidth = this->body.getSize().x;

    // 4th quarter corner
        // bottom position of the body
    sf::Vector2f bodyBottomLeft = {bodyOrigin.x + bodyHeight * sin(this->currRotation), bodyOrigin.y + bodyHeight * cos(this->currRotation)};
    sf::Vector2f bodyBottomRight = {bodyBottomLeft.x + bodyWidth * cos(this->currRotation), bodyBottomLeft.y + bodyWidth * sin(this->currRotation)};

    sf::Vector2f linearEquation = calLinearEquation(bodyBottomLeft, bodyBottomRight);
    double a = linearEquation.x;
    double b = linearEquation.y;

    double distance = 2 * this->arrowHeight - bodyWidth;
    
    // left Point of the arrow
    sf::Vector2f leftPointArrow;
    leftPointArrow.x = bodyBottomLeft.x - distance / sqrt(a * a + 1) ;
    leftPointArrow.y = leftPointArrow.x * a + b;

    // right point of the arrow
    sf::Vector2f rightPointArrow;
    rightPointArrow.x = bodyBottomRight.x + distance / sqrt(a * a + 1);
    rightPointArrow.y = bodyBottomRight.x * a + b;


    sf::Vector2f centerPointArrow;
    double arrowEdge = arrowHeight / sin(45);
    centerPointArrow.x = leftPointArrow.x + arrowEdge * sin(180 - currRotation - 45);
    centerPointArrow.y = leftPointArrow.y + arrowEdge * cos(180 - currRotation - 45);


    arrow[0].position(rightPointArrow);
    arrow[1].position(leftPointArrow);
}

void arrowLine::setPosition(sf::Vector2f bodyPosition)
{
    this->body.setPosition(bodyPosition);
    setArrowPosition();
}

void arrowLine::setRotation()
{
    this->currRotation++;
    setArrowPosition();
}



#include "ArrowLine.hpp"

ArrowShape::ArrowShape(float width, float height, float tipWidth, float tipHeight)
{
    m_width = width; m_height = height;
    m_tipWidth = tipWidth; m_tipHeight = tipHeight;
    // Define the shape of the arrow
    // const float x1 = 0.f;
    // const float x2 = width - tipWidth;
    // const float x3 = width;
    // const float y1 = 0.f;
    // const float y2 = (height - tipHeight) / 2.f;
    // const float y3 = (height + tipHeight) / 2.f;
    m_arrowBody.setPosition({0, 0});
    m_arrowBody.setSize({width, height});
    m_arrowTip.setPointCount(3);
    m_arrowTip.setPoint(0, {width + tipWidth, height / 2});

    float exceed = (tipHeight - height) / 2;
    m_arrowTip.setPoint(1, {width, -exceed});
    m_arrowTip.setPoint(2, {width, height + exceed});

}

void ArrowShape::setColor(const sf::Color &color)
{
    m_arrowBody.setFillColor(color);
    m_arrowTip.setFillColor(color);
}

void ArrowShape::setOutlineColor(const sf::Color &color)
{
    m_arrowBody.setOutlineColor(color);
    m_arrowTip.setOutlineColor(color);
}

void ArrowShape::setOutlineThickness(float thickness)
{
    m_arrowBody.setOutlineThickness(thickness);
    m_arrowTip.setOutlineThickness(thickness);
}



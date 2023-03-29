#ifndef _arrow_h_
#define _arrow_h_
#include <SFML/Graphics.hpp>
class ArrowShape : public sf::Drawable, public sf::Transformable
{
public:
    ArrowShape(float width, float height, float tipWidth, float tipHeight);
    
    void setColor(const sf::Color &color);

    void setOutlineColor(const sf::Color &color);

    void setOutlineThickness(float thickness);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_arrowBody, states);
        target.draw(m_arrowTip, states);
    }

    float m_width;
    float m_height;
    float m_tipWidth;
    float m_tipHeight;
    sf::RectangleShape m_arrowBody;
    sf::ConvexShape m_arrowTip;
};

#endif

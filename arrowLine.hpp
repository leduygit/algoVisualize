#ifndef _arrow_h_
#define _arrow_h_
#include <SFML/Graphics.hpp>
class ArrowShape : public sf::Drawable, public sf::Transformable
{
public:
    ArrowShape(float width = 0, float height = 0, float tipWidth = 0, float tipHeight = 0);
    
    void setColor(const sf::Color &color);

    void setOutlineColor(const sf::Color &color);

    void setOutlineThickness(float thickness);

    sf::Vector2f getTipPosition();
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_arrowBody, states);
        target.draw(m_arrowTip, states);
    }

    float m_width = 0;
    float m_height = 0;
    float m_tipWidth = 0;
    float m_tipHeight = 0;
    sf::RectangleShape m_arrowBody;
    sf::ConvexShape m_arrowTip;
};

#endif

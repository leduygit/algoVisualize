#include "Highlight.hpp"

Highlight::Highlight(std::string file, const sf::Color &color)
{
    if (file != "")
        codeImage.loadTexture(file);
    highlight.setSize({800, 20});
    highlight.setFillColor(color);
}

void Highlight::loadTexture(std::string file)
{
    codeImage.loadTexture(file);
}

void Highlight::setLine(int line)
{
    sf::Vector2f pos = codeImage.getPosition();
    pos.y += 57;
    sf::Vector2f sz = highlight.getSize();
    highlight.setPosition({pos.x, pos.y + (line - 1) * sz.y + 2.3 * (line - 1)});
}

void Highlight::draw(sf::RenderWindow &window){
    codeImage.draw(window);
    window.draw(highlight);
}

void Highlight::setPosition(sf::Vector2f pos)
{
    codeImage.setPosition(pos);
    highlight.setPosition({910, 577 + 57});
}

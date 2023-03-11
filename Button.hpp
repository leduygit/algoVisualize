#ifndef _button_h
#define _button_h
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Button
{
public:
    Button(){};
    Button(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);

    void setTextFont(sf::Font &font);

    void setBackColor(sf::Color color);

    void setTextColor(sf::Color color);

    void setPosition(sf::Vector2f pos);

    void drawButton(sf::RenderWindow &window);

    bool isMouseOnButton(sf::RenderWindow &window);

    bool hoverChangeColor(sf::Event &ev, sf::RenderWindow &window);
private:
    sf::RectangleShape button;
    sf::Text text;
};
#endif
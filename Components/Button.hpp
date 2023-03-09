#ifndef _button_h
#define _button_h
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button();
    Button(std::string str, sf::Vector2f buttonSize, int charSize, sf::Color backgroundColor, sf::Color textColor)
    {
        text.setString(str);
        text.setColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(buttonSize);
        button.setFillColor(backgroundColor);
    }

    void setFont(sf::Font &font){
        text.setFont(font);
    }

    void setBackColor(sf::Color color){
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color){
        text.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);
    }
private:
    sf::RectangleShape button;
    sf::Text text;
};
#endif
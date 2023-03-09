#ifndef _button_h
#define _button_h
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(){};
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

        float xPos = (pos.x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
        float yPos = (pos.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
        text.setPosition({xPos, yPos});
    }

    void drawButton(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOnButton(sf::RenderWindow &window){
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        sf::Vector2f buttonPos = button.getPosition();

        sf::Vector2f buttonSize = button.getSize();
        return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x
             && mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
    }
private:
    sf::RectangleShape button;
    sf::Text text;
};
#endif
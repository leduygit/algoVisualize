#ifndef _button_h
#define _button_h
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Button
{
public:
    Button(){};
    Button(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
    {
        text.setString(str);
        text.setColor(textColor);
        text.setFont(font);
        text.setCharacterSize(buttonSize.y / 3);

        button.setOutlineThickness(6);
        button.setOutlineColor(sf::Color::Green);
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

        float xPos = pos.x + (button.getGlobalBounds().width - text.getLocalBounds().width) / 2.2;
        float yPos = pos.y + text.getLocalBounds().height;
        //std::cout << text.getLocalBounds().width << ' ' << text.getLocalBounds().height << '\n';
        //std::cout << xPos << ' ' << yPos << ' ' << pos.x << ' ' << pos.y << '\n';
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

    bool hoverChangeColor(sf::Event &ev, sf::RenderWindow &window){
        if (this->isMouseOnButton(window)){
            this->setBackColor(sf::Color::Cyan);
            return true;
        }
        else
            this->setBackColor(sf::Color::White);
        return false;
    }
private:
    sf::RectangleShape button;
    sf::Text text;
};
#endif
#ifndef _menu_h
#define _menu_h
#include <SFML/Graphics.hpp>
#include "Button.hpp"
class Menu
{
public:

    void setStart(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor){
        startButton = Button(str, textColor, font, buttonSize, backgroundColor);
    }

    void setPos(sf::Vector2f pos){
        startButton.setPosition(pos);
        settingButton.setPosition({pos.x, pos.y + 140});
    }

    void setSetting(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor){
        settingButton = Button(str, textColor, font, buttonSize, backgroundColor);
    }

    void drawMenu(sf::RenderWindow &window){
        startButton.drawButton(window);
        settingButton.drawButton(window);
    }

    bool checkMenuButton(sf::Event &ev, sf::RenderWindow &window){
        if (startButton.hoverChangeColor(ev, window)) return true;
        if (settingButton.hoverChangeColor(ev, window)) return true;
        return false;
    }
private:
    Button startButton = Button();
    Button settingButton = Button();
};
#endif

#ifndef _menu_h
#define _menu_h
#include <SFML/Graphics.hpp>
#include "Button.hpp"
class Menu
{
public:
    void setStart(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
    {
        startButton = Button(str, textColor, font, buttonSize, backgroundColor);
    }

    void setPos(sf::Vector2f pos)
    {
        startButton.setPosition(pos);
        settingButton.setPosition({pos.x, pos.y + 200});
    }

    void setSetting(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
    {
        settingButton = Button(str, textColor, font, buttonSize, backgroundColor);
    }

    void drawMenu(sf::RenderWindow &window)
    {
        startButton.drawButton(window);
        settingButton.drawButton(window);
    }

    bool checkMenuButton(sf::Event &ev, sf::RenderWindow &window)
    {
        // mouse on start button
        if (startButton.hoverChangeColor(ev, window))
            return true;

        // mouse on setting button
        if (settingButton.hoverChangeColor(ev, window))
            return true;

        return false;
    }

    int changeScreenID(sf::Event &ev, sf::RenderWindow &window, int currentScreenID)
    {
        // mouse clicked
        if (startButton.isMouseOnButton(window)) return 2; // 2 = choosing data structure
        if (settingButton.isMouseOnButton(window)) return 3; // 3 = setting the application
        return currentScreenID;
    }

private:
    Button startButton = Button();
    Button settingButton = Button();
};
#endif

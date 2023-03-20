#ifndef _menu_h
#define _menu_h
#include <SFML/Graphics.hpp>
#include "Button.hpp"

// main menu ID = 1
class Menu
{
public:
    void setMenuFont(sf::Font &font);
    void setStart(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setPos(sf::Vector2f pos);
    void setSetting(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void drawMenu(sf::RenderWindow &window);
    bool checkMenuButton(sf::Event &ev, sf::RenderWindow &window);
    void changeScreenID(sf::Event &ev, sf::RenderWindow &window, int &currentScreenID);
    void handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID);
private:
    Button startButton = Button();
    Button settingButton = Button();
};
#endif

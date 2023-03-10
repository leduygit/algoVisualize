#include "Components/Menu.hpp"
void Menu::setStart(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    startButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void Menu::setPos(sf::Vector2f pos)
{
    startButton.setPosition(pos);
    settingButton.setPosition({pos.x, pos.y + 200});
}

void Menu::setSetting(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    settingButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void Menu::drawMenu(sf::RenderWindow &window)
{
    startButton.drawButton(window);
    settingButton.drawButton(window);
}

bool Menu::checkMenuButton(sf::Event &ev, sf::RenderWindow &window)
{
    // mouse on start button
    if (startButton.hoverChangeColor(ev, window))
        return true;

    // mouse on setting button
    if (settingButton.hoverChangeColor(ev, window))
        return true;

    return false;
}

void Menu::changeScreenID(sf::Event &ev, sf::RenderWindow &window, int &currentScreenID)
{
    // mouse clicked
    if (startButton.isMouseOnButton(window))
        currentScreenID = 2; // 2 = choosing data structure
    else if (settingButton.isMouseOnButton(window))
        currentScreenID = 3; // 3 = setting the application
    return;
}
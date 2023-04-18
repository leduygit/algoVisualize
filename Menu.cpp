#include "Menu.hpp"

void Menu::setMenuFont(sf::Font &font)
{
    startButton.setTextFont(font);
    settingButton.setTextFont(font);
}

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

void Menu::setOutlineThickness(float thickness)
{
    startButton.setOutlineThickness(thickness);
    settingButton.setOutlineThickness(thickness);
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

void Menu::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
{
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case (sf::Event::Closed):
            window.close();
            break;
        case (sf::Event::MouseMoved):
            this->checkMenuButton(ev, window);
            break;
        case (sf::Event::MouseButtonPressed):
            this->changeScreenID(ev, window, screenID);
            break;
        default:
            break;
        }
    }
    window.clear(sf::Color(124,143,160));
    window.draw(background);
    this->drawMenu(window);
}
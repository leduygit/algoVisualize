#include "DatabaseMenu.hpp"

void DatabaseMenu::setStaticButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    staticArrayButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setDynamicButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    dynamicArrayButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setSinglyButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    singlyLinkedListButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setDoublyButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    doublyLinkedListButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setCircularButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    circularLinkedListButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setStackButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    stackButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setQueueButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    queueButton = Button(str, textColor, font, buttonSize, backgroundColor);
}

void DatabaseMenu::setupDatabaseMenu(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    staticArrayButton = Button("Static Array", textColor, font, buttonSize, backgroundColor);
    dynamicArrayButton = Button("Dynamic Array", textColor, font, buttonSize, backgroundColor);
    singlyLinkedListButton = Button("Singly Linked List", textColor, font, buttonSize, backgroundColor);
    doublyLinkedListButton = Button("Doubly Linked List", textColor, font, buttonSize, backgroundColor);
    circularLinkedListButton = Button("Circular Linked List", textColor, font, buttonSize, backgroundColor);
    stackButton = Button("Stack", textColor, font, buttonSize, backgroundColor);
    queueButton = Button("Queue", textColor, font, buttonSize, backgroundColor);
    backButton = Button("Return", textColor, font, {buttonSize.x - 280, buttonSize.y - 50}, backgroundColor);
}


void DatabaseMenu::drawDatabaseMenu(sf::RenderWindow &window)
{
    staticArrayButton.drawButton(window);
    dynamicArrayButton.drawButton(window);
    singlyLinkedListButton.drawButton(window);
    doublyLinkedListButton.drawButton(window);
    circularLinkedListButton.drawButton(window);
    stackButton.drawButton(window);
    queueButton.drawButton(window);
    backButton.drawButton(window);
}

void DatabaseMenu::setPosition(sf::Vector2f pos)
{
    backButton.setPosition({30, 40});

    //first line
    staticArrayButton.setPosition({260 + pos.x, pos.y});
    dynamicArrayButton.setPosition({260 + pos.x + 500, pos.y});

    // second line
    singlyLinkedListButton.setPosition({pos.x, pos.y + 140});
    doublyLinkedListButton.setPosition({pos.x + 500, pos.y + 140});
    circularLinkedListButton.setPosition({pos.x + 1000, pos.y + 140});

    // third line
    stackButton.setPosition({260 + pos.x, pos.y + 280});
    queueButton.setPosition({260 + pos.x + 500, pos.y + 280});
}

bool DatabaseMenu::checkMenuButton(sf::Event &ev, sf::RenderWindow &window)
{
    if (backButton.hoverChangeColor(ev, window)) return true;
    if (staticArrayButton.hoverChangeColor(ev, window)) return true;
    if (dynamicArrayButton.hoverChangeColor(ev, window)) return true;
    if (singlyLinkedListButton.hoverChangeColor(ev, window)) return true;
    if (doublyLinkedListButton.hoverChangeColor(ev, window)) return true;
    if (circularLinkedListButton.hoverChangeColor(ev, window)) return true;
    if (stackButton.hoverChangeColor(ev, window)) return true;
    if (queueButton.hoverChangeColor(ev, window)) return true;
    return false;
}

void DatabaseMenu::changeScreenID(sf::Event &ev, sf::RenderWindow &window, int &screenID)
{
    if (staticArrayButton.isMouseOnButton(window)) screenID = 4;
    else if (dynamicArrayButton.isMouseOnButton(window)) screenID = 5;
    else if (singlyLinkedListButton.isMouseOnButton(window)) screenID = 6;
    else if (doublyLinkedListButton.isMouseOnButton(window)) screenID = 7;
    else if (circularLinkedListButton.isMouseOnButton(window)) screenID = 8;
    else if (stackButton.isMouseOnButton(window)) screenID = 9;
    else if (queueButton.isMouseOnButton(window)) screenID = 10;
    else if (backButton.isMouseOnButton(window)) screenID = 1;
    return;
}

void DatabaseMenu::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID)
{
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case (sf::Event::Closed):
            window.close();
            break;
        case (sf::Event::MouseMoved):
            if (this->checkMenuButton(ev, window))
                break;
        case (sf::Event::MouseButtonPressed):
            this->changeScreenID(ev, window, screenID);
        default:
            break;
        }
    }

    window.clear(sf::Color::White);
    this->drawDatabaseMenu(window);
}
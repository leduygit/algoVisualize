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
    backButton = Button("Return", textColor, font, {buttonSize.x - 200, buttonSize.y}, backgroundColor);
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
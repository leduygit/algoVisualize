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
    backButton = Button("Return", textColor, font, buttonSize, backgroundColor);
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
#ifndef _database_h
#define _database_h
#include "Button.hpp"

// Database Menu ID = 2
class DatabaseMenu{
public:
    DatabaseMenu() {};
    void setStaticButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setDynamicButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setSinglyButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setDoublyButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setCircularButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setStackButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setQueueButton(std::string str, sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void setupDatabaseMenu(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void drawDatabaseMenu(sf::RenderWindow &window);
    void setPosition(sf::Vector2f pos);
    bool checkMenuButton(sf::Event &ev, sf::RenderWindow &window);
    void changeScreenID(sf::Event &ev, sf::RenderWindow &window, int &screenID);
    void handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);
private:
    Button staticArrayButton = Button(); // ID = 4
    Button dynamicArrayButton = Button(); // ID = 5
    Button singlyLinkedListButton = Button(); // ID = 6
    Button doublyLinkedListButton = Button(); // ID = 7
    Button circularLinkedListButton = Button(); // ID = 8
    Button stackButton = Button(); // ID = 9
    Button queueButton = Button(); // ID = 10
    //Button backButton = Button();
};
#endif
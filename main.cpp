#include "Menu.hpp"
#include "DatabaseMenu.hpp"
using namespace std;

void menuInitialize(Menu &menu, sf::Font &font)
{
    sf::Vector2f menuButtonSize(500.f, 120.f);
    sf::Color textColor(90, 200, 200);
    menu.setStart("Start", textColor, font, menuButtonSize, sf::Color::White);
    menu.setSetting("Setting", textColor, font, menuButtonSize, sf::Color::White);
    menu.setPos({550, 320});
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Visualize algo", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font consolas;
    consolas.loadFromFile("Font/Consolas.ttf");

    // Main menu setup
    Menu menu;
    menuInitialize(menu, consolas);
    window.clear(sf::Color::White);
    int screenID = 1;

    // database Menu setup
    sf::Vector2f menuButtonSize(460.f, 110.f);
    sf::Color textColor(90, 200, 200);
    DatabaseMenu dataMenu;
    dataMenu.setupDatabaseMenu(textColor, consolas, menuButtonSize, sf::Color::White);
    dataMenu.setPosition({30, 280});

    // 1 = Default Menu
    // 2 = Database Menu
    // 3 = Setting

    while (window.isOpen())
    {
        sf::Event ev;
        
        switch (screenID)
        {
        case 1:
            menu.handleEvent(ev, window, screenID);
            break;
        default:
            dataMenu.handleEvent(ev, window, screenID);
            break;
        }

        cout << screenID << '\n';
        window.display();
    }
}
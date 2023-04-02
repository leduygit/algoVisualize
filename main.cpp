#include "Menu.hpp"
#include "DatabaseMenu.hpp"
#include "ArrowLine.hpp"
#include "LLNode.hpp"
#include "SLL.hpp"

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

    sf::VertexArray lines(sf::Lines, 3);

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

    // SLL menu setup
    sf::Vector2f SinglyButtonSize = {100, 50};
    SLL SinglyMenu(textColor, consolas, SinglyButtonSize, sf::Color::White);


    // 1 = Default Menu
    // 2 = Database Menu
    // 3 = Setting
    // 4 = Singly linked list

    // ArrowShape arrow(100.f, 5.f, 10.f, 20.f);
    // arrow.setOutlineThickness(3.f);
    // arrow.setPosition({100, 100});
    // arrow.setOutlineColor(sf::Color::Black);
    // arrow.setColor(sf::Color::Cyan);
    // arrow.setRotation(140);

    LLNode test("123", sf::Color::Black, consolas, 30.f, sf::Color::White);
    test.setPosition({50, 50});


    while (window.isOpen())
    {
        sf::Event ev;

        switch (screenID)
        {
        case 1:
            menu.handleEvent(ev, window, screenID);
            break;
        case 6:
            SinglyMenu.handleEvent(ev, window, screenID);
            break;
        default:
            dataMenu.handleEvent(ev, window, screenID);
            break;
        }

        //test.draw(window);
        //window.draw(arrow);
        //std::cout << screenID << '\n';
        window.display();
    }
}
#include "Menu.hpp"
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
    window.setFramerateLimit(144);

    sf::Font consolas;
    consolas.loadFromFile("Font/Consolas.ttf");

    Menu menu;
    menuInitialize(menu, consolas);
    window.clear(sf::Color::White);
    int screenID = 1;

    // 1 = Default Menu
    // 2 = Database Menu
    // 3 = Setting

    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case (sf::Event::Closed):
                window.close();
                break;
            case (sf::Event::MouseMoved):
                if (menu.checkMenuButton(ev, window))
                    break;
            case (sf::Event::MouseButtonPressed):
                menu.changeScreenID(ev, window, screenID);
                break;
            default:
                break;
            }
        }

        cout << screenID << '\n';
        window.clear(sf::Color::White);
        menu.drawMenu(window);
        window.display();
    }
}
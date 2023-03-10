#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Components/Button.hpp"
#include "Components/Menu.hpp"
using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Visualize algo");
    sf::Font consolas;
    consolas.loadFromFile("Font/Consolas.ttf");

    Button testButton("Testing", sf::Color::Blue, consolas, {300, 120}, sf::Color::Red);
    testButton.setPosition({750, 450});

    Menu menu;
    menu.setStart("Start", sf::Color::Blue, consolas, {300, 120}, sf::Color::White);
    menu.setSetting("Setting", sf::Color::Blue, consolas, {300, 120}, sf::Color::White);

    menu.setPos({650, 320});

    while (window.isOpen()){
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
            default:
                break;
            }
        }

        window.clear();
        menu.drawMenu(window);
        window.display();
    }
}
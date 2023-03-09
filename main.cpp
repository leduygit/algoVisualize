#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Components/Button.hpp"
using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Visualize algo");
    sf::Font consolas;
    consolas.loadFromFile("Font/Consolas.ttf");

    Button testButton("Testing", {100, 60}, 10, sf::Color::White, sf::Color::Green);
    testButton.setPosition({80, 80});
    testButton.setFont(consolas);

    while (window.isOpen()){
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //Button testButton;
        testButton.drawButton(window);
        window.display();
    }
}
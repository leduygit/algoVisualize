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

    Button testButton("Testing", sf::Color::Blue, consolas, {300, 120}, sf::Color::Red);
    testButton.setPosition({750, 450});


    // Button button2("Duy Anh", {300, 150}, 30, sf::Color::White, sf::Color::Blue);
    // button2.setPosition({100, 100});
    // button2.setFont(consolas);

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
                if (testButton.isMouseOnButton(window))
                    testButton.setBackColor(sf::Color::Green);
                else
                    testButton.setBackColor(sf::Color::White);
            default:
                break;
            }
        }

        window.clear();
        //Button testButton;
        testButton.drawButton(window);
        window.display();
    }
}
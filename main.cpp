#include "Menu.hpp"
#include "DatabaseMenu.hpp"
#include "ArrowLine.hpp"
#include "LLNode.hpp"
#include "SLL.hpp"
#include "Textbox.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "DLL.hpp"
#include "StaticArray.hpp"
#include "DynamicArray.hpp"

void menuInitialize(Menu &menu, sf::Font &font)
{
    sf::Vector2f menuButtonSize(500.f, 120.f);
    sf::Color textColor(87,113,138);
    menu.setStart("Start", textColor, font, menuButtonSize, sf::Color::White);
    menu.setSetting("Setting", textColor, font, menuButtonSize, sf::Color::White);
    menu.setPos({550, 320});
    menu.setOutlineThickness(6);
}

void changeScreen(int oldID, int newID)
{
    // menu = 1
    // database menu = 2
    // setting = 3
    // static = 4
    // dynamic = 5
    // singly = 6
    // doubly = 7
    // circular = 8
    // stack = 9
    // queue = 10

}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Visualize algo", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    sf::VertexArray lines(sf::Lines, 3);

    sf::Font consolas;
    consolas.loadFromFile("Font/NotoSerifHebrew_Condensed-Black.ttf");

    // Main menu setup
    Menu menu;
    menuInitialize(menu, consolas);
    window.clear(sf::Color::White);
    int screenID = 1;

    // database Menu setup
    sf::Vector2f menuButtonSize(460.f, 110.f);
    sf::Color textColor(87,113,138);
    DatabaseMenu dataMenu;
    dataMenu.setupDatabaseMenu(textColor, consolas, menuButtonSize, sf::Color::White);
    dataMenu.setPosition({30, 280});

    // menu = 1
    // database menu = 2
    // setting = 3
    // static = 4
    // dynamic = 5
    // singly = 6
    // doubly = 7
    // circular = 8
    // stack = 9
    // queue = 10

    // SLL menu setup
    sf::Vector2f featureButtonSize = {100, 50};
    SLL SinglyMenu(textColor, consolas, featureButtonSize, sf::Color::White);

    // Stack menu setup
    Stack StackMenu(textColor, consolas, featureButtonSize, sf::Color::White);

    // Queue menu setup
    Queue queueMenu(textColor, consolas, featureButtonSize, sf::Color::White);

    // DLL menu setup
    DLL DoublyMenu(textColor, consolas, featureButtonSize, sf::Color::White);

    // Static Array menu setup
    StaticArray StaticMenu(textColor, consolas, featureButtonSize, sf::Color::White);

    // Dynamic Array menu setup
    DynamicArray DynamicMenu(textColor, consolas, featureButtonSize, sf::Color::White);


    // background image
    sf::Texture texture;
    texture.loadFromFile("Image/background.png");
    sf::Sprite background;
    background.setTexture(texture);

    sf::Texture featureTexture;
    featureTexture.loadFromFile("Image/FeatureBackground.png");
    sf::Sprite featureBack;
    featureBack.setTexture(featureTexture);



    // 1 = Default Menu
    // 2 = Database Menu
    // 3 = Setting
    // 6 = Singly linked list

   



    while (window.isOpen())
    {
        sf::Event ev;

        switch (screenID)
        {
        case 1:
            menu.handleEvent(ev, window, screenID, background);
            break;
        case 2:
            dataMenu.handleEvent(ev, window, screenID, background);
            break;
        case 3:
            break;
        case 4:
            StaticMenu.handleEvent(ev, window, screenID, featureBack);
            break;
        case 5:
            DynamicMenu.handleEvent(ev, window, screenID, featureBack);
            break;
        case 6:
            SinglyMenu.handleEvent(ev, window, screenID, featureBack);
            break;
        case 7:
            DoublyMenu.handleEvent(ev, window, screenID, featureBack);
            break;
        case 8:
            break;
        case 9:
            StackMenu.handleEvent(ev, window, screenID, featureBack);
            break;
        case 10:
            queueMenu.handleEvent(ev, window, screenID, featureBack);
            break;
        default:
            dataMenu.handleEvent(ev, window, screenID, background);
            break;
        }
        //window.draw(background);
        window.display();
    }
}
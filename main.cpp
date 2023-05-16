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
#include "CLL.hpp"

SLL *SinglyMenu;
Stack *StackMenu;
Queue *queueMenu;
DLL *DoublyMenu;
StaticArray *StaticMenu;
DynamicArray *DynamicMenu;
CLL *CircularMenu;

sf::Texture texture;
sf::Sprite background;

sf::Texture featureTexture;
sf::Sprite featureBack;

sf::Font consolas;
sf::Vector2f featureButtonSize;
sf::Color textColor(87, 113, 138);

void menuInitialize(Menu &menu, sf::Font &font)
{
    sf::Vector2f menuButtonSize(500.f, 120.f);
    sf::Color textColor(87, 113, 138);
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

    if (oldID == newID)
        return;

    if (oldID == 4)
    {
        delete StaticMenu;
        StaticMenu = nullptr;
    }
    else if (oldID == 5)
    {
        delete DynamicMenu;
        DynamicMenu = nullptr;
    }
    else if (oldID == 6)
    {
        delete SinglyMenu;
        SinglyMenu = nullptr;
    }
    else if (oldID == 7)
    {
        delete DoublyMenu;
        DoublyMenu = nullptr;
    }
    else if (oldID == 8)
    {
        delete CircularMenu;
        CircularMenu = nullptr;
    }
    else if (oldID == 9)
    {
        delete StackMenu;
        StackMenu = nullptr;
    }
    else if (oldID == 10)
    {
        delete queueMenu;
        queueMenu = nullptr;
    }

    if (newID == 4)
        StaticMenu = new StaticArray(textColor, consolas, featureButtonSize, sf::Color::White);
    else if (newID == 5)
        DynamicMenu = new DynamicArray(textColor, consolas, featureButtonSize, sf::Color::White);
    else if (newID == 6)
        SinglyMenu = new SLL(textColor, consolas, featureButtonSize, sf::Color::White);
    else if (newID == 7)
        DoublyMenu = new DLL(textColor, consolas, featureButtonSize, sf::Color::White);
    else if (newID == 8)
        CircularMenu = new CLL(textColor, consolas, featureButtonSize, sf::Color::White);
    else if (newID == 9)
        StackMenu = new Stack(textColor, consolas, featureButtonSize, sf::Color::White);
    else if (newID == 10)
        queueMenu = new Queue(textColor, consolas, featureButtonSize, sf::Color::White);
}


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Visualize algo", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    sf::VertexArray lines(sf::Lines, 3);

    consolas.loadFromFile("Font/NotoSerifHebrew_Condensed-Black.ttf");

    // Main menu setup
    Menu menu;
    menuInitialize(menu, consolas);
    window.clear(sf::Color::White);
    int screenID = 2;

    // database Menu setup
    sf::Vector2f menuButtonSize(460.f, 110.f);
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
    featureButtonSize = {100, 50};
    // SinglyMenu = new SLL(textColor, consolas, featureButtonSize, sf::Color::White);

    // // Stack menu setup
    // StackMenu = new Stack(textColor, consolas, featureButtonSize, sf::Color::White);

    // // Queue menu setup
    // queueMenu = new Queue(textColor, consolas, featureButtonSize, sf::Color::White);

    // // DLL menu setup
    // DoublyMenu = new DLL(textColor, consolas, featureButtonSize, sf::Color::White);

    // // Static Array menu setup
    // StaticMenu = new StaticArray(textColor, consolas, featureButtonSize, sf::Color::White);

    // // Dynamic Array menu setup
    // DynamicMenu = new DynamicArray(textColor, consolas, featureButtonSize, sf::Color::White);

    // // CLL menu setup
    // CircularMenu = new CLL(textColor, consolas, featureButtonSize, sf::Color::White);

    // background image

    texture.loadFromFile("Image/background.png");
    background.setTexture(texture);

    featureTexture.loadFromFile("Image/FeatureBackground.png");
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
            changeScreen(1, screenID);
            break;
        case 2:
            dataMenu.handleEvent(ev, window, screenID, background);
            changeScreen(2, screenID);
            break;
        case 3:
            break;
        case 4:
            StaticMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(4, screenID);

            break;
        case 5:
            DynamicMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(5, screenID);

            break;
        case 6:
            SinglyMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(6, screenID);

            break;
        case 7:
            DoublyMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(7, screenID);

            break;
        case 8:
            CircularMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(8, screenID);

            break;
        case 9:
            StackMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(9, screenID);

            break;
        case 10:
            queueMenu->handleEvent(ev, window, screenID, featureBack);
            changeScreen(10, screenID);
            break;
        default:
            break;
        }
        // window.draw(background);
        window.display();
    }
    changeScreen(screenID, -1);
}
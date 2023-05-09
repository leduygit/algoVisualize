#ifndef _StaticArray_H_
#define _StaticArray_H
#include "ArrowLine.hpp"
#include "Button.hpp"
#include "ArrNode.hpp"
#include "string.h"
#include "Textbox.hpp"
#include "Image.hpp"
#include "Highlight.hpp"
#include "Global.hpp"
#include <math.h>
#include <chrono>
#include <thread>
#include <fstream>

#define arrMaxSize 20
class StaticArray
{
private:
    Button create, search, insert, remove, access, backButton;
    sf::RectangleShape buttonBox;

    bool drawSubCreate;
    Button subCreateButton[4];

    bool drawSubAcess;
    Button subAccessButton[2];
    

    // smaller than 10
    const int SASize = arrMaxSize;
    int usedSize = 0;
    ArrNode nodes[arrMaxSize];
    ArrowShape arrow[arrMaxSize];

    int nodeDis;
    sf::Vector2f nodesPos[arrMaxSize];
    int nodeVal[arrMaxSize];

    int searchValue;

    bool isInputVal, isInputPos;
    int currInputBox, inputVal, inputPos;
    Textbox inputBox[8];

    // notification text
    sf::Text noti;
    bool isNoti = 0;
    Image notiFrog;

    // code hightlight image
    Highlight searchCode;
    Highlight addHeadCode;
    Highlight addTailCode;
    Highlight addPosCode;
    Highlight delHeadCode;
    Highlight delPosCode;
    Highlight updatePosCode;

    // title text
    sf::Text title;
    sf::Text inputTitle;
    sf::Text index;
public:
    StaticArray(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    bool checkHover(sf::Event &ev, sf::RenderWindow &window);
    void mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);

    // create function
    void randomArray();
    void inputFromFile(sf::RenderWindow &window, sf::Sprite &background);

    // input function
    void handleInput(sf::RenderWindow &window, sf::Sprite &background);
    void handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background);
    void handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);


    // animation function
    void searchAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addPosAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void delPosAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void updatePosAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void accessPosAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void peekPosAnimation(sf::RenderWindow &window, sf::Sprite &background);

    void addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addTailAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void delHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);
    
    // draw function
    void mainDraw(sf::RenderWindow &window, sf::Sprite &background);
    void drawNotification(sf::RenderWindow &window, sf::Sprite &background);
    void drawWithHighlight(Highlight feature, int highlightLine, sf::RenderWindow &window, sf::Sprite &background);
};
#endif
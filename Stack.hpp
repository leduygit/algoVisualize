#ifndef _Stack_H_
#define _Stack_H_
#include "ArrowLine.hpp"
#include "Button.hpp"
#include "LLNode.hpp"
#include "string.h"
#include "Textbox.hpp"
#include "Image.hpp"
#include "Highlight.hpp"
#include "Global.hpp"
#include <math.h>
#include <chrono>
#include <thread>
#include <fstream>

#define sleepFor(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

class Stack
{
public:
    Stack(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    bool checkHover(sf::Event &ev, sf::RenderWindow &window);
    void mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);
    void drawArrow(sf::RenderWindow &window, int i, int j);

    // create function
    void randomStack();
    void randomSortedStack();
    void inputFromFile(sf::RenderWindow &window, sf::Sprite &background);

    // input function
    void handleInput(sf::RenderWindow &window, sf::Sprite &background);
    void handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background);
    void handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);

    // draw function
    void mainDraw(sf::RenderWindow &window, sf::Sprite &background);
    void drawNotification(sf::RenderWindow &window, sf::Sprite &background);
    void drawWithHighlight(Highlight feature, int highlightLine, int posNotDrawingArrow, int headPos, int tailPos, sf::RenderWindow &window, sf::Sprite &background);
    void drawingHeadTailText(sf::RenderWindow &window, int posHead, int posTail);

    // animation function
    void addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void delHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);

    // pause function
    void pause_for(int pauseTime);


private:
    Button create, insert, remove, backButton;
    sf::RectangleShape buttonBox;

    bool drawSubCreate;
    Button subCreateButton[4];

    bool drawSubInsert;
    Button subInsertButton[3];

    bool drawSubRemove;
    Button subRemoveButton[3];
    

    // smaller than 10
    int StackSize = 0;
    LLNode nodes[11];
    ArrowShape arrow[11];

    int nodeDis;
    sf::Vector2f nodesPos[11];
    int nodeVal[11];

    int searchValue;

    bool isInputVal, isInputPos;
    int currInputBox, inputVal, inputPos;
    Textbox inputBox[8];

    // head/tail text
    sf::Text headText, tailText;

    // notification text
    sf::Text noti;
    bool isNoti = 0;
    Image notiFrog;

    // code hightlight image
    Highlight addHeadCode;
    Highlight delHeadCode;

    // title text
    sf::Text title;
    sf::Text inputTitle;
};
#endif
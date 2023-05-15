#ifndef _CLL_H_
#define _CLL_H_
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

class CLL
{
public:
    CLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    bool checkHover(sf::Event &ev, sf::RenderWindow &window);
    void mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);
    void drawArrow(sf::RenderWindow &window, int i, int j);

    // create function
    void randomCLL();
    void randomSortedCLL();
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
    void drawCircularArrow(sf::RenderWindow &window, int posHead, int posTail);

    // animation function
    void searchAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addTailAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addPosAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void delHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void delPosAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void updatePosAnimation(sf::RenderWindow &window, sf::Sprite &background);


private:
    Button create, search, insert, remove, update, backButton;
    sf::RectangleShape buttonBox;

    bool drawSubCreate;
    Button subCreateButton[4];
    
    bool drawSubSearch;
    Button subSearchButton[1];


    bool drawSubInsert;
    Button subInsertButton[3];

    bool drawSubRemove;
    Button subRemoveButton[3];
    

    // smaller than 10
    int CLLSize = 0;
    int tailID, headID;
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
};
#endif
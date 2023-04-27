#ifndef _SLL_H_
#define _SLL_H_
#include "ArrowLine.hpp"
#include "Button.hpp"
#include "LLNode.hpp"
#include "string.h"
#include "Textbox.hpp"
#include "Image.hpp"
#include "Highlight.hpp"
#include <math.h>

class SLL
{
public:
    SLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    bool checkHover(sf::Event &ev, sf::RenderWindow &window);
    void mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID);
    void drawArrow(sf::RenderWindow &window, int i, int j);

    // create function
    void randomSLL();
    void randomSortedSLL();

    // insert function
    void addSLL(int pos);

    // delete function
    void delSLL(int pos);

    // search function
    void SLLclearSearching();

    // input function
    void handleInput(sf::RenderWindow &window, sf::Sprite &background);
    void handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background);
    void handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background);

    // draw function
    void mainDraw(sf::RenderWindow &window, sf::Sprite &background);

    // notification function
    void drawNotification(sf::RenderWindow &window, sf::Sprite &background);

    // animation function
    void searchAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addTailAnimation(sf::RenderWindow &window, sf::Sprite &background);
    void addPosAnimation(sf::RenderWindow &window, sf::Sprite &background);

    // drawing head/tail text
    void drawingHeadTailText(sf::RenderWindow &window, int posHead, int posTail);


private:
    Button create, search, insert, remove, backButton;
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
    int SLLSize = 0;
    LLNode nodes[11];
    ArrowShape arrow[11];

    int nodeDis;
    sf::Vector2f nodesPos[11];
    int nodeVal[11];

    bool isDeleting[11];
    bool SLLisSearching = 0, doneSearching = 0, nodeSearch[11];
    int searchValue;
    
    int frameDelay = 0;

    bool isInputVal, isInputPos;
    int currInputBox, inputVal, inputPos;
    Textbox inputBox[8];

    float delayTime;

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
};
#endif
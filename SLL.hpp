#ifndef _SLL_H_
#define _SLL_H_
#include "ArrowLine.hpp"
#include "Button.hpp"
#include "LLNode.hpp"
#include "string.h"
#include "Textbox.hpp"
#include <math.h>

class SLL
{
public:
    SLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor);
    void handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID);
    bool checkHover(sf::Event &ev, sf::RenderWindow &window);
    void mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID);
    void drawArrow(sf::RenderWindow &window);

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
    void handleInput();
    void handleFeature(int pos);

private:
    Button create, search, insert, remove, backButton;

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
};
#endif
#ifndef _SLL_H_
#define _SLL_H_
#include "ArrowLine.hpp"
#include "Button.hpp"
#include "LLNode.hpp"

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
private:
    Button create, search, insert, remove;

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
    float nodesPos[11];
};
#endif
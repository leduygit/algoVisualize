#include "SLL.hpp"
#include "string.h"

SLL::SLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    create = Button("Create", textColor, font, buttonSize, backgroundColor);
    search = Button("Search", textColor, font, buttonSize, backgroundColor);
    insert = Button("Insert", textColor, font, buttonSize, backgroundColor);
    remove = Button("Remove", textColor, font, buttonSize, backgroundColor);

    sf::Vector2f position = {100, 550};
    create.setPosition(position);
    search.setPosition({position.x, position.y + buttonSize.y + 20});
    insert.setPosition({position.x, position.y + 2 * buttonSize.y + 40});
    remove.setPosition({position.x, position.y + 3 * buttonSize.y + 60});

    std::string subCreateName[] = {"Empty", "Random", "Sorted", "Fixed size"};

    sf::Vector2f subSize = {150, 50};
    sf::Vector2f subCreatePos = {position.x + buttonSize.x + 20, position.y};
    for (int i = 0; i < 4; ++i)
    {
        subCreateButton[i] = Button(subCreateName[i], textColor, font, subSize, backgroundColor);
        subCreateButton[i].setPosition(subCreatePos);
        subCreatePos.x += 170;
    }

    std::string subSearchName[] = {"Value"};
    sf::Vector2f subSearchPos = {position.x + buttonSize.x + 20, position.y + buttonSize.y + 20};
    for (int i = 0; i < 1; ++i)
    {
        subSearchButton[i] = Button(subSearchName[i], textColor, font, subSize, backgroundColor);
        subSearchButton[i].setPosition(subSearchPos);
        subSearchPos.x += 170;
    }

    std::string subInsertName[] = {"Head", "Tail", "Position"};
    sf::Vector2f subInsertPos = {position.x + buttonSize.x + 20, position.y + 2 * buttonSize.y + 40};
    for (int i = 0; i < 3; ++i)
    {
        subInsertButton[i] = Button(subInsertName[i], textColor, font, subSize, backgroundColor);
        subInsertButton[i].setPosition(subInsertPos);
        subInsertPos.x += 170;
    }

    std::string subRemoveName[] = {"Head", "Tail", "Position"};
    sf::Vector2f subRemovePos = {position.x + buttonSize.x + 20, position.y + 3 * buttonSize.y + 60};
    for (int i = 0; i < 3; ++i)
    {
        subRemoveButton[i] = Button(subRemoveName[i], textColor, font, subSize, backgroundColor);
        subRemoveButton[i].setPosition(subRemovePos);
        subRemovePos.x += 170;
    }
}

void SLL::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID)
{
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case (sf::Event::Closed):
            window.close();
            break;
        case (sf::Event::MouseMoved):
            checkHover(ev, window);
            break;
        case (sf::Event::MouseButtonPressed):
            if (ev.mouseButton.button == sf::Mouse::Left)
                mouseClicked(ev, window, screenID);
            break;
        default:
            break;
        }
    }

    window.clear(sf::Color::White);
    create.drawButton(window);
    search.drawButton(window);
    insert.drawButton(window);
    remove.drawButton(window);

    if (drawSubCreate)
        for (int i = 0; i < 4; ++i)
            subCreateButton[i].drawButton(window);

    if (drawSubSearch)
        for (int i = 0; i < 1; ++i)
            subSearchButton[i].drawButton(window);

    if (drawSubInsert)
        for (int i = 0; i < 3; ++i)
            subInsertButton[i].drawButton(window);

    if (drawSubRemove)
        for (int i = 0; i < 3; ++i)
            subRemoveButton[i].drawButton(window);
}

bool SLL::checkHover(sf::Event &ev, sf::RenderWindow &window)
{
    if (create.hoverChangeColor(ev, window))
        return true;
    if (search.hoverChangeColor(ev, window))
        return true;
    if (insert.hoverChangeColor(ev, window))
        return true;
    if (remove.hoverChangeColor(ev, window))
        return true;

    if (drawSubCreate)
        for (int i = 0; i < 4; ++i)
            if (subCreateButton[i].hoverChangeColor(ev, window))
                return true;

    if (drawSubSearch)
        for (int i = 0; i < 1; ++i)
            if (subSearchButton[i].hoverChangeColor(ev, window))
                return true;

    if (drawSubInsert)
        for (int i = 0; i < 3; ++i)
            if (subInsertButton[i].hoverChangeColor(ev, window))
                return true;

    if (drawSubRemove)
        for (int i = 0; i < 3; ++i)
            if (subInsertButton[i].hoverChangeColor(ev, window))
                return true;

    return false;
}

void SLL::mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID)
{
    // if (ev.type != sf::Event::MouseButtonReleased) return;
    if (create.isMouseOnButton(window))
    {
        drawSubCreate = !drawSubCreate;
        drawSubInsert = drawSubRemove = drawSubSearch = 0;
    }
    else if (search.isMouseOnButton(window))
    {
        drawSubSearch = !drawSubSearch;
        drawSubCreate = drawSubInsert = drawSubRemove = 0;
    }
    else if (insert.isMouseOnButton(window))
    {
        drawSubInsert = !drawSubInsert;
        drawSubCreate = drawSubSearch = drawSubRemove = 0;
    }
    else if (remove.isMouseOnButton(window))
    {
        drawSubRemove = !drawSubRemove;
        drawSubCreate = drawSubInsert = drawSubSearch = 0;
    }
}

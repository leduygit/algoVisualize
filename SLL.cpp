#include "SLL.hpp"
#include "string.h"

int randInt(int l, int r)
{
    if (l > r)
        return r;
    return l + rand() % (r - l + 1);
}

SLL::SLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    create = Button("Create", textColor, font, buttonSize, backgroundColor);
    search = Button("Search", textColor, font, buttonSize, backgroundColor);
    insert = Button("Insert", textColor, font, buttonSize, backgroundColor);
    remove = Button("Remove", textColor, font, buttonSize, backgroundColor);
    backButton = Button("Return", textColor, font, {180, 60}, backgroundColor);

    sf::Vector2f position = {100, 550};
    create.setPosition(position);
    search.setPosition({position.x, position.y + buttonSize.y + 20});
    insert.setPosition({position.x, position.y + 2 * buttonSize.y + 40});
    remove.setPosition({position.x, position.y + 3 * buttonSize.y + 60});
    backButton.setPosition({30, 40});

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

    nodeDis = 150;
    sf::Vector2f nodePos = {50, 170};
    for (int i = 0; i < 11; ++i)
    {
        nodes[i] = LLNode("1", textColor, font, 30.f, backgroundColor);
        nodes[i].setPosition(nodePos);
        nodePos.x += nodeDis;
        // (width, height, tipWidth, tipHeight), in this case the arrow is horizontal
        arrow[i] = ArrowShape(70, 8, 15, 15);
        arrow[i].setColor(sf::Color::Black);
    }
}

void SLL::drawArrow(sf::RenderWindow &window)
{
    for (int i = SLLSize; i > 0; --i)
    {
        sf::Vector2f center1 = nodes[i].getCenter();
        sf::Vector2f center2 = nodes[i - 1].getCenter();
        // radius = 30, outline = 4.f
        sf::Vector2f position = {center2.x + 35.f, center2.y - (30.f - (30.f - 4.f))};
        arrow[i].setPosition(position);
    }

    // window.draw(arrow[5]);
    for (int i = SLLSize - 1; i > 0; --i)
        window.draw(arrow[i]);
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
    backButton.drawButton(window);
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

    for (int i = 0; i < SLLSize; ++i)
        nodes[i].draw(window);
    drawArrow(window);
}

bool SLL::checkHover(sf::Event &ev, sf::RenderWindow &window)
{
    if (backButton.hoverChangeColor(ev, window))
        return true;
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
            if (subRemoveButton[i].hoverChangeColor(ev, window))
                return true;

    return false;
}

void SLL::mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID)
{
    // if (ev.type != sf::Event::MouseButtonReleased) return;
    if (backButton.isMouseOnButton(window))
    {
        SLLSize = 0;
        screenID = 3;
        return;
    }
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

    if (drawSubCreate)
    {
        if (subCreateButton[0].isMouseOnButton(window))
            SLLSize = 0;
        else if (subCreateButton[1].isMouseOnButton(window))
            randomSLL();
        else if (subCreateButton[2].isMouseOnButton(window))
            randomSortedSLL();
    }

    if (drawSubInsert)
    {
        if (subInsertButton[0].isMouseOnButton(window))
            addSLL(0);
        else if (subInsertButton[2].isMouseOnButton(window))
            addSLL(randInt(0, SLLSize - 1));
        else if (subInsertButton[1].isMouseOnButton(window))
            addSLL(SLLSize);
    }

    if (drawSubRemove)
    {
        if (subRemoveButton[0].isMouseOnButton(window))
            delSLL(0);
        else if (subRemoveButton[2].isMouseOnButton(window))
            delSLL(randInt(0, SLLSize - 1));
        else if (subRemoveButton[1].isMouseOnButton(window))
            delSLL(SLLSize - 1);
    }
}

std::string toString(int x)
{
    std::string num = "";
    while (x)
    {
        num += ('0' + x % 10);
        x /= 10;
    }
    reverse(num.begin(), num.end());
    return num;
}

void SLL::randomSLL()
{
    SLLSize = randInt(1, 10);
    for (int i = 0; i < SLLSize; ++i)
        nodes[i].setString(toString(randInt(1, 10)));
}

void SLL::randomSortedSLL()
{
    SLLSize = randInt(1, 10);
    int x = 1;
    for (int i = 0; i < SLLSize; ++i)
    {
        x = randInt(x, 999);
        nodes[i].setString(toString(x));
    }
}

void SLL::addSLL(int pos)
{
    if (pos > SLLSize || pos < 0)
        return;
    if (SLLSize >= 10)
        return;
    for (int i = SLLSize + 1; i > pos; --i)
    {
        nodes[i].setString(nodes[i - 1].getString());
    }
    nodes[pos].setString(toString(randInt(1, 999)));
    ++SLLSize;
}

void SLL::delSLL(int pos)
{
    if (pos > SLLSize - 1 || pos < 0)
        return;
    if (SLLSize <= 0)
        return;

    for (int i = pos; i < SLLSize; ++i)
        nodes[i].setString(nodes[i + 1].getString());
    --SLLSize;
}

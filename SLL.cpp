#include "SLL.hpp"

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
    sf::Vector2f curNodePosition = {50, 170};
    for (int i = 0; i < 11; ++i)
    {
        nodes[i] = LLNode("1", textColor, font, 30.f, backgroundColor);
        nodes[i].setPosition(curNodePosition);
        nodesPos[i] = curNodePosition;
        curNodePosition.x += nodeDis;
        // (width, height, tipWidth, tipHeight), in this case the arrow is horizontal
        arrow[i] = ArrowShape(70, 8, 15, 15);
        arrow[i].setColor(sf::Color::Black);
        isDeleting[i] = 0;
    }

    for (int i = 0; i < 8; ++i)
    {
        inputBox[i] = Textbox(20, sf::Color::Black, 1);
        inputBox[i].setFont(font);
    }

    inputBox[0].setPosition({subCreateButton[3].getPos().x + 60, position.y + buttonSize.y + 20});
    inputBox[1].setPosition({subSearchButton[0].getPos().x + 60, position.y + 2 * buttonSize.y + 40});

    delayTime = 0.f;
}

void SLL::drawArrow(sf::RenderWindow &window)
{
    for (int i = SLLSize; i > 0; --i)
    {
        sf::Vector2f center1 = nodes[i].getCenter();
        sf::Vector2f center2 = nodes[i - 1].getCenter();
        // radius = 30, outline = 4.f
        float angle;
        if (center1.x == center2.x)
            angle = 0;
        else
        {
            float slope = (center1.y - center2.y) / (center1.x - center2.x);
            angle = atan(slope);
        }
        float radius = 32.f;
        float d = 4;
        sf::Vector2f position = {center2.x + radius * cos(angle) + d * sin(angle), center2.y + radius * sin(angle) - d * cos(angle)};

        float arrowWidth = sqrt((center1.x - center2.x) * (center1.x - center2.x) + (center1.y - center2.y) * (center1.y - center2.y));
        arrowWidth -= 2 * radius;
        arrow[i] = ArrowShape(arrowWidth * 0.82, 2 * d, arrowWidth * 0.18, 20);
        arrow[i].setColor(sf::Color::Black);
        // std::cout << radius * cos(angle) - d * sin(angle) << ' ' << radius * sin(angle) + d * cos(angle) << '\n';
        // std::cout << cos(angle) << ' ' << sin(angle) << '\n';
        arrow[i].setPosition(position);
        arrow[i].setRotation(angle * 180 / 3.14);
    }

    // window.draw(arrow[5]);
    for (int i = SLLSize - 1; i > 0; --i)
        window.draw(arrow[i]);
}

int stringToInt(std::string t)
{
    int x = 0;
    for (char c : t) x = x * 10 + (c - '0');
    return x;
}


void SLL::handleFeature(int pos)
{
    // 0 = create fixed size 
    // 1 = search value
    // 2 = insert head
    // 3 = insert tail
    // 4 = insert custom position
    // 5 = remove head
    // 6 = remove tail
    // 7 = remove custom position
    if (pos == 1)
    {
        searchValue = inputVal;
        SLLisSearching = 1;
    }  
}


void SLL::handleInput()
{
    if (isInputPos)
    {
        isInputPos = 0;
        isInputVal = 1;
        inputPos = stringToInt(inputBox[currInputBox].getText());
        inputBox[currInputBox].setText("");
    }
    else
    {
        isInputVal = 0;
        inputVal = stringToInt(inputBox[currInputBox].getText());
        inputBox[currInputBox].setText("");
        handleFeature(currInputBox);
    }
}

void SLL::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID)
{
    sf::Clock clock;
    //textbox testing

    float currTime = 0.f;

    if (isInputPos || isInputVal)
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
                mouseClicked(ev, window, screenID);
                inputPos = inputVal = 0;
                break;
            case (sf::Event::TextEntered):
                if (inputBox[currInputBox].typedOn(ev))
                    handleInput();
                break;
            
            default:
                break;
            }
        }
    }
    else
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
        case (sf::Event::KeyPressed):
            break;
        default:
            break;
        }
    }

    // if (SLLSize != 0)
    // {
    //     int i = randInt(0, SLLSize);
    //     nodes[i].setPosition({nodesPos[i].x, 300});
    // }

    window.clear(sf::Color::White);
    backButton.drawButton(window);
    create.drawButton(window);
    search.drawButton(window);
    insert.drawButton(window);
    remove.drawButton(window);
    if (isInputPos || isInputVal) inputBox[currInputBox].drawTo(window);

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

    bool colorNewNode = 0;
    std::cout << doneSearching << '\n';
    if (doneSearching) SLLclearSearching();
    for (int i = 0; i < SLLSize; ++i)
    {
        if (SLLisSearching && !colorNewNode && !nodeSearch[i])
        {
            colorNewNode = 1;
            nodeSearch[i] = 1;
            if (nodeVal[i] == searchValue){
                nodes[i].setBackgroundColor(sf::Color::Red);
                SLLisSearching = 0;
                doneSearching = 1;
                frameDelay = 2;
            }
            else{
                nodes[i].setBackgroundColor(sf::Color::Green);
                if (i == SLLSize - 1 && SLLisSearching)
                {
                    doneSearching = 1;
                    frameDelay = 2;
                }
            }
        }
        if (isDeleting[i])
        {
            nodes[i].setRadius(nodes[i].getRadius() - 2.f);
            nodes[i].draw(window);
            if (nodes[i].getRadius() == 0)
            {
                isDeleting[i] = 0;
                nodes[i].setRadius(30.f);
                delSLL(i);
            }
            continue;
        }
        nodes[i].draw(window);
        sf::Vector2f curPos = nodes[i].getPosition();
        if (curPos.y > nodesPos[i].y)
            nodes[i].setPosition({curPos.x, curPos.y - 5});
        else if (curPos.x > nodesPos[i].x)
            nodes[i].setPosition({curPos.x - 5, curPos.y});
        else if (curPos.x < nodesPos[i].x)
            nodes[i].setPosition({curPos.x + 5, curPos.y});
    }
    drawArrow(window);
    if (SLLisSearching) _sleep(500);
    else if (frameDelay > 0)
    {
        _sleep(500);
        --frameDelay;
    }
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
        {
            if (SLLSize > 0)
            {
                isDeleting[0] = 1;
                delSLL(0);
            }
        }
        else if (subRemoveButton[2].isMouseOnButton(window))
        {
            int pos = randInt(0, SLLSize - 1);
            isDeleting[pos] = 1;
            delSLL(pos);
        }
        else if (subRemoveButton[1].isMouseOnButton(window))
        {
            isDeleting[SLLSize - 1] = 1;
            delSLL(SLLSize - 1);
        }
    }

    if (drawSubSearch)
    {
        if (subSearchButton[0].isMouseOnButton(window))
        {
            isInputVal = 1;
            currInputBox = 1;
            inputBox[1].setSelected(1);
            doneSearching = 0;
            for (int i = 0; i < SLLSize; ++i)
                nodeSearch[i] = 0;
        }
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
    {
        nodes[i].setPosition(nodesPos[i]);
        int x = randInt(1, 100);
        nodeVal[i] = x;
        nodes[i].setString(toString(x));
    }
}

void SLL::randomSortedSLL()
{
    SLLSize = randInt(1, 10);
    int x = 1;
    for (int i = 0; i < SLLSize; ++i)
    {
        x = randInt(x, 100);
        nodeVal[i] = x;
        nodes[i].setString(toString(x));
        nodes[i].setPosition(nodesPos[i]);
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
        nodes[i].setPosition(nodesPos[i - 1]);
    }

    ++SLLSize;
    // for (int i = 0; i < pos; ++i) nodes[i].setPosition(nodesPos[i - 1]);
    int val = randInt(1, 999);
    nodeVal[pos] = val;
    nodes[pos].setString(toString(val));
    nodes[pos].setPosition({nodesPos[pos].x, 300});
}

void SLL::delSLL(int pos)
{
    if (pos > SLLSize - 1 || pos < 0)
        return;
    if (SLLSize <= 0)
        return;
    if (isDeleting[pos])
        return;
    for (int i = pos; i < SLLSize; ++i)
    {
        nodes[i].setPosition(nodesPos[i + 1]);
        nodes[i].setString(nodes[i + 1].getString());
        nodeVal[i] = nodeVal[i + 1];
    }
    --SLLSize;
}

void SLL::SLLclearSearching()
{
    for (int i = 0; i < SLLSize; ++i){
        nodes[i].setBackgroundColor(sf::Color::White);
        nodeSearch[i] = 0;
    }
    doneSearching = 0;
    SLLisSearching = 0;
}

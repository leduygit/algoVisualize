#include "SLL.hpp"

void pause_for(int pauseTime)
{
    std::chrono::milliseconds duration = std::chrono::milliseconds(pauseTime);
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + duration;

    while (std::chrono::steady_clock::now() < end_time)
    {
        // Do other work while waiting
        std::this_thread::yield();
    }
}

int randInt(int l, int r)
{
    if (l > r)
        return r;
    return l + rand() % (r - l + 1);
}

SLL::SLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    headText.setFillColor(sf::Color::Black);
    tailText.setFillColor(sf::Color::Black);
    headText.setFont(font);
    tailText.setFont(font);
    headText.setString("Head");
    tailText.setString("Tail");
    tailText.setCharacterSize(20);
    headText.setCharacterSize(20);

    noti.setFillColor(sf::Color::Black);
    noti.setFont(font);
    noti.setPosition({580, 420});
    noti.setString("testing");
    noti.setCharacterSize(60);

    notiFrog.loadTexture("Image/notifrog.png");
    notiFrog.setPosition({400, 350});
    searchCode.loadTexture("Image/SLLsearchCode.png");
    searchCode.setPosition({911, 577});
    addHeadCode.loadTexture("Image/SLLaddHeadCode.png");
    addHeadCode.setPosition({911, 666});
    addTailCode.loadTexture("Image/SLLaddTailCode.png");
    addTailCode.setPosition({911, 666});
    addPosCode.loadTexture("Image/SLLaddPosCode.png");
    addPosCode.setPosition({911, 600});
    delHeadCode.loadTexture("Image/SLLdelHeadCode.png");
    delHeadCode.setPosition({911, 643});
    delPosCode.loadTexture("Image/SLLdelPosCode.png");
    delPosCode.setPosition({911, 554});
    updatePosCode.loadTexture("Image/SLLupdatePosCode.png");
    updatePosCode.setPosition({911, 621});


    create = Button("Create", textColor, font, buttonSize, backgroundColor);
    search = Button("Search", textColor, font, buttonSize, backgroundColor);
    insert = Button("Insert", textColor, font, buttonSize, backgroundColor);
    remove = Button("Remove", textColor, font, buttonSize, backgroundColor);
    update = Button("Update", textColor, font, buttonSize, backgroundColor);
    backButton = Button("Return", textColor, font, {100, 50}, backgroundColor);
    backButton.setOutlineThickness(4);

    sf::Vector2f position = {100, 520};
    buttonBox.setOutlineColor(sf::Color::Black);
    buttonBox.setOutlineThickness(4.f);
    buttonBox.setPosition(position);
    buttonBox.setSize({buttonSize.x, 5 * buttonSize.y});

    create.setPosition(position);
    search.setPosition({position.x, position.y + buttonSize.y});
    insert.setPosition({position.x, position.y + 2 * buttonSize.y});
    remove.setPosition({position.x, position.y + 3 * buttonSize.y});
    update.setPosition({position.x, position.y + 4 * buttonSize.y});
    backButton.setPosition({40, 38});

    std::string subCreateName[] = {"Empty", "Random", "Sorted", "Fixed size"};

    sf::Vector2f subSize = {150, 50};
    sf::Vector2f subCreatePos = {position.x + buttonSize.x + 20, position.y};
    for (int i = 0; i < 4; ++i)
    {
        subCreateButton[i] = Button(subCreateName[i], textColor, font, subSize, backgroundColor);
        subCreateButton[i].setPosition(subCreatePos);
        subCreateButton[i].setOutlineThickness(3);
        subCreatePos.x += 170;
    }

    std::string subSearchName[] = {"Value"};
    sf::Vector2f subSearchPos = {position.x + buttonSize.x + 20, position.y + buttonSize.y};
    for (int i = 0; i < 1; ++i)
    {
        subSearchButton[i] = Button(subSearchName[i], textColor, font, subSize, backgroundColor);
        subSearchButton[i].setPosition(subSearchPos);
        subSearchButton[i].setOutlineThickness(3);
        subSearchPos.x += 170;
    }

    std::string subInsertName[] = {"Head", "Tail", "Position"};
    sf::Vector2f subInsertPos = {position.x + buttonSize.x + 20, position.y + 2 * buttonSize.y};
    for (int i = 0; i < 3; ++i)
    {
        subInsertButton[i] = Button(subInsertName[i], textColor, font, subSize, backgroundColor);
        subInsertButton[i].setPosition(subInsertPos);
        subInsertButton[i].setOutlineThickness(3);
        subInsertPos.x += 170;
    }

    std::string subRemoveName[] = {"Head", "Tail", "Position"};
    sf::Vector2f subRemovePos = {position.x + buttonSize.x + 20, position.y + 3 * buttonSize.y};
    for (int i = 0; i < 3; ++i)
    {
        subRemoveButton[i] = Button(subRemoveName[i], textColor, font, subSize, backgroundColor);
        subRemoveButton[i].setPosition(subRemovePos);
        subRemoveButton[i].setOutlineThickness(3);
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

    // create input box
    inputBox[0].setPosition({subCreateButton[3].getPos().x + 60, position.y + buttonSize.y + 5});

    // search input box
    inputBox[1].setPosition({subSearchButton[0].getPos().x + 60, position.y + 2 * buttonSize.y + 5});

    // insert input box
    inputBox[2].setPosition({subInsertButton[0].getPos().x + 60, position.y + 3 * buttonSize.y + 5});
    inputBox[3].setPosition({subInsertButton[1].getPos().x + 60, position.y + 3 * buttonSize.y + 5});
    inputBox[4].setPosition({subInsertButton[2].getPos().x + 60, position.y + 3 * buttonSize.y + 5});

    // remove input box
    inputBox[5].setPosition({subInsertButton[2].getPos().x + 60, position.y + 4 * buttonSize.y + 5});

    // update input box
    inputBox[6].setPosition({update.getPos().x + 160, position.y + 4 * buttonSize.y + 15});
    delayTime = 0.f;
}

void SLL::drawArrow(sf::RenderWindow &window, int i, int j)
{
    // assume that i < j
    sf::Vector2f center1 = nodes[i].getCenter();
    sf::Vector2f center2 = nodes[j].getCenter();
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

    // window.draw(arrow[5]);
    window.draw(arrow[i]);
}

int stringToInt(std::string t)
{
    int x = 0;
    for (char c : t)
        x = x * 10 + (c - '0');
    return x;
}

void SLL::handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background)
{
    // 0 = create fixed size
    // 1 = search value
    // 2 = insert head
    // 3 = insert tail
    // 4 = insert custom position
    // 5 = remove custom position
    // 6 = update value for position
    switch (pos)
    {
    case 1:
        searchValue = inputVal;
        searchAnimation(window, background);
        break;
    case 2:
        addHeadAnimation(window, background);
        break;
    case 3:
        addTailAnimation(window, background);
        break;
    case 4:
        addPosAnimation(window, background);
        break;
    case 5:
        delPosAnimation(window, background);
        break;
    case 6:
        updatePosAnimation(window, background);
        break;
    default:
        break;
    }
}

void SLL::handleInput(sf::RenderWindow &window, sf::Sprite &background)
{
    if (isInputPos)
    {
        isInputPos = 0;
        inputPos = stringToInt(inputBox[currInputBox].getText());
        inputBox[currInputBox].setText("");
        if (currInputBox == 5)
        {
            handleFeature(currInputBox, window, background);
            return;
        }
        isInputVal = 1;
    }
    else
    {
        isInputVal = 0;
        inputVal = stringToInt(inputBox[currInputBox].getText());
        inputBox[currInputBox].setText("");
        handleFeature(currInputBox, window, background);
    }
}

std::string toString(int x)
{
    std::string num = "";
    if (x == 0)
        num += '0';
    while (x)
    {
        num += ('0' + x % 10);
        x /= 10;
    }
    reverse(num.begin(), num.end());
    return num;
}

void SLL::searchAnimation(sf::RenderWindow &window, sf::Sprite &background)
{

    // line 1, checking null array
    mainDraw(window, background);
    searchCode.setLine(1);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    searchCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(500);

    if (SLLSize == 0)
    {
        noti.setString("Not found value " + toString(searchValue));
        mainDraw(window, background);
        for (int i = 0; i < SLLSize; ++i)
        {
            nodes[i].draw(window);
            if (i > 0)
                drawArrow(window, i, i - 1);
        }
        searchCode.draw(window);
        drawingHeadTailText(window, 0, SLLSize - 1);
        window.display();
        pause_for(500);
        drawNotification(window, background);
        return;
    }

    int foundValue = 0;
    // change nodes color and highlight animation
    for (int i = 0; i < SLLSize; ++i)
    {
        // if first frame then draw initialize frame
        if (i == 0)
        {
            nodes[i].setBackgroundColor(sf::Color::Green);
            searchCode.setLine(2);
            mainDraw(window, background);
            for (int j = 0; j < SLLSize; ++j)
            {
                nodes[j].draw(window);
                if (j > 0)
                    drawArrow(window, j, j - 1);
            }
            searchCode.draw(window);
            drawingHeadTailText(window, 0, SLLSize - 1);
            window.display();
            pause_for(500);
        }

        // first frame - while statement
        {
            searchCode.setLine(3);
            mainDraw(window, background);
            for (int j = 0; j < SLLSize; ++j)
            {
                nodes[j].draw(window);
                if (j > 0)
                    drawArrow(window, j, j - 1);
            }
            searchCode.draw(window);
            drawingHeadTailText(window, 0, SLLSize - 1);
            window.display();
            pause_for(500);
        }

        // found value
        if (nodeVal[i] == searchValue)
        {
            foundValue = i + 1;
            break;
        }

        // if last node -> not jumping to next
        if (i == SLLSize - 1)
            break;

        // second frame - jumping to next node
        {
            // set next node color
            if (i + 1 < SLLSize)
                nodes[i + 1].setBackgroundColor(sf::Color::Green);
            searchCode.setLine(4);
            mainDraw(window, background);
            for (int j = 0; j < SLLSize; ++j)
            {
                nodes[j].draw(window);
                if (j > 0)
                    drawArrow(window, j, j - 1);
            }
            searchCode.draw(window);
            drawingHeadTailText(window, 0, SLLSize - 1);

            window.display();
            pause_for(500);
        }
    }

    // last if statement
    {
        searchCode.setLine(6);
        mainDraw(window, background);
        for (int i = 0; i < SLLSize; ++i)
        {
            nodes[i].draw(window);
            if (i > 0)
                drawArrow(window, i, i - 1);
        }
        searchCode.draw(window);
        drawingHeadTailText(window, 0, SLLSize - 1);

        window.display();
        pause_for(500);
    }
    if (foundValue)
        nodes[foundValue - 1].setBackgroundColor(sf::Color::Red);

    // set notification text
    if (foundValue)
    {
        searchCode.setLine(6);
        noti.setString("Found at index " + toString(foundValue));
    }
    else
    {
        searchCode.setLine(7);
        noti.setString("Not found value " + toString(searchValue));
    }

    // return frame
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    searchCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);

    window.display();
    pause_for(500);
    drawNotification(window, background);

    for (int i = 0; i < SLLSize; ++i)
        nodes[i].setBackgroundColor(sf::Color::White);
}

void SLL::updatePosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    // line 1, checking null array
    drawWithHighlight(updatePosCode, 1, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(500);

    if (SLLSize == 0)
    {
        noti.setString("Not found value " + toString(searchValue));
        drawNotification(window, background);
        return;
    }

    if (inputPos >= SLLSize) return;

    // set cur = head;
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(updatePosCode, 2, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(500);

    // finding update pos
    for (int i = 0; i <= inputPos; ++i)
    {
        // for statement
        drawWithHighlight(updatePosCode, 3, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);

        // last node
        if (i == inputPos) break;

        // jumping to next node
        nodes[i].setBackgroundColor(sf::Color::White);
        nodes[i + 1].setBackgroundColor(sf::Color::Green);
        drawWithHighlight(updatePosCode, 4, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    // delete old data
    std::string curData = nodes[inputPos].getString();
    while (true)
    {
        drawWithHighlight(updatePosCode, 5, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);
        if (curData == "") break;
        curData.pop_back();
        nodes[inputPos].setString(curData);
    }

    // update new data
    nodeVal[inputPos] = inputVal;
    std::string newData = toString(inputVal);
    std::string tmp = "";
    for (int i = 0; i < newData.size(); ++i)
    {
        tmp += newData[i];
        nodes[inputPos].setString(tmp);
        drawWithHighlight(updatePosCode, 5, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    nodes[inputPos].setBackgroundColor(sf::Color::White);
}

void SLL::drawingHeadTailText(sf::RenderWindow &window, int posHead, int posTail)
{
    if (posHead >= SLLSize)
        return;
    if (SLLSize == 0)
        return;
    sf::Vector2f headPos = nodes[posHead].getCenter();
    headText.setPosition({headPos.x - 27, headPos.y + 35});
    sf::Vector2f tailPos = nodes[posTail].getCenter();
    tailText.setPosition({tailPos.x - 17, tailPos.y + 35});
    if (posHead == posTail)
    {
        headText.setString("Head/Tail");
        window.draw(headText);
    }
    else
    {
        headText.setString("Head");
        window.draw(headText);
        if (posTail < SLLSize)
            window.draw(tailText);
    }
}

void SLL::drawWithHighlight(Highlight feature, int highlightLine, int posNotDrawingArrow, int headPos, int tailPos, sf::RenderWindow &window, sf::Sprite &background)
{
    // posNotDrawingArrow = -1, draw all arrow
    feature.setLine(highlightLine);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0 && i != posNotDrawingArrow)
            drawArrow(window, i, i - 1);
    }
    feature.draw(window);
    drawingHeadTailText(window, headPos, tailPos);
}

void SLL::delHeadAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    // first line checking empty
    drawWithHighlight(delHeadCode, 1, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(1000);

    if (SLLSize == 0)
    {
        noti.setString("Linked list empty");
        drawNotification(window, background);
        return;
    }

    // second line setting cur = head;
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(delHeadCode, 2, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(1000);

    // third line changing head
    drawWithHighlight(delHeadCode, 3, -1, 1, SLLSize - 1, window, background);
    window.display();
    pause_for(1000);

    // last line deleting nodes
    bool isDeleteNode = true;
    while (isDeleteNode)
    {
        drawWithHighlight(delHeadCode, 4, -1, 1, SLLSize - 1, window, background);
        window.display();
        isDeleteNode = (nodes[0].getRadius() > 0);
        nodes[0].setRadius(nodes[0].getRadius() - 1);
    }

    nodes[0].setRadius(30);
    nodes[0].setBackgroundColor(sf::Color::White);
    // making changes to linkedlist
    --SLLSize;
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].setString(nodes[i + 1].getString());
        nodes[i].setPosition(nodesPos[i + 1]);
        nodeVal[i] = nodeVal[i + 1];
    }

    // moving back
    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        drawWithHighlight(delHeadCode, 4, -1, 0, SLLSize - 1, window, background);
        window.display();
        for (int i = 0; i < SLLSize; ++i)
        {
            sf::Vector2f curPos = nodes[i].getPosition();
            if (curPos != nodesPos[i])
            {
                isMoving = true;
                curPos.x -= 1;
            }
            nodes[i].setPosition(curPos);
        }
    }
}

void SLL::delPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    // checking empty
    drawWithHighlight(delPosCode, 1, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(500);

    if (SLLSize == 0)
    {
        noti.setString("Linked list empty");
        drawNotification(window, background);
        pause_for(500);
        return;
    }

    --inputPos;
    if (inputPos < 0 || inputPos >= SLLSize)
        return;

    // set cur = head
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(delPosCode, 2, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(500);

    // finding delPos
    for (int i = 0; i < inputPos; ++i)
    {
        // for statement
        drawWithHighlight(delPosCode, 3, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);

        // last node
        if (i == inputPos - 1)
            break;

        // jumping to next node
        nodes[i].setBackgroundColor(sf::Color::White);
        nodes[i + 1].setBackgroundColor(sf::Color::Green);
        drawWithHighlight(delPosCode, 4, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    // set deletion node, and the next node of it
    nodes[inputPos].setBackgroundColor(sf::Color::Red);
    if (inputPos + 1 < SLLSize)
        nodes[inputPos + 1].setBackgroundColor(sf::Color::Yellow);

    drawWithHighlight(delPosCode, 5, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(500);

    // deleting
    bool isDeleteNode = true;
    while (isDeleteNode)
    {
        drawWithHighlight(delPosCode, 6, -1, 0, SLLSize - 1, window, background);
        window.display();
        isDeleteNode = (nodes[inputPos].getRadius() > 0);
        nodes[inputPos].setRadius(nodes[inputPos].getRadius() - 1);
    }

    // making changes to array
    --SLLSize;
    nodes[inputPos].setBackgroundColor(sf::Color::Yellow);
    nodes[inputPos].setRadius(30);
    if (inputPos < 10)
        nodes[inputPos + 1].setBackgroundColor(sf::Color::White);

    for (int i = inputPos; i < SLLSize; ++i)
    {
        nodes[i].setString(nodes[i + 1].getString());
        nodes[i].setPosition(nodesPos[i + 1]);
        nodeVal[i] = nodeVal[i + 1];
    }

    // moving
    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        if (inputPos == SLLSize)
            drawWithHighlight(delPosCode, 6, inputPos, 0, SLLSize, window, background);
        else
            drawWithHighlight(delPosCode, 6, inputPos, 0, SLLSize - 1, window, background);

        window.display();
        for (int i = 0; i < SLLSize; ++i)
        {
            sf::Vector2f curPos = nodes[i].getPosition();
            if (curPos != nodesPos[i])
            {
                isMoving = true;
                curPos.x -= 1;
            }
            nodes[i].setPosition(curPos);
        }
    }
    pause_for(500);

    // linking
    if (inputPos == SLLSize)
    {
        drawWithHighlight(delPosCode, 7, -1, 0, SLLSize, window, background);
        window.display();
        pause_for(500);
    }
    else
    {
        drawWithHighlight(delPosCode, 7, -1, 0, SLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    // new tail
    if (inputPos == SLLSize)
    {
        drawWithHighlight(delPosCode, 8, -1, 0, SLLSize, window, background);
        window.display();
        pause_for(500);
    }

    drawWithHighlight(delPosCode, 8, -1, 0, SLLSize - 1, window, background);
    window.display();
    pause_for(500);

    for (int i = 0; i < 10; ++i)
        nodes[i].setBackgroundColor(sf::Color::White);
}

void SLL::addPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    if (inputPos < 0 || inputPos > SLLSize || inputPos >= 10 || SLLSize >= 10)
        return;
    if (inputPos == 0)
    {
        addHeadAnimation(window, background);
        return;
    }
    if (inputPos == SLLSize)
    {
        addTailAnimation(window, background);
        return;
    }

    // init statement
    addPosCode.setLine(1);
    mainDraw(window, background);
    nodes[0].setBackgroundColor(sf::Color::Green);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(500);

    // for statement
    for (int i = 0; i < inputPos; ++i)
    {
        // for condition
        addPosCode.setLine(2);
        mainDraw(window, background);
        for (int j = 0; j < SLLSize; ++j)
        {
            nodes[j].draw(window);
            if (j > 0)
                drawArrow(window, j, j - 1);
        }
        addPosCode.draw(window);
        drawingHeadTailText(window, 0, SLLSize - 1);
        window.display();
        pause_for(500);

        // last node
        if (i == inputPos - 1)
            break;
        nodes[i].setBackgroundColor(sf::Color::White);
        nodes[i + 1].setBackgroundColor(sf::Color::Green);

        // jumping to next node
        addPosCode.setLine(3);
        mainDraw(window, background);
        for (int j = 0; j < SLLSize; ++j)
        {
            nodes[j].draw(window);
            if (j > 0)
                drawArrow(window, j, j - 1);
        }
        addPosCode.draw(window);
        drawingHeadTailText(window, 0, SLLSize - 1);
        window.display();
        pause_for(500);
    }

    // making changes to array
    SLLSize++;
    for (int i = SLLSize - 1; i > inputPos; --i)
    {
        nodes[i].setString(nodes[i - 1].getString());
        nodeVal[i] = nodeVal[i - 1];
        nodes[i].setPosition(nodesPos[i - 1]);
    }
    nodes[inputPos].setString(toString(inputVal));
    nodeVal[inputPos] = inputVal;
    nodes[inputPos].setPosition({nodesPos[inputPos].x, 300});

    // ading new Node
    nodes[inputPos].setBackgroundColor(sf::Color::Yellow);
    addPosCode.setLine(4);
    mainDraw(window, background);
    for (int j = 0; j < SLLSize; ++j)
    {
        nodes[j].draw(window);
        if (j - 1 == inputPos && j >= 2)
            drawArrow(window, j, j - 2);
        if (j == inputPos || j - 1 == inputPos)
            continue;
        if (j > 0)
            drawArrow(window, j, j - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(1000);

    // moving
    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < SLLSize; ++i)
        {
            sf::Vector2f curPos = nodes[i].getPosition();
            if (curPos != nodesPos[i])
                isMoving = true;
            if (curPos.x < nodesPos[i].x)
                curPos.x += 1;
            else if (curPos.y > nodesPos[i].y)
                curPos.y -= 1;
            nodes[i].setPosition(curPos);
            nodes[i].draw(window);
            if (i == inputPos || i - 1 == inputPos)
                continue;
            if (i > 0)
                drawArrow(window, i, i - 1);
        }
        addPosCode.draw(window);
        drawingHeadTailText(window, 0, SLLSize - 1);
        window.display();
    }
    pause_for(1000);

    // link added node to next node
    addPosCode.setLine(5);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i == inputPos)
            continue;
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(1000);

    // link cur node to added node
    addPosCode.setLine(6);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(1000);

    for (int i = 0; i < SLLSize; ++i)
        nodes[i].setBackgroundColor(sf::Color::White);
}

void SLL::addTailAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    if (SLLSize >= 10)
        return;
    nodeVal[SLLSize] = inputVal;
    nodes[SLLSize].setString(toString(inputVal));
    nodes[SLLSize].setPosition({nodesPos[SLLSize].x, 300});
    nodes[SLLSize].setBackgroundColor(sf::Color::Red);
    ++SLLSize;

    // first frame creating new node
    addTailCode.setLine(1);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0 && i < SLLSize - 1)
            drawArrow(window, i, i - 1);
    }
    addTailCode.draw(window);
    if (SLLSize > 1)
        drawingHeadTailText(window, 0, SLLSize - 2);
    window.display();
    pause_for(1000);

    // moving animation

    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < SLLSize; ++i)
        {
            sf::Vector2f curPos = nodes[i].getPosition();
            if (curPos != nodesPos[i])
                isMoving = true;
            if (curPos.x < nodesPos[i].x)
                curPos.x += 2;
            if (curPos.y > nodesPos[i].y)
                curPos.y -= 2;
            nodes[i].setPosition(curPos);
            nodes[i].draw(window);
            if (i > 0 && i < SLLSize - 1)
                drawArrow(window, i, i - 1);
        }
        addTailCode.draw(window);
        if (SLLSize > 1)
            drawingHeadTailText(window, 0, SLLSize - 2);
        window.display();
    }
    pause_for(1000);

    // second frame drawing arrow
    addTailCode.setLine(2);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addTailCode.draw(window);
    if (SLLSize > 1)
        drawingHeadTailText(window, 0, SLLSize - 2);
    window.display();
    pause_for(1000);

    // last frame changing head
    addTailCode.setLine(3);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addTailCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(1000);

    nodes[SLLSize - 1].setBackgroundColor(sf::Color::White);
}

void SLL::addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    if (SLLSize >= 10)
        return;
    // preparing new position/ value for nodes
    for (int i = SLLSize + 1; i > 0; --i)
    {
        nodes[i].setString(nodes[i - 1].getString());
        nodes[i].setPosition(nodesPos[i - 1]);
        nodeVal[i] = nodeVal[i - 1];
    }
    nodeVal[0] = inputVal;
    nodes[0].setString(toString(inputVal));
    nodes[0].setPosition({nodesPos[0].x, 300});
    nodes[0].setBackgroundColor(sf::Color::Red);
    ++SLLSize;

    // first frame creating new node
    addHeadCode.setLine(1);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 1)
            drawArrow(window, i, i - 1);
    }
    addHeadCode.draw(window);
    if (SLLSize > 1)
        drawingHeadTailText(window, 1, SLLSize - 1);
    window.display();
    pause_for(1000);

    // moving animation

    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < SLLSize; ++i)
        {
            sf::Vector2f curPos = nodes[i].getPosition();
            if (curPos != nodesPos[i])
                isMoving = true;
            if (curPos.x < nodesPos[i].x)
                curPos.x += 2;
            if (curPos.y > nodesPos[i].y)
                curPos.y -= 2;
            nodes[i].setPosition(curPos);
            nodes[i].draw(window);
            if (i > 1)
                drawArrow(window, i, i - 1);
        }
        addHeadCode.draw(window);
        if (SLLSize > 1)
            drawingHeadTailText(window, 1, SLLSize - 1);
        window.display();
    }
    pause_for(1000);

    // second frame drawing arrow
    addHeadCode.setLine(2);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addHeadCode.draw(window);
    if (SLLSize > 1)
        drawingHeadTailText(window, 1, SLLSize - 1);
    window.display();
    pause_for(1000);

    // last frame changing head
    addHeadCode.setLine(3);
    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addHeadCode.draw(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    window.display();
    pause_for(1000);

    nodes[0].setBackgroundColor(sf::Color::White);
}

void SLL::drawNotification(sf::RenderWindow &window, sf::Sprite &background)
{

    mainDraw(window, background);
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    notiFrog.draw(window);
    window.draw(noti);
    drawingHeadTailText(window, 0, SLLSize - 1);

    window.display();

    pause_for(1000);
}

void SLL::mainDraw(sf::RenderWindow &window, sf::Sprite &background)
{
    window.clear();
    window.draw(background);
    window.draw(buttonBox);
    backButton.drawButton(window);
    create.drawButton(window);
    search.drawButton(window);
    insert.drawButton(window);
    remove.drawButton(window);
    update.drawButton(window);

    if (isInputPos || isInputVal)
        inputBox[currInputBox].drawTo(window);

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

void SLL::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
{
    sf::Clock clock;
    // textbox testing

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
                mouseClicked(ev, window, screenID, background);
                isInputPos = isInputVal = 0;
                break;
            case (sf::Event::TextEntered):
                if (inputBox[currInputBox].typedOn(ev))
                    handleInput(window, background);
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
                    mouseClicked(ev, window, screenID, background);
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

    mainDraw(window, background);
    bool colorNewNode = 0;

    for (int i = 0; i < SLLSize; ++i)
    {
        if (SLLisSearching && !colorNewNode && !nodeSearch[i])
        {
            colorNewNode = 1;
            nodeSearch[i] = 1;
            if (nodeVal[i] == searchValue)
            {
                nodes[i].setBackgroundColor(sf::Color::Red);
                isNoti = true;
                noti.setString("found at index " + toString(i + 1));
                SLLisSearching = 0;
                doneSearching = 1;
                frameDelay = 2;
            }
            else
            {
                nodes[i].setBackgroundColor(sf::Color::Green);
                if (i == SLLSize - 1 && SLLisSearching)
                {
                    isNoti = true;
                    noti.setString("not found value " + toString(searchValue));
                    doneSearching = 1;
                    frameDelay = 1;
                }
            }
        }
        if (isDeleting[i])
        {
            nodes[i].setRadius(nodes[i].getRadius() - 1.f);
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
        if (curPos == nodesPos[i])
            continue;
        if (curPos.y > nodesPos[i].y)
            nodes[i].setPosition({curPos.x, curPos.y - 2});
        else if (curPos.x > nodesPos[i].x)
            nodes[i].setPosition({curPos.x - 2, curPos.y});
        else if (curPos.x < nodesPos[i].x)
            nodes[i].setPosition({curPos.x + 2, curPos.y});
    }

    for (int i = 1; i < SLLSize; ++i)
        drawArrow(window, i, i - 1);
    // drawArrow(window);
    drawingHeadTailText(window, 0, SLLSize - 1);
    // addHeadCode.draw(window);
    if (isNoti)
    {
        isNoti = false;
        notiFrog.draw(window);
        window.draw(noti);
    }
    if (SLLisSearching)
        pause_for(500);
    else if (frameDelay > 0)
    {
        if (frameDelay > 1)
            pause_for(500);
        else
            pause_for(2000);
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
    if (update.hoverChangeColor(ev, window))
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

void SLL::mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
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
    else if (update.isMouseOnButton(window))
    {
        isInputPos = 1;
        currInputBox = 6;
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
        {
            isInputVal = 1;
            currInputBox = 2;
        }
        else if (subInsertButton[2].isMouseOnButton(window))
        {
            isInputPos = 1;
            currInputBox = 4;
        }
        else if (subInsertButton[1].isMouseOnButton(window))
        {
            isInputVal = 1;
            currInputBox = 3;
        }
    }

    if (drawSubRemove)
    {
        if (subRemoveButton[0].isMouseOnButton(window))
        {
            delHeadAnimation(window, background);
        }
        else if (subRemoveButton[2].isMouseOnButton(window))
        {
            isInputPos = 1;
            currInputBox = 5;
        }
        else if (subRemoveButton[1].isMouseOnButton(window))
        {
            inputPos = SLLSize;
            delPosAnimation(window, background);
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
        nodeVal[i] = nodeVal[i - 1];
    }

    ++SLLSize;
    // for (int i = 0; i < pos; ++i) nodes[i].setPosition(nodesPos[i - 1]);
    int val = inputVal;
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
    for (int i = 0; i < SLLSize; ++i)
    {
        nodes[i].setBackgroundColor(sf::Color::White);
        nodeSearch[i] = 0;
    }
    doneSearching = 0;
    SLLisSearching = 0;
}

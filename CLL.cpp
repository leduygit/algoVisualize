#include "CLL.hpp"

CLL::CLL(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    CLLSize = 0;
    drawSubCreate = drawSubInsert = drawSubRemove = drawSubSearch = 0;
    title.setFont(font);
    title.setString("Circular Linked List");
    title.setCharacterSize(30);
    title.setStyle(sf::Text::Italic);
    title.setPosition({250, 60});
    title.setFillColor(sf::Color::Black);

    headText.setFillColor(sf::Color::Black);
    tailText.setFillColor(sf::Color::Black);
    inputTitle.setFillColor(sf::Color::Black);
    headText.setFont(font);
    tailText.setFont(font);
    inputTitle.setFont(font);
    headText.setString("Head");
    tailText.setString("Tail");
    tailText.setCharacterSize(20);
    headText.setCharacterSize(20);
    inputTitle.setCharacterSize(20);

    noti.setFillColor(sf::Color::Black);
    noti.setFont(font);
    noti.setPosition({580, 420});
    noti.setCharacterSize(60);

    notiFrog.loadTexture("Image/notifrog.png");
    notiFrog.setPosition({400, 350});
    searchCode.loadTexture("Image/SLLsearchCode.png");
    searchCode.setPosition({911, 577});
    addHeadCode.loadTexture("Image/CLLaddHeadCode.png");
    addHeadCode.setPosition({911, 666});
    addTailCode.loadTexture("Image/CLLaddTailCode.png");
    addTailCode.setPosition({911, 666});
    addPosCode.loadTexture("Image/SLLaddPosCode.png");
    addPosCode.setPosition({911, 600});
    delHeadCode.loadTexture("Image/CLLdelHeadCode.png");
    delHeadCode.setPosition({911, 643});
    delPosCode.loadTexture("Image/CLLdelPosCode.png");
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

    std::string subCreateName[] = {"Empty", "Random", "Sorted", "File"};

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
    }

    for (int i = 0; i < 8; ++i)
    {
        inputBox[i] = Textbox(20, sf::Color::Black, 1);
        inputBox[i].setFont(font);
    }

    // create input box
    inputBox[0].setPosition({subCreateButton[3].getPos().x + 100, position.y + buttonSize.y + 5});

    // search input box
    inputBox[1].setPosition({subSearchButton[0].getPos().x + 100, position.y + 2 * buttonSize.y + 5});

    // insert input box
    inputBox[2].setPosition({subInsertButton[0].getPos().x + 100, position.y + 3 * buttonSize.y + 5});
    inputBox[3].setPosition({subInsertButton[1].getPos().x + 100, position.y + 3 * buttonSize.y + 5});
    inputBox[4].setPosition({subInsertButton[2].getPos().x + 100, position.y + 3 * buttonSize.y + 5});

    // remove input box
    inputBox[5].setPosition({subInsertButton[2].getPos().x + 100, position.y + 4 * buttonSize.y + 5});

    // update input box
    inputBox[6].setPosition({update.getPos().x + 210, position.y + 4 * buttonSize.y + 15});
}

void CLL::inputFromFile(sf::RenderWindow &window, sf::Sprite &background)
{
    std::ifstream fi;
    fi.open("data.txt");
    if (!fi.is_open()) 
    {
        noti.setString("Can't found data.txt, please input from data.txt");
        drawNotification(window, background);
        return;
    }
    fi >> CLLSize;
    if (CLLSize > 10)
    {
        CLLSize = 0;
        noti.setString("Size must be from 1 to 10");
        drawNotification(window, background);
        return;
    }
    for (int i = 0; i < CLLSize; ++i)
    {
        fi >> nodeVal[i];
        if (nodeVal[i] > 100 || nodeVal[i] < 0)
        {
            CLLSize = 0;
            noti.setString("Value must be from 1 to 100");
            drawNotification(window, background);
            return;
        }
        nodes[i].setString(toString(nodeVal[i]));
    }
    fi.close();
}

void CLL::drawArrow(sf::RenderWindow &window, int i, int j)
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

void CLL::handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background)
{
    // 0 = create fixed size
    // 1 = search value
    // 2 = insert head
    // 3 = insert tail
    // 4 = insert custom position
    // 5 = remove custom position
    // 6 = update value for position
    if (inputPos > CLLSize)
    {
        noti.setString("Out of bound");
        drawNotification(window, background);
        inputPos = 0;
        return;
    }

    if (inputVal > 100)
    {
        noti.setString("Value must be from 0 to 100");
        drawNotification(window, background);
        inputVal = 0;
        return;
    }

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

void CLL::handleInput(sf::RenderWindow &window, sf::Sprite &background)
{
    if (isInputPos)
    {
        isInputPos = 0;
        inputPos = stringToInt(inputBox[currInputBox].getText());
        inputBox[currInputBox].setText("");
        if (currInputBox == 5)
        {
            inputVal = 0;
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


void CLL::searchAnimation(sf::RenderWindow &window, sf::Sprite &background)
{

    // line 1, checking null array
    mainDraw(window, background);
    searchCode.setLine(1);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    searchCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(500);

    if (CLLSize == 0)
    {
        noti.setString("Not found value " + toString(searchValue));
        mainDraw(window, background);
        for (int i = 0; i < CLLSize; ++i)
        {
            nodes[i].draw(window);
            if (i > 0)
                drawArrow(window, i, i - 1);
        }
        searchCode.draw(window);
        drawingHeadTailText(window, 0, CLLSize - 1);
        window.display();
        pause_for(500);
        drawNotification(window, background);
        return;
    }

    int foundValue = 0;
    // change nodes color and highlight animation
    for (int i = 0; i < CLLSize; ++i)
    {
        // if first frame then draw initialize frame
        if (i == 0)
        {
            nodes[i].setBackgroundColor(sf::Color::Green);
            searchCode.setLine(2);
            mainDraw(window, background);
            for (int j = 0; j < CLLSize; ++j)
            {
                nodes[j].draw(window);
                if (j > 0)
                    drawArrow(window, j, j - 1);
            }
            searchCode.draw(window);
            drawingHeadTailText(window, 0, CLLSize - 1);
            window.display();
            pause_for(500);
        }

        // first frame - while statement
        {
            searchCode.setLine(3);
            mainDraw(window, background);
            for (int j = 0; j < CLLSize; ++j)
            {
                nodes[j].draw(window);
                if (j > 0)
                    drawArrow(window, j, j - 1);
            }
            searchCode.draw(window);
            drawingHeadTailText(window, 0, CLLSize - 1);
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
        if (i == CLLSize - 1)
            break;

        // second frame - jumping to next node
        {
            // set next node color
            if (i + 1 < CLLSize)
                nodes[i + 1].setBackgroundColor(sf::Color::Green);
            searchCode.setLine(4);
            mainDraw(window, background);
            for (int j = 0; j < CLLSize; ++j)
            {
                nodes[j].draw(window);
                if (j > 0)
                    drawArrow(window, j, j - 1);
            }
            searchCode.draw(window);
            drawingHeadTailText(window, 0, CLLSize - 1);

            window.display();
            pause_for(500);
        }
    }

    // last if statement
    {
        searchCode.setLine(6);
        mainDraw(window, background);
        for (int i = 0; i < CLLSize; ++i)
        {
            nodes[i].draw(window);
            if (i > 0)
                drawArrow(window, i, i - 1);
        }
        searchCode.draw(window);
        drawingHeadTailText(window, 0, CLLSize - 1);

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
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    searchCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);

    window.display();
    pause_for(500);
    drawNotification(window, background);

    for (int i = 0; i < CLLSize; ++i)
        nodes[i].setBackgroundColor(sf::Color::White);
}

void CLL::updatePosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    // line 1, checking null array
    drawWithHighlight(updatePosCode, 1, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(500);

    if (CLLSize == 0)
    {
        noti.setString("Not found value " + toString(searchValue));
        drawNotification(window, background);
        return;
    }

    if (inputPos >= CLLSize) return;

    // set cur = head;
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(updatePosCode, 2, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(500);

    // finding update pos
    for (int i = 0; i <= inputPos; ++i)
    {
        // for statement
        drawWithHighlight(updatePosCode, 3, -1, 0, CLLSize - 1, window, background);
        window.display();
        pause_for(500);

        // last node
        if (i == inputPos) break;

        // jumping to next node
        nodes[i].setBackgroundColor(sf::Color::White);
        nodes[i + 1].setBackgroundColor(sf::Color::Green);
        drawWithHighlight(updatePosCode, 4, -1, 0, CLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    // delete old data
    std::string curData = nodes[inputPos].getString();
    while (true)
    {
        drawWithHighlight(updatePosCode, 5, -1, 0, CLLSize - 1, window, background);
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
        drawWithHighlight(updatePosCode, 5, -1, 0, CLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    nodes[inputPos].setBackgroundColor(sf::Color::White);
}

void CLL::drawCircularArrow(sf::RenderWindow &window, int posHead, int posTail)
{
    if (posHead != 0 || posTail != CLLSize - 1) return;
    sf::RectangleShape rect;

    // mui ten di sang ngang
    rect.setSize({40, 10});
    sf::Vector2f headPos = nodes[posHead].getCenter();
    sf::Vector2f tailPos = nodes[posTail].getCenter();

    rect.setFillColor(sf::Color::Black);
    rect.setPosition({tailPos.x + 33, tailPos.y - 5});
    window.draw(rect);

    // mui ten doc (o cuoi)
    rect.setSize({10, 150});
    rect.setPosition({tailPos.x + 63, tailPos.y + 5});
    window.draw(rect);
    // rect.setSize({10, 92});
    // rect.setPosition({headPos.x - 5, headPos.y + 63});
    // window.draw(rect);

    // arrow
    ArrowShape arr(72, 8, 20, 20);
    arr.setColor(sf::Color::Black);
    arr.setPosition({headPos.x - 5, headPos.y + 155});
    arr.rotate(-90);
    window.draw(arr);

    rect.setSize({tailPos.x + 73 - headPos.x + 5, 10});
    rect.setPosition({headPos.x - 5, headPos.y + 155});
    window.draw(rect);

}

void CLL::drawingHeadTailText(sf::RenderWindow &window, int posHead, int posTail)
{
    if (posHead >= CLLSize)
        return;
    if (CLLSize == 0)
        return;
    sf::Vector2f headPos = nodes[posHead].getCenter();
    headText.setPosition({headPos.x - 27, headPos.y + 35});
    sf::Vector2f tailPos = nodes[posTail].getCenter();
    tailText.setPosition({tailPos.x - 17, tailPos.y + 35});
    if (posHead == posTail)
    {
        headText.setPosition({headPos.x - 40, headPos.y + 35});
        headText.setString("Head/Tail");
        window.draw(headText);
    }
    else
    {
        headText.setString("Head");
        window.draw(headText);
        if (posTail < CLLSize)
            window.draw(tailText);
    }
    drawCircularArrow(window, posHead, posTail);
}

void CLL::drawWithHighlight(Highlight feature, int highlightLine, int posNotDrawingArrow, int headPos, int tailPos, sf::RenderWindow &window, sf::Sprite &background)
{
    // posNotDrawingArrow = -1, draw all arrow
    feature.setLine(highlightLine);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0 && i != posNotDrawingArrow)
            drawArrow(window, i, i - 1);
    }
    feature.draw(window);
    drawingHeadTailText(window, headPos, tailPos);
}

void CLL::delHeadAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    // first line checking empty
    drawWithHighlight(delHeadCode, 1, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(1000);

    if (CLLSize == 0)
    {
        noti.setString("Linked list empty");
        drawNotification(window, background);
        return;
    }

    // second line setting cur = head;
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(delHeadCode, 2, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(1000);

    // third line changing head
    drawWithHighlight(delHeadCode, 3, -1, 1, CLLSize - 1, window, background);
    window.display();
    pause_for(1000);

    // last line deleting nodes
    bool isDeleteNode = true;
    while (isDeleteNode)
    {
        drawWithHighlight(delHeadCode, 4, -1, 1, CLLSize - 1, window, background);
        window.display();
        isDeleteNode = (nodes[0].getRadius() > 0);
        nodes[0].setRadius(nodes[0].getRadius() - 1);
    }

    nodes[0].setRadius(30);
    nodes[0].setBackgroundColor(sf::Color::White);
    // making changes to linkedlist
    --CLLSize;
    for (int i = 0; i < CLLSize; ++i)
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
        drawWithHighlight(delHeadCode, 4, -1, 0, CLLSize - 1, window, background);
        window.display();
        for (int i = 0; i < CLLSize; ++i)
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

void CLL::delPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    // checking empty
    drawWithHighlight(delPosCode, 1, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(500);

    if (CLLSize == 0)
    {
        noti.setString("Linked list empty");
        drawNotification(window, background);
        pause_for(500);
        return;
    }

    --inputPos;
    if (inputPos < 0 || inputPos >= CLLSize)
        return;

    // set cur = head
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(delPosCode, 2, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(500);

    // finding delPos
    for (int i = 0; i < inputPos; ++i)
    {
        // for statement
        drawWithHighlight(delPosCode, 3, -1, 0, CLLSize - 1, window, background);
        window.display();
        pause_for(500);

        // last node
        if (i == inputPos - 1)
            break;

        // jumping to next node
        nodes[i].setBackgroundColor(sf::Color::White);
        nodes[i + 1].setBackgroundColor(sf::Color::Green);
        drawWithHighlight(delPosCode, 4, -1, 0, CLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    // set deletion node, and the next node of it
    nodes[inputPos].setBackgroundColor(sf::Color::Red);
    if (inputPos + 1 < CLLSize)
        nodes[inputPos + 1].setBackgroundColor(sf::Color::Yellow);

    drawWithHighlight(delPosCode, 5, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(500);

    // deleting
    bool isDeleteNode = true;
    while (isDeleteNode)
    {
        drawWithHighlight(delPosCode, 6, -1, 0, CLLSize - 1, window, background);
        window.display();
        isDeleteNode = (nodes[inputPos].getRadius() > 0);
        nodes[inputPos].setRadius(nodes[inputPos].getRadius() - 1);
    }

    // making changes to array
    --CLLSize;
    nodes[inputPos].setBackgroundColor(sf::Color::Yellow);
    nodes[inputPos].setRadius(30);
    if (inputPos < 10)
        nodes[inputPos + 1].setBackgroundColor(sf::Color::White);

    for (int i = inputPos; i < CLLSize; ++i)
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
        if (inputPos == CLLSize)
            drawWithHighlight(delPosCode, 6, inputPos, 0, CLLSize, window, background);
        else
            drawWithHighlight(delPosCode, 6, inputPos, 0, CLLSize - 1, window, background);

        window.display();
        for (int i = 0; i < CLLSize; ++i)
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
    if (inputPos == CLLSize)
    {
        drawWithHighlight(delPosCode, 7, -1, 0, CLLSize, window, background);
        window.display();
        pause_for(500);
    }
    else
    {
        drawWithHighlight(delPosCode, 7, -1, 0, CLLSize - 1, window, background);
        window.display();
        pause_for(500);
    }

    // new tail
    if (inputPos == CLLSize)
    {
        drawWithHighlight(delPosCode, 8, -1, 0, CLLSize, window, background);
        window.display();
        pause_for(500);
    }

    drawWithHighlight(delPosCode, 8, -1, 0, CLLSize - 1, window, background);
    window.display();
    pause_for(500);

    for (int i = 0; i < 10; ++i)
        nodes[i].setBackgroundColor(sf::Color::White);
}

void CLL::addPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    if (inputPos < 0 || inputPos > CLLSize || inputPos >= 10 || CLLSize >= 10)
        return;
    if (inputPos == 0)
    {
        addHeadAnimation(window, background);
        return;
    }
    if (inputPos == CLLSize)
    {
        addTailAnimation(window, background);
        return;
    }

    // init statement
    addPosCode.setLine(1);
    mainDraw(window, background);
    nodes[0].setBackgroundColor(sf::Color::Green);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(500);

    // for statement
    for (int i = 0; i < inputPos; ++i)
    {
        // for condition
        addPosCode.setLine(2);
        mainDraw(window, background);
        for (int j = 0; j < CLLSize; ++j)
        {
            nodes[j].draw(window);
            if (j > 0)
                drawArrow(window, j, j - 1);
        }
        addPosCode.draw(window);
        drawingHeadTailText(window, 0, CLLSize - 1);
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
        for (int j = 0; j < CLLSize; ++j)
        {
            nodes[j].draw(window);
            if (j > 0)
                drawArrow(window, j, j - 1);
        }
        addPosCode.draw(window);
        drawingHeadTailText(window, 0, CLLSize - 1);
        window.display();
        pause_for(500);
    }

    // making changes to array
    CLLSize++;
    for (int i = CLLSize - 1; i > inputPos; --i)
    {
        nodes[i].setString(nodes[i - 1].getString());
        nodeVal[i] = nodeVal[i - 1];
        nodes[i].setPosition(nodesPos[i - 1]);
    }
    nodes[inputPos].setString(toString(inputVal));
    nodeVal[inputPos] = inputVal;
    nodes[inputPos].setPosition({nodesPos[inputPos].x, 275});

    // ading new Node
    nodes[inputPos].setBackgroundColor(sf::Color::Yellow);
    addPosCode.setLine(4);
    mainDraw(window, background);
    for (int j = 0; j < CLLSize; ++j)
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
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(1000);

    // moving
    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < CLLSize; ++i)
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
        drawingHeadTailText(window, 0, CLLSize - 1);
        window.display();
    }
    pause_for(1000);

    // link added node to next node
    addPosCode.setLine(5);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i == inputPos)
            continue;
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(1000);

    // link cur node to added node
    addPosCode.setLine(6);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }
    addPosCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(1000);

    for (int i = 0; i < CLLSize; ++i)
        nodes[i].setBackgroundColor(sf::Color::White);
}

void CLL::addTailAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    if (CLLSize >= 10)
        return;
    nodeVal[CLLSize] = inputVal;
    nodes[CLLSize].setString(toString(inputVal));
    nodes[CLLSize].setPosition({nodesPos[CLLSize].x, 300});
    nodes[CLLSize].setBackgroundColor(sf::Color::Red);
    ++CLLSize;

    // first frame creating new node
    addTailCode.setLine(1);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0 && i < CLLSize - 1)
            drawArrow(window, i, i - 1);
    }
    addTailCode.draw(window);
    if (CLLSize > 1)
        drawingHeadTailText(window, 0, CLLSize - 2);
    window.display();
    pause_for(1000);

    // moving animation

    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < CLLSize; ++i)
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
            if (i > 0 && i < CLLSize - 1)
                drawArrow(window, i, i - 1);
        }
        addTailCode.draw(window);
        if (CLLSize > 1)
            drawingHeadTailText(window, 0, CLLSize - 2);
        window.display();
    }
    pause_for(1000);

    // second frame drawing arrow
    addTailCode.setLine(2);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addTailCode.draw(window);
    if (CLLSize > 1)
        drawingHeadTailText(window, 0, CLLSize - 2);
    window.display();
    pause_for(1000);

    // last frame changing head
    addTailCode.setLine(3);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addTailCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(1000);

    nodes[CLLSize - 1].setBackgroundColor(sf::Color::White);
}

void CLL::addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    if (CLLSize >= 10)
        return;
    // preparing new position/ value for nodes
    for (int i = CLLSize + 1; i > 0; --i)
    {
        nodes[i].setString(nodes[i - 1].getString());
        nodes[i].setPosition(nodesPos[i - 1]);
        nodeVal[i] = nodeVal[i - 1];
    }
    nodeVal[0] = inputVal;
    nodes[0].setString(toString(inputVal));
    nodes[0].setPosition({nodesPos[0].x, 300});
    nodes[0].setBackgroundColor(sf::Color::Red);
    ++CLLSize;

    // first frame creating new node
    addHeadCode.setLine(1);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 1)
            drawArrow(window, i, i - 1);
    }
    addHeadCode.draw(window);
    if (CLLSize > 1)
        drawingHeadTailText(window, 1, CLLSize - 1);
    window.display();
    pause_for(1000);

    // moving animation

    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < CLLSize; ++i)
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
        if (CLLSize > 1)
            drawingHeadTailText(window, 1, CLLSize - 1);
        window.display();
    }
    pause_for(1000);

    // second frame drawing arrow
    addHeadCode.setLine(2);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addHeadCode.draw(window);
    if (CLLSize > 1)
        drawingHeadTailText(window, 1, CLLSize - 1);
    window.display();
    pause_for(1000);

    // last frame changing head
    addHeadCode.setLine(3);
    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addHeadCode.draw(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    window.display();
    pause_for(1000);

    nodes[0].setBackgroundColor(sf::Color::White);
}

void CLL::drawNotification(sf::RenderWindow &window, sf::Sprite &background)
{

    mainDraw(window, background);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    notiFrog.draw(window);
    window.draw(noti);
    drawingHeadTailText(window, 0, CLLSize - 1);

    window.display();

    pause_for(1000);
}

void CLL::mainDraw(sf::RenderWindow &window, sf::Sprite &background)
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
    window.draw(title);

    if (isInputPos || isInputVal){
        inputBox[currInputBox].drawTo(window);
        if (isInputPos)
            inputTitle.setString("Index: ");
        else
            inputTitle.setString("Value: ");
        sf::Vector2f inputPos = inputBox[currInputBox].getPosition();
        inputTitle.setPosition({inputPos.x - 75, inputPos.y});
        window.draw(inputTitle);
    }

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

void CLL::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
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

    // if (CLLSize != 0)
    // {
    //     int i = randInt(0, CLLSize);
    //     nodes[i].setPosition({nodesPos[i].x, 300});
    // }

    mainDraw(window, background);

    for (int i = 0; i < CLLSize; ++i) nodes[i].draw(window);
    

    for (int i = 1; i < CLLSize; ++i)
        drawArrow(window, i, i - 1);
    // drawArrow(window);
    drawingHeadTailText(window, 0, CLLSize - 1);
    // addHeadCode.draw(window);
}

bool CLL::checkHover(sf::Event &ev, sf::RenderWindow &window)
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

void CLL::mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
{
    // if (ev.type != sf::Event::MouseButtonReleased) return;
    if (backButton.isMouseOnButton(window))
    {
        CLLSize = 0;
        screenID = 2;
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
        drawSubCreate = drawSubInsert = drawSubRemove = drawSubSearch = 0;
    }

    if (drawSubCreate)
    {
        if (subCreateButton[0].isMouseOnButton(window))
            CLLSize = 0;
        else if (subCreateButton[1].isMouseOnButton(window))
            randomCLL();
        else if (subCreateButton[2].isMouseOnButton(window))
            randomSortedCLL();
        else if (subCreateButton[3].isMouseOnButton(window))
            inputFromFile(window, background);
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
            inputPos = CLLSize;
            delPosAnimation(window, background);
        }
    }

    if (drawSubSearch)
    {
        if (subSearchButton[0].isMouseOnButton(window))
        {
            isInputVal = 1;
            inputPos = 0;
            currInputBox = 1;
            inputBox[1].setSelected(1);
        }
    }
}

void CLL::randomCLL()
{
    CLLSize = randInt(1, 10);
    for (int i = 0; i < CLLSize; ++i)
    {
        nodes[i].setPosition(nodesPos[i]);
        int x = randInt(1, 100);
        nodeVal[i] = x;
        nodes[i].setString(toString(x));
    }
}

void CLL::randomSortedCLL()
{
    CLLSize = randInt(1, 10);
    int x = 1;
    for (int i = 0; i < CLLSize; ++i)
    {
        x = randInt(x, 100);
        nodeVal[i] = x;
        nodes[i].setString(toString(x));
        nodes[i].setPosition(nodesPos[i]);
    }
}

#include "Stack.hpp"

void Stack::pause_for(int pauseTime)
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

Stack::Stack(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    StackSize = 0;
    drawSubCreate = drawSubInsert = drawSubRemove = 0;
    isInputPos = isInputVal = 0;

    title.setFont(font);
    title.setString("Stack");
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
    noti.setString("testing");
    noti.setCharacterSize(60);

    notiFrog.loadTexture("Image/notifrog.png");
    notiFrog.setPosition({400, 350});

    addHeadCode.loadTexture("Image/SLLaddHeadCode.png");
    addHeadCode.setPosition({911, 666});
    delHeadCode.loadTexture("Image/SLLdelHeadCode.png");
    delHeadCode.setPosition({911, 643});

    create = Button("Create", textColor, font, buttonSize, backgroundColor);
    insert = Button("Push", textColor, font, buttonSize, backgroundColor);
    remove = Button("Pop", textColor, font, buttonSize, backgroundColor);
    backButton = Button("Return", textColor, font, {100, 50}, backgroundColor);
    backButton.setOutlineThickness(4);

    sf::Vector2f position = {100, 520};
    buttonBox.setOutlineColor(sf::Color::Black);
    buttonBox.setOutlineThickness(4.f);
    buttonBox.setPosition(position);
    buttonBox.setSize({buttonSize.x, 3 * buttonSize.y});

    create.setPosition(position);
    insert.setPosition({position.x, position.y + buttonSize.y});
    remove.setPosition({position.x, position.y + 2 * buttonSize.y});
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

    // insert input box
    inputBox[2].setPosition({insert.getPos().x + 210, position.y + buttonSize.y + 5});

    // remove input box
    inputBox[5].setPosition({subInsertButton[2].getPos().x + 100, position.y + 4 * buttonSize.y + 5});
}

void Stack::inputFromFile(sf::RenderWindow &window, sf::Sprite &background)
{
    std::ifstream fi;
    fi.open("data.txt");
    if (!fi.is_open())
    {
        noti.setString("Can't found data.txt, please input from data.txt");
        drawNotification(window, background);
        return;
    }
    fi >> StackSize;
    if (StackSize > 10)
    {
        StackSize = 0;
        noti.setString("Size must be from 1 to 10");
        drawNotification(window, background);
        return;
    }
    for (int i = 0; i < StackSize; ++i)
    {
        fi >> nodeVal[i];
        if (nodeVal[i] > 100 || nodeVal[i] < 0)
        {
            StackSize = 0;
            noti.setString("Value must be from 1 to 100");
            drawNotification(window, background);
            return;
        }
        nodes[i].setString(toString(nodeVal[i]));
    }
    fi.close();
}

void Stack::drawArrow(sf::RenderWindow &window, int i, int j)
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

void Stack::handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background)
{
    // 0 = create fixed size
    // 1 = search value
    // 2 = insert head
    // 3 = insert tail
    // 4 = insert custom position
    // 5 = remove custom position
    // 6 = update value for position
    if (inputPos > StackSize)
    {
        noti.setString("Position must be from 1 to " + toString(StackSize));
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
    case 2:
        addHeadAnimation(window, background);
        break;
    default:
        break;
    }
}

void Stack::handleInput(sf::RenderWindow &window, sf::Sprite &background)
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

void Stack::drawingHeadTailText(sf::RenderWindow &window, int posHead, int posTail)
{
    if (posHead >= StackSize)
        return;
    if (StackSize == 0)
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
        if (posTail < StackSize)
            window.draw(tailText);
    }
}

void Stack::drawWithHighlight(Highlight feature, int highlightLine, int posNotDrawingArrow, int headPos, int tailPos, sf::RenderWindow &window, sf::Sprite &background)
{
    // posNotDrawingArrow = -1, draw all arrow
    feature.setLine(highlightLine);
    mainDraw(window, background);
    for (int i = 0; i < StackSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0 && i != posNotDrawingArrow)
            drawArrow(window, i, i - 1);
    }
    feature.draw(window);
    drawingHeadTailText(window, headPos, tailPos);
}

void Stack::delHeadAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    // first line checking empty
    drawWithHighlight(delHeadCode, 1, -1, 0, StackSize - 1, window, background);
    window.display();
    pause_for(1000);

    if (StackSize == 0)
    {
        noti.setString("Stack empty");
        drawNotification(window, background);
        return;
    }

    // second line setting cur = head;
    nodes[0].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(delHeadCode, 2, -1, 0, StackSize - 1, window, background);
    window.display();
    pause_for(1000);

    // third line changing head
    drawWithHighlight(delHeadCode, 3, -1, 1, StackSize - 1, window, background);
    window.display();
    pause_for(1000);

    // last line deleting nodes
    bool isDeleteNode = true;
    while (isDeleteNode)
    {
        drawWithHighlight(delHeadCode, 4, -1, 1, StackSize - 1, window, background);
        window.display();
        isDeleteNode = (nodes[0].getRadius() > 0);
        nodes[0].setRadius(nodes[0].getRadius() - 1);
    }

    nodes[0].setRadius(30);
    nodes[0].setBackgroundColor(sf::Color::White);
    // making changes to linkedlist
    --StackSize;
    for (int i = 0; i < StackSize; ++i)
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
        drawWithHighlight(delHeadCode, 4, -1, 0, StackSize - 1, window, background);
        window.display();
        for (int i = 0; i < StackSize; ++i)
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

void Stack::addHeadAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    if (StackSize >= 10)
        return;
    // preparing new position/ value for nodes
    for (int i = StackSize + 1; i > 0; --i)
    {
        nodes[i].setString(nodes[i - 1].getString());
        nodes[i].setPosition(nodesPos[i - 1]);
        nodeVal[i] = nodeVal[i - 1];
    }
    nodeVal[0] = inputVal;
    nodes[0].setString(toString(inputVal));
    nodes[0].setPosition({nodesPos[0].x, 300});
    nodes[0].setBackgroundColor(sf::Color::Red);
    ++StackSize;

    // first frame creating new node
    addHeadCode.setLine(1);
    mainDraw(window, background);
    for (int i = 0; i < StackSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 1)
            drawArrow(window, i, i - 1);
    }
    addHeadCode.draw(window);
    if (StackSize > 1)
        drawingHeadTailText(window, 1, StackSize - 1);
    window.display();
    pause_for(1000);

    // moving animation

    bool isMoving = true;
    while (isMoving)
    {
        isMoving = false;
        mainDraw(window, background);
        for (int i = 0; i < StackSize; ++i)
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
        if (StackSize > 1)
            drawingHeadTailText(window, 1, StackSize - 1);
        window.display();
    }
    pause_for(1000);

    // second frame drawing arrow
    addHeadCode.setLine(2);
    mainDraw(window, background);
    for (int i = 0; i < StackSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addHeadCode.draw(window);
    if (StackSize > 1)
        drawingHeadTailText(window, 1, StackSize - 1);
    window.display();
    pause_for(1000);

    // last frame changing head
    addHeadCode.setLine(3);
    mainDraw(window, background);
    for (int i = 0; i < StackSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    addHeadCode.draw(window);
    drawingHeadTailText(window, 0, StackSize - 1);
    window.display();
    pause_for(1000);

    nodes[0].setBackgroundColor(sf::Color::White);
}

void Stack::drawNotification(sf::RenderWindow &window, sf::Sprite &background)
{

    mainDraw(window, background);
    for (int i = 0; i < StackSize; ++i)
    {
        nodes[i].draw(window);
        if (i > 0)
            drawArrow(window, i, i - 1);
    }

    notiFrog.draw(window);
    window.draw(noti);
    drawingHeadTailText(window, 0, StackSize - 1);

    window.display();

    pause_for(1000);
}

void Stack::mainDraw(sf::RenderWindow &window, sf::Sprite &background)
{
    window.clear();
    window.draw(background);
    window.draw(buttonBox);
    backButton.drawButton(window);
    create.drawButton(window);
    insert.drawButton(window);
    remove.drawButton(window);
    window.draw(title);

    if (isInputPos || isInputVal)
    {
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

    if (drawSubInsert)
        for (int i = 0; i < 3; ++i)
            subInsertButton[i].drawButton(window);

    if (drawSubRemove)
        for (int i = 0; i < 3; ++i)
            subRemoveButton[i].drawButton(window);
}

void Stack::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
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

    // if (StackSize != 0)
    // {
    //     int i = randInt(0, StackSize);
    //     nodes[i].setPosition({nodesPos[i].x, 300});
    // }

    mainDraw(window, background);
    bool colorNewNode = 0;

    for (int i = 0; i < StackSize; ++i)
        nodes[i].draw(window);

    for (int i = 1; i < StackSize; ++i)
        drawArrow(window, i, i - 1);
    // drawArrow(window);
    drawingHeadTailText(window, 0, StackSize - 1);
    // addHeadCode.draw(window);
}

bool Stack::checkHover(sf::Event &ev, sf::RenderWindow &window)
{
    if (backButton.hoverChangeColor(ev, window))
        return true;
    if (create.hoverChangeColor(ev, window))
        return true;
    if (insert.hoverChangeColor(ev, window))
        return true;
    if (remove.hoverChangeColor(ev, window))
        return true;

    if (drawSubCreate)
        for (int i = 0; i < 4; ++i)
            if (subCreateButton[i].hoverChangeColor(ev, window))
                return true;

    return false;
}

void Stack::mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
{
    // if (ev.type != sf::Event::MouseButtonReleased) return;
    if (backButton.isMouseOnButton(window))
    {
        StackSize = 0;
        screenID = 2;
        return;
    }
    if (create.isMouseOnButton(window))
    {
        drawSubCreate = !drawSubCreate;
    }
    else if (insert.isMouseOnButton(window))
    {
        isInputVal = 1;
        currInputBox = 2;
        drawSubCreate = 0;
    }
    else if (remove.isMouseOnButton(window))
    {
        delHeadAnimation(window, background);
        drawSubCreate = 0;
    }

    if (drawSubCreate)
    {
        if (subCreateButton[0].isMouseOnButton(window))
            StackSize = 0;
        else if (subCreateButton[1].isMouseOnButton(window))
            randomStack();
        else if (subCreateButton[2].isMouseOnButton(window))
            randomSortedStack();
        else if (subCreateButton[3].isMouseOnButton(window))
            inputFromFile(window, background);
    }
}

void Stack::randomStack()
{
    StackSize = randInt(1, 10);
    for (int i = 0; i < StackSize; ++i)
    {
        nodes[i].setPosition(nodesPos[i]);
        int x = randInt(1, 100);
        nodeVal[i] = x;
        nodes[i].setString(toString(x));
    }
}

void Stack::randomSortedStack()
{
    StackSize = randInt(1, 10);
    int x = 1;
    for (int i = 0; i < StackSize; ++i)
    {
        x = randInt(x, 100);
        nodeVal[i] = x;
        nodes[i].setString(toString(x));
        nodes[i].setPosition(nodesPos[i]);
    }
}

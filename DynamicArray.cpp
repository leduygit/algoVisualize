#include "DynamicArray.hpp"

DynamicArray::DynamicArray(sf::Color textColor, sf::Font &font, sf::Vector2f buttonSize, sf::Color backgroundColor)
{
    SASize = usedSize = 0;
    drawSubAcess = drawSubCreate = 0;
    isInputPos = isInputVal = 0;

    title.setFont(font);
    title.setString("Dynamic Array");
    title.setCharacterSize(30);
    title.setStyle(sf::Text::Italic);
    title.setPosition({250, 60});
    title.setFillColor(sf::Color::Black);

    // hightlight setup
    searchCode.loadTexture("Image/ArraySearchCode.png");
    searchCode.setPosition({911, 643});
    delPosCode.loadTexture("Image/ArrayDelPosCode.png");
    delPosCode.setPosition({911, 666});
    addPosCode.loadTexture("Image/DynamicAddPosCode.png");
    addPosCode.setPosition({911, 620});
    updatePosCode.loadTexture("Image/ArrayUpdatePosCode.png");
    updatePosCode.setPosition({911, 712});
    accessPosCode.loadTexture("Image/ArrayAccessPosCode.png");
    accessPosCode.setPosition({911, 712});

    index.setFont(font);
    index.setCharacterSize(30);
    index.setFillColor(sf::Color::Black);

    inputTitle.setFillColor(sf::Color::Black);
    inputTitle.setFont(font);
    inputTitle.setCharacterSize(20);

    noti.setFillColor(sf::Color::Black);
    noti.setFont(font);
    noti.setPosition({580, 420});
    noti.setCharacterSize(60);

    notiFrog.loadTexture("Image/notifrog.png");
    notiFrog.setPosition({400, 350});

    create = Button("Create", textColor, font, buttonSize, backgroundColor);
    search = Button("Search", textColor, font, buttonSize, backgroundColor);
    insert = Button("Insert", textColor, font, buttonSize, backgroundColor);
    remove = Button("Remove", textColor, font, buttonSize, backgroundColor);
    access = Button("Access", textColor, font, buttonSize, backgroundColor);
    backButton = Button("Return", textColor, font, {100, 50}, backgroundColor);
    backButton.setOutlineThickness(4);

    sf::Vector2f position = {100, 520};
    buttonBox.setOutlineColor(sf::Color::Black);
    buttonBox.setOutlineThickness(4.f);
    buttonBox.setPosition(position);
    buttonBox.setSize({buttonSize.x, 5 * buttonSize.y});

    create.setPosition(position);
    access.setPosition({position.x, position.y + buttonSize.y});
    search.setPosition({position.x, position.y + 2 * buttonSize.y});
    insert.setPosition({position.x, position.y + 3 * buttonSize.y});
    remove.setPosition({position.x, position.y + 4 * buttonSize.y});
    backButton.setPosition({40, 38});

    std::string subCreateName[] = {"Empty", "Random", "File", "Allocate"};
    sf::Vector2f subSize = {150, 50};
    sf::Vector2f subCreatePos = {position.x + buttonSize.x + 20, position.y};
    for (int i = 0; i < 4; ++i)
    {
        subCreateButton[i] = Button(subCreateName[i], textColor, font, subSize, backgroundColor);
        subCreateButton[i].setPosition(subCreatePos);
        subCreateButton[i].setOutlineThickness(3);
        subCreatePos.x += 170;
    }

    std::string subAccessName[] = {"Update", "Peek"};
    sf::Vector2f subAccessPos = {position.x + buttonSize.x + 20, position.y + buttonSize.y};
    for (int i = 0; i < 2; ++i)
    {
        subAccessButton[i] = Button(subAccessName[i], textColor, font, subSize, backgroundColor);
        subAccessButton[i].setPosition(subAccessPos);
        subAccessButton[i].setOutlineThickness(3);
        subAccessPos.x += 170;
    }

    sf::Vector2f curNodePos = {100, 220};
    for (int i = 0; i < arrMaxSize; ++i)
    {
        nodes[i] = ArrNode("0", textColor, font, 70.f, backgroundColor);
        nodes[i].setPosition(curNodePos);
        nodesPos[i] = curNodePos;
        curNodePos.x += 70;
    }

    for (int i = 0; i < 8; ++i)
    {
        inputBox[i] = Textbox(20, sf::Color::Black, 1);
        inputBox[i].setFont(font);
    }

    // access input box
    inputBox[0].setPosition({subAccessButton[0].getPos().x + 100, position.y + 2 * buttonSize.y + 5});
    inputBox[1].setPosition({subAccessButton[1].getPos().x + 100, position.y + 2 * buttonSize.y + 5});

    // search input box
    inputBox[2].setPosition({search.getPos().x + 210, position.y + 2 * buttonSize.y + 15});

    //  insert input box
    inputBox[3].setPosition({insert.getPos().x + 210, position.y + 3 * buttonSize.y + 15});

    // remove input box
    inputBox[4].setPosition({remove.getPos().x + 210, position.y + 4 * buttonSize.y + 15});

    // allocate input box
    inputBox[5].setPosition({subCreateButton[3].getPos().x + 100, position.y + buttonSize.y + 5});
}

bool DynamicArray::checkHover(sf::Event &ev, sf::RenderWindow &window)
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
    if (access.hoverChangeColor(ev, window))
        return true;

    if (drawSubCreate)
        for (int i = 0; i < 4; ++i)
            if (subCreateButton[i].hoverChangeColor(ev, window))
                return true;
    if (drawSubAcess)
        for (int i = 0; i < 2; ++i)
            if (subAccessButton[i].hoverChangeColor(ev, window))
                return true;

    return false;
}

void DynamicArray::mouseClicked(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
{
    if (backButton.isMouseOnButton(window))
    {
        screenID = 2;
        return;
    }
    if (create.isMouseOnButton(window))
    {
        drawSubCreate = !drawSubCreate;
        drawSubAcess = 0;
    }
    else if (access.isMouseOnButton(window))
    {
        drawSubAcess = !drawSubAcess;
        drawSubCreate = 0;
    }
    else if (search.isMouseOnButton(window))
    {
        isInputVal = 1;
        currInputBox = 2;
        drawSubAcess = drawSubCreate = 0;
    }
    else if (insert.isMouseOnButton(window))
    {
        isInputPos = 1;
        currInputBox = 3;
        drawSubAcess = drawSubCreate = 0;
    }
    else if (remove.isMouseOnButton(window))
    {
        isInputPos = 1;
        currInputBox = 4;
        drawSubAcess = drawSubCreate = 0;
    }

    if (drawSubCreate)
    {
        if (subCreateButton[0].isMouseOnButton(window))
        {
            usedSize = 0;
            SASize = 0;
            for (int i = 0; i < arrMaxSize; ++i)
                nodes[i].setString("0");
        }
        else if (subCreateButton[1].isMouseOnButton(window))
            randomArray();
        else if (subCreateButton[2].isMouseOnButton(window))
            inputFromFile(window, background);
        else if (subCreateButton[3].isMouseOnButton(window))
        {
            isInputVal = 1;
            currInputBox = 5;
        }
    }
    else if (drawSubAcess)
    {
        if (subAccessButton[0].isMouseOnButton(window))
        {
            isInputPos = 1;
            currInputBox = 0;
        }
        else if (subAccessButton[1].isMouseOnButton(window))
        {
            isInputPos = 1;
            currInputBox = 1;
        }
    }
}

void DynamicArray::randomArray()
{
    // SASize = randInt(0, arrMaxSize);
    usedSize = randInt(0, SASize);
    for (int i = 0; i < usedSize; ++i)
    {
        int val = randInt(0, 99);
        nodeVal[i] = val;
        nodes[i].setString(toString(val));
    }

    for (int i = usedSize; i < SASize; ++i)
        nodes[i].setString("0");
}

void DynamicArray::inputFromFile(sf::RenderWindow &window, sf::Sprite &background)
{
    std::ifstream fi;
    fi.open("data.txt");
    if (!fi.is_open())
    {
        noti.setString("Can't found data.txt, please input from data.txt");
        drawNotification(window, background);
        return;
    }
    fi >> usedSize;
    if (usedSize > arrMaxSize)
    {
        usedSize = 0;
        noti.setString("Size must be from 1 to " + toString(arrMaxSize));
        drawNotification(window, background);
        return;
    }
    for (int i = 0; i < usedSize; ++i)
    {
        fi >> nodeVal[i];
        if (nodeVal[i] > 100 || nodeVal[i] < 0)
        {
            usedSize = 0;
            noti.setString("Value must be from 1 to 100");
            drawNotification(window, background);
            return;
        }
        nodes[i].setString(toString(nodeVal[i]));
    }
    for (int i = usedSize; i < SASize; ++i)
        nodes[i].setString("0");

    fi.close();
}

void DynamicArray::allocateArray(sf::RenderWindow &window, sf::Sprite &background)
{
    if (inputVal > arrMaxSize)
    {
        noti.setString("Out of bound");
        drawNotification(window, background);
        return;
    }
    SASize = inputVal;
}

void DynamicArray::handleInput(sf::RenderWindow &window, sf::Sprite &background)
{
    if (isInputPos)
    {
        isInputPos = 0;
        inputPos = stringToInt(inputBox[currInputBox].getText());
        inputBox[currInputBox].setText("");
        if (currInputBox == 1 || currInputBox == 4)
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

void DynamicArray::handleFeature(int pos, sf::RenderWindow &window, sf::Sprite &background)
{
    if (inputVal > 99)
    {
        noti.setString("Value must be from 0 to 99");
        drawNotification(window, background);
        inputVal = 0;
        return;
    }

    switch (pos)
    {
    case 0:
        updatePosAnimation(window, background);
        break;
    case 1:
        peekPosAnimation(window, background);
        break;
    case 2:
        searchAnimation(window, background);
        break;
    case 3:
        addPosAnimation(window, background);
        break;
    case 4:
        delPosAnimation(window, background);
        break;
    case 5:
        allocateArray(window, background);
        break;
    default:
        break;
    }
}

void DynamicArray::handleEvent(sf::Event &ev, sf::RenderWindow &window, int &screenID, sf::Sprite &background)
{
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

    mainDraw(window, background);
    for (int i = 0; i < SASize; ++i)
        nodes[i].draw(window);
}

void DynamicArray::mainDraw(sf::RenderWindow &window, sf::Sprite &background)
{
    window.clear();
    window.draw(background);
    window.draw(buttonBox);
    backButton.drawButton(window);
    create.drawButton(window);
    access.drawButton(window);
    insert.drawButton(window);
    remove.drawButton(window);
    search.drawButton(window);
    window.draw(title);

    if (isInputPos || isInputVal)
    {
        inputBox[currInputBox].drawTo(window);
        if (isInputPos)
            inputTitle.setString("Index: ");
        else
        {
            if (currInputBox == 5)
                inputTitle.setString("Size: ");
            else
                inputTitle.setString("Value: ");
        }
        sf::Vector2f inputPos = inputBox[currInputBox].getPosition();
        inputTitle.setPosition({inputPos.x - 75, inputPos.y});
        window.draw(inputTitle);
    }

    if (drawSubCreate)
        for (int i = 0; i < 4; ++i)
            subCreateButton[i].drawButton(window);

    if (drawSubAcess)
        for (int i = 0; i < 2; ++i)
            subAccessButton[i].drawButton(window);

    // drawing index
    for (int i = 0; i < SASize; ++i)
    {
        sf::Vector2f position;
        position = nodes[i].getPosition();
        index.setPosition({position.x + 25, position.y + 75});
        index.setString(toString(i + 1));
        if (i + 1 > 9)
            index.setPosition({position.x + 20, position.y + 75});
        if (i + 1 == usedSize)
            index.setFillColor(sf::Color::Red);
        else
            index.setFillColor(sf::Color::Black);
        window.draw(index);
        if (i + 1 == usedSize)
        {
            index.setPosition({position.x + 21, position.y - 40});
            index.setString("N");
            window.draw(index);
        }
    }
}

void DynamicArray::drawNotification(sf::RenderWindow &window, sf::Sprite &background)
{
    mainDraw(window, background);
    for (int i = 0; i < SASize; ++i)
        nodes[i].draw(window);
    notiFrog.draw(window);
    window.draw(noti);
    window.display();
    pause_for(1000);
}

void DynamicArray::drawWithHighlight(Highlight feature, int hightlightLine, sf::RenderWindow &window, sf::Sprite &background)
{
    feature.setLine(hightlightLine);
    mainDraw(window, background);
    for (int i = 0; i < SASize; ++i)
        nodes[i].draw(window);
    feature.draw(window);
}

void DynamicArray::searchAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    for (int i = 0; i <= usedSize; ++i)
    {
        // for statement
        drawWithHighlight(searchCode, 1, window, background);
        window.display();
        pause_for(350);
        if (i > 0)
            nodes[i - 1].setBackgroundColor(sf::Color::White);
        if (i == usedSize)
            break;

        nodes[i].setBackgroundColor(sf::Color::Green);
        // if statement
        drawWithHighlight(searchCode, 2, window, background);
        window.display();
        pause_for(350);

        if (nodeVal[i] == inputVal)
        {
            nodes[i].setBackgroundColor(sf::Color::Red);
            drawWithHighlight(searchCode, 3, window, background);
            window.display();
            pause_for(350);

            nodes[i].setBackgroundColor(sf::Color::White);
            noti.setString("Found at index " + toString(i + 1));

            drawNotification(window, background);
            return;
        }
    }

    drawWithHighlight(searchCode, 4, window, background);
    window.display();
    pause_for(350);
    noti.setString("Not found value " + toString(inputVal));
    drawNotification(window, background);
    return;
}
void DynamicArray::addPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    if (SASize == arrMaxSize || inputPos < 0 || inputPos > usedSize || inputPos > SASize)
    {
        noti.setString("Out of bound");
        drawNotification(window, background);
        return;
    }

    drawWithHighlight(addPosCode, 1, window, background);
    window.display();
    pause_for(350);
    if (usedSize == SASize)
        SASize++;
    drawWithHighlight(addPosCode, 1, window, background);
    window.display();
    pause_for(350);

    ++usedSize;
    drawWithHighlight(addPosCode, 2, window, background);
    window.display();
    pause_for(350);

    for (int i = usedSize - 1; i >= inputPos; --i)
    {
        // for statement
        drawWithHighlight(addPosCode, 3, window, background);
        window.display();
        pause_for(350);

        nodes[i + 1].setBackgroundColor(sf::Color::White);
        if (i == inputPos)
            break;
        nodes[i].setBackgroundColor(sf::Color::Green);

        // change statement
        nodeVal[i] = nodeVal[i - 1];
        nodes[i].setString("");
        drawWithHighlight(addPosCode, 4, window, background);
        window.display();
        pause_for(350);

        nodes[i].setString(toString(nodeVal[i]));
        drawWithHighlight(addPosCode, 4, window, background);
        window.display();
        pause_for(350);
    }

    nodeVal[inputPos] = inputVal;
    nodes[inputPos].setBackgroundColor(sf::Color::Green);
    nodes[inputPos].setString("");
    drawWithHighlight(addPosCode, 5, window, background);
    window.display();
    pause_for(350);

    nodes[inputPos].setString(toString(nodeVal[inputPos]));
    drawWithHighlight(addPosCode, 5, window, background);
    window.display();
    pause_for(350);

    nodes[inputPos].setBackgroundColor(sf::Color::White);
}
void DynamicArray::delPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    if (inputPos >= usedSize || inputPos < 0)
    {
        noti.setString("Out of bound");
        drawNotification(window, background);
        return;
    }
    for (int i = inputPos; i < usedSize; ++i)
    {
        // for statement
        drawWithHighlight(delPosCode, 1, window, background);
        window.display();
        pause_for(430);

        if (i > 0)
            nodes[i - 1].setBackgroundColor(sf::Color::White);
        if (i == usedSize - 1)
            break;

        // change statement
        nodes[i].setBackgroundColor(sf::Color::Green);
        nodeVal[i] = nodeVal[i + 1];
        nodes[i].setString("");
        drawWithHighlight(delPosCode, 2, window, background);
        window.display();
        pause_for(430);

        nodes[i].setString(toString(nodeVal[i]));
        drawWithHighlight(delPosCode, 2, window, background);
        window.display();
        pause_for(430);
    }

    --usedSize;
    drawWithHighlight(delPosCode, 3, window, background);
    window.display();
    pause_for(430);
}
void DynamicArray::updatePosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    if (inputPos >= usedSize || inputPos < 0)
    {
        noti.setString("Out of bound");
        drawNotification(window, background);
        return;
    }
    nodeVal[inputPos] = inputVal;
    nodes[inputPos].setBackgroundColor(sf::Color::Green);
    nodes[inputPos].setString("");
    drawWithHighlight(updatePosCode, 1, window, background);
    window.display();
    pause_for(500);

    nodes[inputPos].setString(toString(inputVal));
    drawWithHighlight(updatePosCode, 1, window, background);
    window.display();
    pause_for(500);

    nodes[inputPos].setBackgroundColor(sf::Color::White);
}

void DynamicArray::peekPosAnimation(sf::RenderWindow &window, sf::Sprite &background)
{
    --inputPos;
    if (inputPos >= usedSize || inputPos < 0)
    {
        noti.setString("Out of bound");
        drawNotification(window, background);
        return;
    }
    nodes[inputPos].setBackgroundColor(sf::Color::Green);
    drawWithHighlight(accessPosCode, 1, window, background);
    window.display();
    pause_for(500);
    nodes[inputPos].setBackgroundColor(sf::Color::White);

    noti.setString("Value at position " + toString(inputPos + 1) + " : " + toString(nodeVal[inputPos]));
    drawNotification(window, background);
}

#ifndef _menu_h
#define _menu_h
#include <SFML/Graphics.hpp>
#include "Components/Button.hpp"
class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
private:
    
};
#endif

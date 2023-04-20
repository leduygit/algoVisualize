#ifndef _image_h_
#define _image_h_
#include <SFML/Graphics.hpp>
class Image
{
private:
    sf::Texture texture;
    sf::Sprite image;
public:
    Image(std::string file = "");
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
    void loadTexture(std::string file);
    sf::Vector2f getPosition();
};


#endif
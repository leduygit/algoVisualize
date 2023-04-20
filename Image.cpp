#include "Image.hpp"

Image::Image(std::string file)
{
    if (file == "") return;
    texture.loadFromFile(file);
    image.setTexture(texture);
}

void Image::loadTexture(std::string file)
{
    texture.loadFromFile(file);
    image.setTexture(texture);
}

void Image::setPosition(sf::Vector2f pos)
{
    image.setPosition(pos);
}

void Image::draw(sf::RenderWindow &window)
{
    window.draw(image);
}

sf::Vector2f Image::getPosition()
{
    return image.getPosition();
}
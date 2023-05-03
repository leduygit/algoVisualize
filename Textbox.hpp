#ifndef _Textbox_h_
#define _Textbox_h_
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox(int size = 0, sf::Color color = sf::Color::Black, bool sel = 1);

	// Make sure font is passed by reference:
	void setFont(sf::Font &fonts);
	void setPosition(sf::Vector2f point);

	// set text
	void setText(std::string str);

	// Set char limits:
	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	// Change selected state:
	void setSelected(bool sel);

	std::string getText();

	void drawTo(sf::RenderWindow &window);

	// Function for event loop:
	bool typedOn(sf::Event input);

	// Delete the last character of the text:
	void deleteLastChar();

	// Get user input:
	void inputLogic(int charTyped);

	sf::Vector2f getPosition();

private:
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	
};

#endif
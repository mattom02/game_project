#include "../include/DeathScreen.h"

DeathScreen::DeathScreen (float width, float height, int size) {
	font.loadFromFile("font.ttf");

	text[0].setFont(font);
	text[0].setCharacterSize(size * 1.5);
	text[0].setFillColor(sf::Color::White);
	text[0].setPosition((width / 2) - 130, height / 2);
	text[0].setString("You died");

	text[1].setFont(font);
	text[1].setCharacterSize(size);
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition((width / 2) - (width / 3.75), (height / 2) + (2 * size));
	text[1].setString("Press ENTER to get back to the menu\n                   or ESC to exit");
}

void DeathScreen::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	for (auto& i : text) {
		target.draw(i, state);
	}
}
#include "ScoreText.h"

ScoreText::ScoreText(float X, float Y, int size) {
	font.loadFromFile("font.ttf");
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::White);
	text.setPosition(X, Y);
	text.setString(std::to_string(totalScore));
}

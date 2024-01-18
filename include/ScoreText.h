#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class ScoreText : public sf::Drawable
{
public:
	ScoreText(float X, float Y, int size);

	void updateScore() { totalScore++; text.setString(std::to_string(totalScore));}

	int getScore() { return totalScore; }
private:
	int totalScore = 0;

	sf::Text text;

	sf::Font font;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override { target.draw(text, state); }
};


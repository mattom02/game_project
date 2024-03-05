#pragma once
#include "SFML/Graphics.hpp"

class DeathScreen : public sf::Drawable
{
public:
	DeathScreen(float width, float height, int size);
private:
	sf::Text text[2];
	sf::Font font;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};


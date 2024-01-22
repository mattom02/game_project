#pragma once
#include "SFML/Graphics.hpp"

class MainMenu : public sf::Drawable
{
public:
	MainMenu(float width, float height, int size);

	void moveUpMain();

	void moveDownMain();

	void moveUpPlay();

	void moveDownPlay();

	void selectPlay() { isPlaySelected = true; }

	void unselectPlay();

	bool getIsPlaySelected() const { return isPlaySelected; }

	int getSelectedIndexMain() const { return selectedIndexMain; }

	int getSelectedIndexPlay() const { return selectedIndexPlay; }
private:
	sf::Text selectableBarsMain[2];
	sf::Text selectableBarsPlay[4];

	sf::Font font;

	int selectedIndexMain = 0;
	int selectedIndexPlay = 0;

	bool isPlaySelected = false;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};


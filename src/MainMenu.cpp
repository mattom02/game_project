#include "../include/MainMenu.h"

MainMenu::MainMenu(float width, float height, int size) {
	font.loadFromFile("font.ttf");

	selectableBarsMain[0].setFont(font);
	selectableBarsMain[0].setCharacterSize(size);
	selectableBarsMain[0].setFillColor(sf::Color::Red);
	selectableBarsMain[0].setPosition(width / 2, height / 2);
	selectableBarsMain[0].setString("Play");

	selectableBarsMain[1].setFont(font);
	selectableBarsMain[1].setCharacterSize(size);
	selectableBarsMain[1].setFillColor(sf::Color::White);
	selectableBarsMain[1].setPosition(width / 2, (height / 2) + (2 * size));
	selectableBarsMain[1].setString("Exit");

	selectableBarsPlay[0].setFont(font);
	selectableBarsPlay[0].setCharacterSize(size);
	selectableBarsPlay[0].setFillColor(sf::Color::Red);
	selectableBarsPlay[0].setPosition(width / 2, height / 2);
	selectableBarsPlay[0].setString("Easy");

	selectableBarsPlay[1].setFont(font);
	selectableBarsPlay[1].setCharacterSize(size);
	selectableBarsPlay[1].setFillColor(sf::Color::White);
	selectableBarsPlay[1].setPosition(width / 2, (height / 2) + (2 * size));
	selectableBarsPlay[1].setString("Medium");

	selectableBarsPlay[2].setFont(font);
	selectableBarsPlay[2].setCharacterSize(size);
	selectableBarsPlay[2].setFillColor(sf::Color::White);
	selectableBarsPlay[2].setPosition(width / 2, (height / 2) + (4 * size));
	selectableBarsPlay[2].setString("Hard");

	selectableBarsPlay[3].setFont(font);
	selectableBarsPlay[3].setCharacterSize(size);
	selectableBarsPlay[3].setFillColor(sf::Color::White);
	selectableBarsPlay[3].setPosition(width / 2, (height / 2) + (6 * size));
	selectableBarsPlay[3].setString("Back");
}

void MainMenu::unselectPlay() { 
	isPlaySelected = false; 
	selectedIndexPlay = 0; 
	selectableBarsPlay[3].setFillColor(sf::Color::White);
	selectableBarsPlay[2].setFillColor(sf::Color::White);
	selectableBarsPlay[1].setFillColor(sf::Color::White);
	selectableBarsPlay[0].setFillColor(sf::Color::Red);
}

void MainMenu::moveUpMain() {
	if (selectedIndexMain > 0) {
		selectableBarsMain[selectedIndexMain].setFillColor(sf::Color::White);
		selectedIndexMain--;
		selectableBarsMain[selectedIndexMain].setFillColor(sf::Color::Red);
	}
}

void MainMenu::moveDownMain() {
	if (selectedIndexMain < 1) {
		selectableBarsMain[selectedIndexMain].setFillColor(sf::Color::White);
		selectedIndexMain++;
		selectableBarsMain[selectedIndexMain].setFillColor(sf::Color::Red);
	}
}

void MainMenu::moveUpPlay() {
	if (selectedIndexPlay > 0) {
		selectableBarsPlay[selectedIndexPlay].setFillColor(sf::Color::White);
		selectedIndexPlay--;
		selectableBarsPlay[selectedIndexPlay].setFillColor(sf::Color::Red);
	}
}

void MainMenu::moveDownPlay() {
	if (selectedIndexPlay < 3) {
		selectableBarsPlay[selectedIndexPlay].setFillColor(sf::Color::White);
		selectedIndexPlay++;
		selectableBarsPlay[selectedIndexPlay].setFillColor(sf::Color::Red);
	}
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	if (selectedIndexMain == 0 and isPlaySelected) {
		for (auto& i : selectableBarsPlay) {
			target.draw(i, state);
		}
	}
	else {
		for (auto& i : selectableBarsMain) {
			target.draw(i, state);
		}
	}
}
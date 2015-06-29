#pragma once
#include "GameObject.h"
#include "Food.h"
#include "Ghostclass.h"

class Score : public GameObject
{
public:
	Score();
	~Score();

	//methods
	void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);
	void Draw(sf::RenderWindow &window);

private:
	sf::Font font;
	sf::Vector2f pos;
	sf::Text scoreLabel;
	sf::Text bestScoreLabel;
	int bonusScore;
	int bestScore;
};
/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: This is Score class. This class draws and updates the score.
*/

#include "Score.h"

void Score::Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor)
{
	Food* food = dynamic_cast<Food*>(GameController::GetGameObjectManager().Get("NFood"));
	Ghostclass* inky = dynamic_cast<Ghostclass*>(GameController::GetGameObjectManager().Get("_Inky"));
	Ghostclass* blinky = dynamic_cast<Ghostclass*>(GameController::GetGameObjectManager().Get("_Blinky"));
	Ghostclass* pinky = dynamic_cast<Ghostclass*>(GameController::GetGameObjectManager().Get("_Pinky"));
	Ghostclass* clyde = dynamic_cast<Ghostclass*>(GameController::GetGameObjectManager().Get("_Clyde"));
	if (inky->GetEaten() || blinky->GetEaten() || pinky->GetEaten() || clyde->GetEaten())
	{
		bonusScore += 10;
		inky->SetEaten(false);
		blinky->SetEaten(false);
		pinky->SetEaten(false);
		clyde->SetEaten(false);
	}
	int calc = (bonusScore + *food->getScore());
	std::string score = "Score " + std::to_string(calc);
	scoreLabel.setString(score);
	if (calc > bestScore)
	{
		bestScore = calc;
		bestScoreLabel.setString("HS " + std::to_string(bestScore));
	}

}

void Score::ResetBonus()
{
	bonusScore = 0;
}

void Score::Draw(sf::RenderWindow &window)
{
	window.draw(scoreLabel);
	window.draw(bestScoreLabel);
}

Score::Score()
{
	sf::Color color(255, 255, 0);
	pos.x = 10;
	pos.y = 497;
	font.loadFromFile("assets/8-BIT WONDER.ttf");
	scoreLabel.setPosition(pos);
	scoreLabel.setColor(color);
	scoreLabel.setFont(font);
	bestScoreLabel.setPosition(pos.x + 265, pos.y);
	bestScoreLabel.setColor(color);
	bestScoreLabel.setFont(font);	
}

Score::~Score()
{

}
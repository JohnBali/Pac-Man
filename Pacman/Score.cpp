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
	std::string score = "Score " + std::to_string(bonusScore + *food->getScore());
	scoreLabel.setString(score);
	bestScoreLabel.setString(std::to_string(bestScore));
	if (score > std::to_string(bestScore))
	{
		bestScore = std::stoi(score);
	}
}

void Score::Draw(sf::RenderWindow &window)
{
	window.draw(scoreLabel);
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
	bonusScore = 0;
}

Score::~Score()
{

}
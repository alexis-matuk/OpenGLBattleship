#include "OpponentMapSceneTransitioner.hpp"

void OpponentMapSceneTransitioner::toTransition()
{
	std::cout << "Going to my map being hit" << std::endl;
	myMapBeingHitScene();
}
void OpponentMapSceneTransitioner::fromTransition() {
	std::cout << "Going to hitting their map" << std::endl;
	inGameScene();
}
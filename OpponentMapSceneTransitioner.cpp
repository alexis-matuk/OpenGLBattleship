/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "OpponentMapSceneTransitioner.hpp"

/*
  Transition to your map being hit scene
*/
void OpponentMapSceneTransitioner::toTransition()
{
	std::cout << "Going to my map being hit" << std::endl;
	myMapBeingHitScene();
}

/*
  Transition to you attacking the opponent's map
*/
void OpponentMapSceneTransitioner::fromTransition() {
	std::cout << "Going to hitting their map" << std::endl;
	inGameScene();
}
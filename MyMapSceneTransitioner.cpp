/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "MyMapSceneTransitioner.hpp"

/*
  Specify to which scene should we transition  
*/
void MyMapSceneTransitioner::toTransition()
{
	std::cout << "Going to hitting their map" << std::endl;    
	inGameScene();
}

void MyMapSceneTransitioner::fromTransition() {

}
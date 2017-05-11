/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "OtherDestroyListener.hpp"

/*
  Server callback for when the opponent misses a shot
*/
void OtherDestroyListener::onMiss(int row, int col) const
{
	std::cout << "=== They missed my ship === " << std::endl;
	sceneTransitioner->fromTransition();
	Tile * _hitTile = map->getGrid()[col][row];
	_hitTile->updateState(Tile::State::FREE);
	missile = new Missile(_hitTile);
	while(shooting)
	{
		;
	}    
	shooting = true;
	sleep(1);
	sceneTransitioner->toTransition();
	shooting = false;  
}

/*
  Server callback for when the opponent hits a ship
*/
void OtherDestroyListener::onHit(int row, int col, bool destroyed) const 
{
	std::cout << "=== They hit my ship ===" << std::endl;
	sceneTransitioner->fromTransition(); 
	Tile * _hitTile = map->getGrid()[col][row];
	_hitTile->updateState(Tile::State::USED);
	missile = new Missile(_hitTile);
	while(shooting)
	{
		;
	}
	if(!destroyed)
	{ 
		shooting = true; 
		sleep(1);         
		sceneTransitioner->toTransition();
		shooting = false;
	}  
}

/*
  Server callback for when the opponent destroys a ship
*/
void OtherDestroyListener::onDestroy(char shipId, int row1, int col1, int row2, int col2) {
	std::cout << "==== They destroyed my ship ===" << std::endl;  
	shooting = true;
	Ship * hitShip = map->getShipFromId(shipId);
	hitShip->setDrawing(true);
	shipsDestroyed.push_back(hitShip);
	sleep(1);
	sceneTransitioner->toTransition();
	shooting = false;  
}
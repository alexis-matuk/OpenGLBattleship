/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "MyDestroyListener.hpp"
/*
  Set map  
*/
void MyDestroyListener::setMap(Map * _map)
{
	map = _map;
}  

/*
  Get map  
*/
Map * MyDestroyListener::getMap()
{
	return map;
}

/*
    Set other map.
    We need a reference to both.
*/
void MyDestroyListener::setOtherMap(Map * _otherMap)
{
	otherMap = _otherMap;
}

/*
  Get other map  
*/
Map * MyDestroyListener::getOtherMap()
{
	return otherMap;
}

/*
    Set a scene transitioner.
    Depending on who goes first and wbat the event is, we need to change between
    	different scenes
*/
void MyDestroyListener::setTransitioner(SceneTransitioner *transitioner) {
	sceneTransitioner = transitioner;
}

/*
    Get the list of ships destroyed
*/
std::vector<Ship*> MyDestroyListener::getShipsDestroyed()
{
	return shipsDestroyed;
}

/*
  Server callback for when you destroy one of their ships  
*/
void MyDestroyListener::onDestroy(char shipId, int row1, int col1, int row2, int col2) {
	std::cout << "id: " << shipId << "row1: " << row1 << "row2: " << row2 << "col1: " << col1 << "col2: " << col2 << std::endl;                
	std::cout << "==== I destroyed their ship ===" << std::endl; 
	shooting = true;
	Tile * tileToClip = map->getGrid()[col1][row1];    
	Ship * shipToClip = map->getShipFromId(shipId);     
	shipToClip->setDrawing(true);  
	shipsDestroyed.push_back(shipToClip);    
	Map::Direction shipDir;
	if(row1 == row2)
		shipDir = Map::Direction::LEFT_RIGHT;
	else
		shipDir = Map::Direction::TOP_BOTTOM;    
	map->addShipToList(shipToClip); 
	map->UIClipShip(shipDir, shipToClip, tileToClip);    
	sleep(1);     
	sceneTransitioner->toTransition();    
	shooting = false;   
}

/*
  Server callback for when you miss one of their ships  
*/
void MyDestroyListener::onMiss(int row, int col) const {
	std::cout << "=== I missed their ship === " << std::endl;
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
  Server callback for when you hit one of their ships  
*/
void MyDestroyListener::onHit(int row, int col, bool destroyed) const {
	std::cout << "=== I hit their ship ===" << std::endl;
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
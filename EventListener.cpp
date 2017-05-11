/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "EventListener.hpp"

/*
	Set map for the event listener	
*/
void EventListener::setMap(Map * _map)
{
	map = _map;
}

/*
	Callback from server that tells the eventlistener to shoot	
*/
void EventListener::shoot(int &row, int &col) {
	while (x == -1 || y == -1) {
		;
	}
	row = x;
	col = y;
	x = -1;
	y = -1;
}

/*
	Set position of the shot tile
*/
void EventListener::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

/*
	Callback from server to know when to send your ships
*/
void EventListener::sendShips(char ships[ROWS][COLS]) {
	while(!map->getReadyToSend())
	{
	;//BLOCK
	}
	char ** _ships = map->exportMapToServer();
	for (int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			ships[i][j] = _ships[i][j];
		}
	}
}


void EventListener::connected()
{

}

/*
	Function that tells you when the server is ready
*/
void EventListener::ready()
{
	waitingForServer = false;
}

/*
	Function that tells you if you lost	
*/
void EventListener::lost()
{
	printf("LOST\n");
	UI->findPanelByName("result")->setContent("YOU LOST :C");
	UI->findPanelByName("result")->setColor(255, 0, 0);
	Scene->changeScene("Ending");
}

/*
	Function that tells you if you won
*/
void EventListener::won()
{
	printf("WON\n");
	UI->findPanelByName("result")->setContent("YOU WON!!");
	UI->findPanelByName("result")->setColor(255, 255, 0);
	Scene->changeScene("Ending");
}

/*
	Callback function that tells you if you attack first
*/
void EventListener::onAttack()
{
	hasOrder = true;
	attacking = true;
	defending = false;
}

/*
	Callback functio that tells you if you defend first
*/
void EventListener::onDefend()
{
	hasOrder = true;
	defending = true;
	attacking = false;    
}
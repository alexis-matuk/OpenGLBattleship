#include "EventListener.hpp"

void EventListener::setMap(Map * _map)
{
	map = _map;
}

void EventListener::shoot(int &row, int &col) {
	while (x == -1 || y == -1) {
		;
	}
	row = x;
	col = y;
	x = -1;
	y = -1;
}

void EventListener::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}


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

void EventListener::ready()
{
	waitingForServer = false;
}

void EventListener::lost()
{
	UI->findPanelByName("result")->setContent("YOU LOST :C");
	UI->findPanelByName("result")->setColor(255, 0, 0);
	Scene->changeScene("Ending");
}

void EventListener::won()
{
	UI->findPanelByName("result")->setContent("YOU WON!!");
	UI->findPanelByName("result")->setColor(255, 255, 0);
	Scene->changeScene("Ending");
}

void EventListener::onAttack()
{
	hasOrder = true;
	attacking = true;
	defending = false;
}

void EventListener::onDefend()
{
	hasOrder = true;
	defending = true;
	attacking = false;    
}
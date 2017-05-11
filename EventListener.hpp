#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "HeaderInclude.hpp"
#include "aggregateFuncs.hpp"
#include "ClientServerBattleship/server/ClientEventListener.hpp"
#include "Map.hpp"
#include "UIHandler.hpp"
#include "SceneManager.hpp"
class EventListener : public ClientEventListener {
private:
	int x = -1;
	int y = -1;
	Map * map;
public:
	void setMap(Map * _map);
	virtual void shoot(int &row, int &col);
	void setPosition(int x, int y);
	virtual void sendShips(char ships[ROWS][COLS]);
	virtual void connected();
	virtual void ready();
	virtual void lost();
	virtual void won();
	virtual void onAttack();
	virtual void onDefend();
};

#endif 
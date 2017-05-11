#ifndef MYDESTROYLISTENER_H
#define MYDESTROYLISTENER_H
#include "HeaderInclude.hpp"
#include "ClientServerBattleship/board/DestroyListener.hpp"
#include "SceneTransitioner.hpp"
#include "Missile.hpp"
#include "Map.hpp"
class MyDestroyListener : public DestroyListener {
protected:
	Map * map;
	Map * otherMap;
	SceneTransitioner *sceneTransitioner;	
	std::vector<Ship*> shipsDestroyed;
public: 	
	void setMap(Map * _map);
	Map * getMap();
	void setOtherMap(Map * _otherMap);
	Map * getOtherMap();
	void setTransitioner(SceneTransitioner *transitioner);
	std::vector<Ship*> getShipsDestroyed();
	virtual void onDestroy(char shipId, int row1, int col1, int row2, int col2);
	virtual void onMiss(int row, int col) const;
	virtual void onHit(int row, int col, bool destroyed) const;
};

#endif
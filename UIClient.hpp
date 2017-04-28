#ifndef UIClient_H
#define UIClient_H

#include "ClientServerBattleship/board/DestroyListener.hpp"
#include "ClientServerBattleship/server/ClientEventListener.hpp"
#include "ClientServerBattleship/server/Client.hpp"

#include "Map.hpp"

class SceneTransitioner {
public:
	virtual void transition() = 0;
};

class OpponentMapSceneTransitioner : public SceneTransitioner {
public:
	virtual void transition() {
		inGameScene();
	}
};

class MyMapSceneTransitioner : public SceneTransitioner {
public:
	virtual void transition() {
		pickingScene();
	}
};

class MyDestroyListener : public DestroyListener {
private:
  //VAMOS A NECESITAR DOS TRANSITIONERS
  //TRANSICIÓN -> MISIL -> TRANSICIÓN
	Map * map;
	SceneTransitioner *sceneTransitioner;	
 public: 	
 	void setMap(Map * _map)
 	{
 		map = _map;
 	}

 	void setTransitioner(SceneTransitioner *transitioner) {
 		sceneTransitioner = transitioner;
 	}

  virtual void onDestroy(char shipId, int row1, int col1, int row2, int col2) const {
    std::cout << "Your ship was destroyed " << shipId << " located on (" << row1 << ", " << col1 << ") (" << row2 << ", " << col2 << ")\n";
  }
  virtual void onMiss(int row, int col) const {  	
    Tile * _hitTile = map->getGrid()[col][row];
    _hitTile->updateState(Tile::State::FREE);  
    missile = new Missile(_hitTile);
    while(shooting)
    {
    	;
    }    
    sleep(3);    	
    sceneTransitioner->transition();
  }
  virtual void onHit(int row, int col) const {
    Tile * _hitTile = map->getGrid()[col][row];
    _hitTile->updateState(Tile::State::USED);
    missile = new Missile(_hitTile);
    while(shooting)
    {
    	;
    }    
    sleep(3);    	    
    sceneTransitioner->transition();
  }
};

class EventListener : public ClientEventListener {
 private:
 	int x = -1;
 	int y = -1;
 	Map * map;
 public:
 	void setMap(Map * _map)
 	{
 		map = _map;
 	}
  virtual void shoot(int &row, int &col) {
    while (x == -1 || y == -1) {
    	;
    }
    row = x;
    col = y;
    x = -1;
    y = -1;
  }

  void setPosition(int x, int y) {
  	this->x = x;
  	this->y = y;
  }

  virtual void sendShips(char ships[ROWS][COLS]) {
  	while(!map->everyShipPlaced())
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
};

class UIClient : public Client{
private:
	EventListener eventListener;
	MyDestroyListener myDestroyListener;
	MyDestroyListener oDestroyListener;
	OpponentMapSceneTransitioner myMapToTheirMap;
	MyMapSceneTransitioner theirMapToMyMap;
public:
	UIClient(char const *port, char const *hostname, struct addrinfo *hints, Map * _myMap, Map * _opponentMap) : Client(port, hostname, hints, &eventListener, &myDestroyListener, &oDestroyListener) {
	    eventListener.setMap(_myMap);
	    myDestroyListener.setMap(_opponentMap);
	    oDestroyListener.setMap(_myMap);	    
	    myDestroyListener.setTransitioner(&myMapToTheirMap);
	    oDestroyListener.setTransitioner(&theirMapToMyMap);
	 }
	 EventListener & getEventListener(){
	 	return eventListener;
	 }
};

#endif //UIClient_H
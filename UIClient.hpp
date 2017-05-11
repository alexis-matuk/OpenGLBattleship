#ifndef UIClient_H
#define UIClient_H

#include "ClientServerBattleship/server/Client.hpp"
#include "Map.hpp"
#include "SceneTransitioner.hpp"
#include "OpponentMapSceneTransitioner.hpp"
#include "MyMapSceneTransitioner.hpp"
#include "MyDestroyListener.hpp"
#include "OtherDestroyListener.hpp"
#include "EventListener.hpp"

class UIClient : public Client{
private:  
	EventListener eventListener;
	MyDestroyListener myDestroyListener;
	OtherDestroyListener oDestroyListener;
	OpponentMapSceneTransitioner myMapToTheirMap;
	MyMapSceneTransitioner theirMapToMyMap;
  std::vector<glm::vec3> enemyPositions;
  std::vector<glm::vec3> friendlyPositions;
  int ww;
  int wh;
  bool setEnemy = false;
  bool setFriendly = false;
public:
	UIClient(char const *port, char const *hostname, struct addrinfo *hints, Map * _myMap, Map * _opponentMap);
	 EventListener & getEventListener();
   void initEnemyPositions();
   void updateEnemyPositions();
   void initFriendlyPositions();
   void updateFriendlyPositions();
   void setup();
   void setww(int _ww);
   void setwh(int _wh);
   void drawFriendlyShips();
   void drawEnemyShips();
};

#endif //UIClient_H
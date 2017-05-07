#ifndef UIClient_H
#define UIClient_H

#include "ClientServerBattleship/board/DestroyListener.hpp"
#include "ClientServerBattleship/server/ClientEventListener.hpp"
#include "ClientServerBattleship/server/Client.hpp"

#include "Map.hpp"

class SceneTransitioner {
public:
  virtual void toTransition() = 0;
	virtual void fromTransition() = 0;
};

class OpponentMapSceneTransitioner : public SceneTransitioner {
public:
  virtual void toTransition()
  {
    myMapBeingHitScene();
  }
	virtual void fromTransition() {
		inGameScene();
	}
};

class MyMapSceneTransitioner : public SceneTransitioner {
public:
	virtual void toTransition()
  {
    inGameScene();
  }
  virtual void fromTransition() {
    // pickingScene();
  }
};

class MyDestroyListener : public DestroyListener {
protected:
  //VAMOS A NECESITAR DOS TRANSITIONERS
  //TRANSICIÓN -> MISIL -> TRANSICIÓN
	Map * map;
  Map * otherMap;
	SceneTransitioner *sceneTransitioner;	
  std::vector<Ship*> shipsDestroyed;
 public: 	
 	void setMap(Map * _map)
 	{
 		map = _map;
 	}  

  Map * getMap()
  {
    return map;
  }

  void setOtherMap(Map * _otherMap)
  {
    otherMap = _otherMap;
  }

  Map * getOtherMap()
  {
    return otherMap;
  }

 	void setTransitioner(SceneTransitioner *transitioner) {
 		sceneTransitioner = transitioner;
 	}

  std::vector<Ship*> getShipsDestroyed()
  {
    return shipsDestroyed;
  }

  virtual void onDestroy(char shipId, int row1, int col1, int row2, int col2) {      
      shooting = true;
      Ship * hitShip = otherMap->getShipFromId(shipId);
      hitShip->setDrawing(true);
      shipsDestroyed.push_back(hitShip);
      std::cout << "Adding destroyed ship: " << hitShip->getName() << std::endl;
      sleep(1);
      sceneTransitioner->toTransition();
      shooting = false;
  }

  virtual void onMiss(int row, int col) const {
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
  virtual void onHit(int row, int col, bool destroyed) const {
    std::cout << "New hit at row, col, destroyed: " << row << " " << col << " " << destroyed << " " << std::endl;
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
};

class OtherDestroyListener : public MyDestroyListener {
private:
  //VAMOS A NECESITAR DOS TRANSITIONERS
  //TRANSICIÓN -> MISIL -> TRANSICIÓN  
 public:  
  virtual void onDestroy(char shipId, int row1, int col1, int row2, int col2) {
    shooting = true;
    Tile * tileToClip = otherMap->getGrid()[col1][row1];
    Ship * shipToClip = otherMap->getShipFromId(shipId);    
    shipToClip->setDrawing(true);
    shipsDestroyed.push_back(shipToClip);
    std::cout << "Adding destroyed ship: " << shipToClip->getName() << std::endl;
    Map::Direction shipDir;
    if(row1 == row2)
      shipDir = Map::Direction::LEFT_RIGHT;
    else
      shipDir = Map::Direction::TOP_BOTTOM;
    otherMap->addShipToList(shipToClip);
    otherMap->UIClipShip(shipDir, shipToClip, tileToClip);
    sleep(1);     
    sceneTransitioner->toTransition();
    shooting = false;
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

  virtual void connected()
  {

  }

  virtual void ready()
  {
    waitingForServer = false;
  }

  virtual void lost()
  {
    UI->findPanelByName("result")->setContent("YOU LOST :C");
    UI->findPanelByName("result")->setColor(255, 0, 0);
    Scene->changeScene("Ending");
  }

  virtual void won()
  {
    UI->findPanelByName("result")->setContent("YOU WON!!");
    UI->findPanelByName("result")->setColor(255, 255, 0);
    Scene->changeScene("Ending");
  }

  virtual void onAttack()
  {
    hasOrder = true;
    attacking = true;
    defending = false;
  }

  virtual void onDefend()
  {
    hasOrder = true;
    defending = true;
    attacking = false;    
  }

};

class UIClient : public Client{
private:  
	EventListener eventListener;
	MyDestroyListener myDestroyListener;
	OtherDestroyListener oDestroyListener;
	OpponentMapSceneTransitioner myMapToTheirMap;
	MyMapSceneTransitioner theirMapToMyMap;
  std::vector<glm::vec3> enemyPositions; //left
  std::vector<glm::vec3> friendlyPositions; //right
  int ww;
  int wh;
  bool setEnemy = false;
  bool setFriendly = false;
public:
	UIClient(char const *port, char const *hostname, struct addrinfo *hints, Map * _myMap, Map * _opponentMap) : Client(port, hostname, hints, &eventListener, &myDestroyListener, &oDestroyListener) {
	    eventListener.setMap(_myMap);

      myDestroyListener.setMap(_opponentMap);   
	    myDestroyListener.setOtherMap(_myMap);	           
	    myDestroyListener.setTransitioner(&myMapToTheirMap);

      oDestroyListener.setMap(_myMap);   
      oDestroyListener.setOtherMap(_opponentMap);   
	    oDestroyListener.setTransitioner(&theirMapToMyMap);      
	 }
	 EventListener & getEventListener(){
	 	return eventListener;
	 }

   void initEnemyPositions()
   {    
    float area = (float) 7*wh/8 - (float) wh/3;
    float xarea = (float) ww/2;

    glm::vec3 pos_1 = screenToWorldPoint(ww/4, 7*wh/8 - area/5);        
    glm::vec3 pos_2 = screenToWorldPoint(ww/4, 7*wh/8 - 2*area/5);    
    glm::vec3 pos_3 = screenToWorldPoint(ww/4, 7*wh/8 - 3*area/5);    
    glm::vec3 pos_4 = screenToWorldPoint(ww/4, 7*wh/8 - 4*area/5);    
    glm::vec3 pos_5 = screenToWorldPoint(ww/4, 7*wh/8 - 5*area/5);    
    glBegin(GL_POINTS);
      glColor3f(0,1,0);
      glVertex3f(ww/4, 7*wh/8 - area/5, 0);
    glEnd();
    enemyPositions.push_back(glm::vec3(pos_5.x, pos_5.y, pos_5.z));
    enemyPositions.push_back(glm::vec3(pos_4.x, pos_4.y, pos_4.z));
    enemyPositions.push_back(glm::vec3(pos_3.x, pos_3.y, pos_3.z));
    enemyPositions.push_back(glm::vec3(pos_2.x, pos_2.y, pos_2.z));
    enemyPositions.push_back(glm::vec3(pos_1.x, pos_1.y, pos_1.z));
   }

   void updateEnemyPositions()
   {
    float area = (float) 7*wh/8 - (float) wh/3;
    float xarea = (float) ww/2;

    glm::vec3 pos_1 = screenToWorldPoint(ww/4, 7*wh/8 - area/5);        
    glm::vec3 pos_2 = screenToWorldPoint(ww/4, 7*wh/8 - 2*area/5);    
    glm::vec3 pos_3 = screenToWorldPoint(ww/4, 7*wh/8 - 3*area/5);    
    glm::vec3 pos_4 = screenToWorldPoint(ww/4, 7*wh/8 - 4*area/5);    
    glm::vec3 pos_5 = screenToWorldPoint(ww/4, 7*wh/8 - 5*area/5);    
    glBegin(GL_POINTS);
      glColor3f(0,1,0);
      glVertex3f(ww/4, 7*wh/8 - area/5, 0);
    glEnd();
    enemyPositions[0] = (glm::vec3(pos_5.x, pos_5.y, pos_5.z));
    enemyPositions[1] = (glm::vec3(pos_4.x, pos_4.y, pos_4.z));
    enemyPositions[2] = (glm::vec3(pos_3.x, pos_3.y, pos_3.z));
    enemyPositions[3] = (glm::vec3(pos_2.x, pos_2.y, pos_2.z));
    enemyPositions[4] = (glm::vec3(pos_1.x, pos_1.y, pos_1.z));
   }

   void initFriendlyPositions()
   {    
    float area = (float) 7*wh/8 - (float) wh/3;
    float xarea = (float) ww/2;

    glm::vec3 pos_1 = screenToWorldPoint(3*ww/4, 7*wh/8 - area/5);        
    glm::vec3 pos_2 = screenToWorldPoint(3*ww/4, 7*wh/8 - 2*area/5);    
    glm::vec3 pos_3 = screenToWorldPoint(3*ww/4, 7*wh/8 - 3*area/5);    
    glm::vec3 pos_4 = screenToWorldPoint(3*ww/4, 7*wh/8 - 4*area/5);    
    glm::vec3 pos_5 = screenToWorldPoint(3*ww/4, 7*wh/8 - 5*area/5);    
    glBegin(GL_POINTS);
      glColor3f(0,1,0);
      glVertex3f(ww/4, 7*wh/8 - area/5, 0);
    glEnd();
    friendlyPositions.push_back(glm::vec3(pos_5.x, pos_5.y, pos_5.z));
    friendlyPositions.push_back(glm::vec3(pos_4.x, pos_4.y, pos_4.z));
    friendlyPositions.push_back(glm::vec3(pos_3.x, pos_3.y, pos_3.z));
    friendlyPositions.push_back(glm::vec3(pos_2.x, pos_2.y, pos_2.z));
    friendlyPositions.push_back(glm::vec3(pos_1.x, pos_1.y, pos_1.z));
   }

   void updateFriendlyPositions()
   {
    float area = (float) 7*wh/8 - (float) wh/3;
    float xarea = (float) ww/2;

    glm::vec3 pos_1 = screenToWorldPoint(3*ww/4, 7*wh/8 - area/5);        
    glm::vec3 pos_2 = screenToWorldPoint(3*ww/4, 7*wh/8 - 2*area/5);    
    glm::vec3 pos_3 = screenToWorldPoint(3*ww/4, 7*wh/8 - 3*area/5);    
    glm::vec3 pos_4 = screenToWorldPoint(3*ww/4, 7*wh/8 - 4*area/5);    
    glm::vec3 pos_5 = screenToWorldPoint(3*ww/4, 7*wh/8 - 5*area/5);    
    glBegin(GL_POINTS);
      glColor3f(0,1,0);
      glVertex3f(ww/4, 7*wh/8 - area/5, 0);
    glEnd();
    friendlyPositions[0] = (glm::vec3(pos_5.x, pos_5.y, pos_5.z));
    friendlyPositions[1] = (glm::vec3(pos_4.x, pos_4.y, pos_4.z));
    friendlyPositions[2] = (glm::vec3(pos_3.x, pos_3.y, pos_3.z));
    friendlyPositions[3] = (glm::vec3(pos_2.x, pos_2.y, pos_2.z));
    friendlyPositions[4] = (glm::vec3(pos_1.x, pos_1.y, pos_1.z));
   }

   void setup()
   {

   }

   void setww(int _ww)
   {    
    ww = _ww;
   }

   void setwh(int _wh)
   {
    wh = _wh;
   }

   void drawFriendlyShips()
   {
      std::vector<Ship*> ships = myDestroyListener.getShipsDestroyed();
      for(int i = 0; i < ships.size(); i++)
      {                
        if(!setFriendly)
        {
          ships[i]->resetParams();
          ships[i]->addRotation(0,90,0);
          initFriendlyPositions();
        }
        else
        {
          updateFriendlyPositions();
        }
        ships[i]->setTranslation(friendlyPositions[i].x, friendlyPositions[i].y, friendlyPositions[i].z);
        ships[i]->Draw(textureMode);
      }
      setFriendly = true;
   }
   
   void drawEnemyShips()
   {      
      std::vector<Ship*> ships = oDestroyListener.getShipsDestroyed();
      for(int i = 0; i < ships.size(); i++)
      {                
        if(!setEnemy)
        {
          ships[i]->resetParams();
          ships[i]->addRotation(0,90,0);
          initEnemyPositions();
        }
        else
        {
          updateEnemyPositions();
        }
        ships[i]->setTranslation(enemyPositions[i].x, enemyPositions[i].y, enemyPositions[i].z);
        ships[i]->Draw(textureMode);
      }
      setEnemy = true;
   }
};

#endif //UIClient_H
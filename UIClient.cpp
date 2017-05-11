#include "UIClient.hpp"

UIClient::UIClient(char const *port, char const *hostname, struct addrinfo *hints, Map * _myMap, Map * _opponentMap) : Client(port, hostname, hints, &eventListener, &myDestroyListener, &oDestroyListener) {
	eventListener.setMap(_myMap);

	myDestroyListener.setMap(_opponentMap);   
	myDestroyListener.setOtherMap(_myMap);	           
	myDestroyListener.setTransitioner(&myMapToTheirMap);

	oDestroyListener.setMap(_myMap);   
	oDestroyListener.setOtherMap(_opponentMap);   
	oDestroyListener.setTransitioner(&theirMapToMyMap);      
}

EventListener & UIClient::getEventListener(){
	return eventListener;
}

void UIClient::initEnemyPositions()
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

void UIClient::updateEnemyPositions()
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

void UIClient::initFriendlyPositions()
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

void UIClient::updateFriendlyPositions()
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

void UIClient::setup()
{

}

void UIClient::setww(int _ww)
{    
	ww = _ww;
}

void UIClient::setwh(int _wh)
{
	wh = _wh;
}

void UIClient::drawFriendlyShips()
{
	std::vector<Ship*> ships = oDestroyListener.getShipsDestroyed();
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

void UIClient::drawEnemyShips()
{      
	std::vector<Ship*> ships = myDestroyListener.getShipsDestroyed();
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
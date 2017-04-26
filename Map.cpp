#include "Map.hpp"

Map::Map(bool _empty) : A("Objects/A.obj"),  B("Objects/B.obj"),  C("Objects/C.obj"),  D("Objects/D.obj"),  E("Objects/E.obj"),  F("Objects/F.obj"),  G("Objects/G.obj"),  H("Objects/H.obj"),  I("Objects/I.obj"),  J("Objects/J.obj"),  K("Objects/K.obj"),  N1("Objects/1.obj"),  N2("Objects/2.obj"),  N3("Objects/3.obj"),  N4("Objects/4.obj"),  N5("Objects/5.obj"),  N6("Objects/6.obj"),  N7("Objects/7.obj"),  N8("Objects/8.obj"),  N9("Objects/9.obj"),  N10("Objects/10.obj"),  N11("Objects/11.obj")
{	
		ship_2 = new Ship("Objects/Bladesong/Bladesong.obj", 0,0.4,0); 
		ship_5 = new Ship("Objects/Submarino/i400.obj", 0, 0.2, 0); 
		ship_3 = new Ship("Objects/Gunboat/Gunboat.obj", 0,0.25,0); 
		ship_3_2 = new Ship("Objects/Prestes/Prestes.obj", 0,0.08,0); 
		ship_4 = new Ship("Objects/Carrier/carrier.obj", 0,0.1,0);

		ship_2->setLife(2);
		ship_5->setLife(5);
		ship_3->setLife(3);
		ship_3_2->setLife(3);
		ship_4->setLife(4);

		std::vector<std::vector<float>> ship_2_box = ship_2->getBoundingBox();		
		ship_2->setTopAnchor(glm::vec3((ship_2_box[2][0]+ship_2_box[3][0])/2, (ship_2_box[2][1]+ship_2_box[3][1])/2, (ship_2_box[2][2]+ship_2_box[3][2])/2));
		ship_2->setLeftAnchor(glm::vec3((ship_2_box[2][0]+ship_2_box[7][0])/2, (ship_2_box[2][1]+ship_2_box[7][1])/2, (ship_2_box[2][2]+ship_2_box[7][2])/2));

		std::vector<std::vector<float>> ship_3_box = ship_3->getBoundingBox();		
		ship_3->setTopAnchor(glm::vec3((ship_3_box[2][0]+ship_3_box[3][0])/2, (ship_3_box[2][1]+ship_3_box[3][1])/2, (ship_3_box[2][2]+ship_3_box[3][2])/2));
		ship_3->setLeftAnchor(glm::vec3((ship_3_box[2][0]+ship_3_box[7][0])/2, (ship_3_box[2][1]+ship_3_box[7][1])/2, (ship_3_box[2][2]+ship_3_box[7][2])/2));
		
		std::vector<std::vector<float>> ship_3_2_box = ship_3_2->getBoundingBox();		
		ship_3_2->setTopAnchor(glm::vec3((ship_3_2_box[4][0]+ship_3_2_box[3][0])/2, (ship_3_2_box[4][1]+ship_3_2_box[3][1])/2, (ship_3_2_box[4][2]+ship_3_2_box[3][2])/2));
		ship_3_2->setLeftAnchor(glm::vec3((ship_3_2_box[2][0]+ship_3_2_box[3][0])/2, (ship_3_2_box[2][1]+ship_3_2_box[3][1])/2, (ship_3_2_box[2][2]+ship_3_2_box[3][2])/2));

		std::vector<std::vector<float>> ship_4_box = ship_4->getBoundingBox();		
		ship_4->setTopAnchor(glm::vec3((ship_4_box[4][0]+ship_4_box[7][0])/2, (ship_4_box[4][1]+ship_4_box[7][1])/2, (ship_4_box[4][2]+ship_4_box[7][2])/2));
		ship_4->setLeftAnchor(glm::vec3((ship_4_box[3][0]+ship_4_box[4][0])/2, (ship_4_box[3][1]+ship_4_box[4][1])/2, (ship_4_box[3][2]+ship_4_box[4][2])/2));

		std::vector<std::vector<float>> ship_5_box = ship_5->getBoundingBox();		
		ship_5->setTopAnchor(glm::vec3((ship_5_box[3][0]+ship_5_box[4][0])/2, (ship_5_box[3][1]+ship_5_box[4][1])/2, (ship_5_box[3][2]+ship_5_box[4][2])/2));
		ship_5->setLeftAnchor(glm::vec3((ship_5_box[2][0]+ship_5_box[3][0])/2, (ship_5_box[2][1]+ship_5_box[3][1])/2, (ship_5_box[2][2]+ship_5_box[3][2])/2));

		for(int i = 0; i < X; i++)
		{
			std::vector<Tile*> row;			
			for(int j = 0; j < Y; j++)
			{				
				row.push_back(new Tile());
			}
			grid.push_back(row);
		}
		
		if(!_empty)
			initShips();
		else
		{
			mapStartX = -2;
			ship_2->setParams(0.37,0.37,0.37, 0,0,0.24, 90,0,0);
			ship_3->setParams(0.57,0.57,0.57, 0,0,0.3, 90,0,0);
			ship_3_2->setParams(0.57,0.57,0.57, 0,0,0.23, 90,90,0);	
			ship_4->setParams(0.65,0.8,0.8, 0,0,0.2, 90,180,0);
			ship_5->setParams(1,0.57,1.2, 0,0,0.15 ,90,90,0);	

			ship_2->setName("2 - Bladesong");
			ship_3->setName("3 - Gunboat");
			ship_3_2->setName("3 - Prestes");
			ship_4->setName("4 - Carrier");
			ship_5->setName("5 - Submarine");
		}

		initTiles();
		initLetters();
		initNumbers();

		tileSideLength = grid[0][0]->getTileSideLength();	
		std::cout << "tileSideLength: " << tileSideLength << std::endl;			
}

Map::~Map()
{

}

Ship * Map::getShip(int pos)
{
	return ships[pos];
}


void Map::initLetters()
{
	A.setParams(0.5,0.5,0.5, 0,4.3,0, 90,0,0);
	B.setParams(0.8,0.8,0.8, 0,3.9,0, 90,0,0);
	C.setParams(1,1,1, 0,3.46,0, 90,0,0);
	D.setParams(1.3,1.3,1.3, 0.0,3.05,0, 90,0,0);
	E.setParams(1.5,1.5,1.5, 0,2.62,0, 90,0,0);
	F.setParams(1.5,1.5,1.5, 0,2.2,0, 90,0,0);
	G.setParams(0.25,0.25,0.25, 0,1.78,0, 90,0,0);
	H.setParams(0.5,0.5,0.5, 0,1.35,0, 90,0,0);
	I.setParams(0.7,0.7,0.7, 0,0.92,0, 90,0,0);
	J.setParams(1,1,1, 0,0.5,0, 90,0,0);
	K.setParams(1.3,1.3,1.3, 0,0.05,0, 90,0,0);
	A.setName("A");
	B.setName("B");
	C.setName("C");
	D.setName("D");
	E.setName("E");
	F.setName("F");
	G.setName("G");
	H.setName("H");
	I.setName("I");
	J.setName("J");
	K.setName("K");
}

void Map::initNumbers()
{
	N1.setParams(0.5,0.5,0.5, 0,0.1,0, 90,0,0);
	N2.setParams(1.7,1.7,1.7, 0.42,0.1,0, 90,0,0);
	N3.setParams(1.1,1.1,1.1, 0.84,0.1,0, 90,0,0);
	N4.setParams(1.5,1.5,1.5, 1.26,0.1,0, 90,0,0);
	N5.setParams(2.2,2.2,2.2, 1.68,0.1,0, 90,0,0);
	N6.setParams(1.1,1.1,1.1, 2.1,0.1,0, 90,0,0);
	N7.setParams(1.1,1.1,1.1, 2.52,0.1,0, 90,0,0);
	N8.setParams(1.3,1.3,1.3, 2.94,0.1,0, 90,0,0);
	N9.setParams(1.7,1.7,1.7, 3.36,0.1,0, 90,0,0);
	N10.setParams(1.7,1.7,1.7, 3.78,0.1,0, 90,0,0);
	N11.setParams(2.3,2.3,2.3, 4.21,0.1,0, 90,0,0);
	N1.setName("1");
	N2.setName("2");
	N3.setName("3");
	N4.setName("4");
	N5.setName("5");
	N6.setName("6");
	N7.setName("7");
	N8.setName("8");
	N9.setName("9");
	N10.setName("10");
	N11.setName("11");
}

void Map::initShips()
{

	ship_2->setParams(0.37,0.37,0.37, 2 + 0.1,1,0.24, 90,0,0);
	ship_3->setParams(0.57,0.57,0.57, 2.6 + 0.1,1,0.3, 90,0,0);
	ship_3_2->setParams(0.57,0.57,0.57, 2 + 0.1,-1,0.23, 90,90,0);	
	ship_4->setParams(0.65,0.8,0.8, 2.6 + 0.1,-1,0.2, 90,180,0);
	ship_5->setParams(1,0.57,1.2, 3.3 + 0.1,0.25,0.15 ,90,90,0);	

	ship_2->setName("2 - Bladesong");
	ship_3->setName("3 - Gunboat");
	ship_3_2->setName("3 - Prestes");
	ship_4->setName("4 - Carrier");
	ship_5->setName("5 - Submarine");

	ships.push_back(ship_2);
	ships.push_back(ship_3);
	ships.push_back(ship_3_2);
	ships.push_back(ship_4);	
	ships.push_back(ship_5);
}

void Map::drawShips()
{	
	for(int i = 0;i < ships.size(); i++)
	{
		ships[i]->Draw(textureMode);
		if(debug)
		{
			ships[i]->DrawBoundingBox();
		}
	}		
}

void Map::initTiles()
{
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{ 
			grid[i][j]->setParams(0.6,0.6,0.6, mapStartX+(i*.42),mapStartY-(j*.42),0, 90,0,0);
			std::ostringstream os;
			os << "Tile (" << letterArray[j] << ", " << i+1 << ")"; 
			grid[i][j]->setName(os.str());
			grid[i][j]->setGridPos(i, j);								
		}
	}	
}


bool shipSort (std::pair<Ship*, float> i,std::pair<Ship*, float> j)
{ 
	return j.second > i.second;
}

bool tileSort (std::pair<Tile*, float> i,std::pair<Tile*, float> j)
{ 
	return j.second > i.second;
}

Tile * Map::getTileHit(glm::vec3 near, glm::vec3 far)
{
	std::vector<std::pair<Tile*, float>> hitObjects;
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			float dist;
			if(grid[i][j]->checkIntersection(near, far, dist))
			{				
				std::pair<Tile*, float> temp(grid[i][j], dist);
				hitObjects.push_back(temp);
			}
		}
	}
	std::sort(hitObjects.begin(), hitObjects.end(), tileSort);
	if(hitObjects.size() > 0)
		return hitObjects[0].first;
	else
		return nullptr;
}

Ship * Map::getShipHit(glm::vec3 near, glm::vec3 far)
{
	std::vector<std::pair<Ship*, float>> hitObjects;
	for(int i = 0; i < ships.size(); i++)
	{
		float dist;
		if(ships[i]->checkIntersection(near, far, dist))
		{				
			std::pair<Ship*, float> temp(ships[i], dist);
			hitObjects.push_back(temp);
		}
	}
	std::sort(hitObjects.begin(), hitObjects.end(), shipSort);
	if(hitObjects.size() > 0)
	{		
		return hitObjects[0].first;
	}
	else
		return nullptr;
}

Tile * Map::getClosestTile(Ship * _ship, Direction _dir)
{
	Tile * closestTile = nullptr;	
	glm::vec3 ship = _ship->getTopAnchor();
	float closestDist;
	if(_dir == Direction::TOP_BOTTOM)
		closestDist = glm::distance(grid[0][0]->getTopAnchor(), ship);
	else
		closestDist = glm::distance(grid[0][0]->getLeftAnchor(), ship);	
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			float dist;
			if(_dir == Direction::TOP_BOTTOM)
				dist = glm::distance(grid[i][j]->getTopAnchor(), ship);
			else
				dist = glm::distance(grid[i][j]->getLeftAnchor(), ship);
			if(dist <= tileSideLength)
			{								
				//Tile and ship are within reasonable distance
				if(dist <= closestDist && grid[i][j]->getCurrentState() == Tile::State::FREE)
				{					
					closestTile = grid[i][j];
					closestDist = dist;
				}
			}
		}
	}
	return closestTile;
}

void Map::clipAndUpdateShip(Ship * current_ship)
{
	if(current_ship != nullptr)
    {         
    	Direction ship_dir = current_ship->getDirection();                       
        Tile * closestTile = getClosestTile(current_ship, ship_dir);        
        if(closestTile != nullptr && !tilesUsed(closestTile, current_ship, ship_dir))
        {
            std::cout << "Closest tile is: " << closestTile->getName() << std::endl;
            clipShipToTile(ship_dir, current_ship, closestTile);
        }
        else
        {
        	std::map<std::string, float> initParams = current_ship->getInitialParams();
        	current_ship->setParamsByMap(initParams);
        	current_ship->setDirection(Direction::TOP_BOTTOM);
        }
    }        
}

void Map::updateTileInGrid(Tile * _tile, int ship_life, Direction _dir, Tile::State _state)
{
	std::vector<int> start_pos = _tile->getGridPos();
	if(_dir == Direction::TOP_BOTTOM)
	{				
		std::vector<int> end_pos = {start_pos[0], (start_pos[1] + ship_life-1)};	
		for(int i = 0; i < ship_life; i++)
		{
			grid[start_pos[0]][start_pos[1]+i]->updateState(_state);
		}	
	}	
	else if(_dir == Direction::LEFT_RIGHT)
	{		
		std::vector<int> end_pos = {(start_pos[0] + ship_life-1), start_pos[1]};	
		for(int i = 0; i < ship_life; i++)
		{
			grid[start_pos[0]+i][start_pos[1]]->updateState(_state);
		}
	}
}

void Map::updateShipPositions(Tile * _tile, Ship * _ship, Direction _dir)
{
	int ship_life = _ship->getLife();
	if(_dir == Direction::TOP_BOTTOM)
	{
		std::vector<int> start_pos = _tile->getGridPos();		
		std::vector<int> end_pos = {start_pos[0], (start_pos[1] + ship_life-1)};		
		_ship->setStartPos(start_pos);
		_ship->setEndPos(end_pos);
	}	
	else if(_dir == Direction::LEFT_RIGHT)
	{
		std::vector<int> start_pos = _tile->getGridPos();		
		std::vector<int> end_pos = {(start_pos[0] + ship_life-1), start_pos[1]};		
		_ship->setStartPos(start_pos);
		_ship->setEndPos(end_pos);
	}
	std::cout << _ship->getName() << " start position: (" << _ship->getStartPos()[0] << ", " << _ship->getStartPos()[1] << ")" << std::endl;
	std::cout << _ship->getName() << " end position: (" << _ship->getEndPos()[0] << ", " << _ship->getEndPos()[1] << ")" << std::endl;
}

bool Map::tilesUsed(Tile * _tile, Ship * _ship, Direction _dir)
{
	int ship_life = _ship->getLife();
	std::vector<int> start_pos = _tile->getGridPos();
	if(_dir == Direction::TOP_BOTTOM)
	{					
		if(start_pos[1]+ship_life > Y)
			return true;	
		for(int i = 0; i < ship_life; i++)
		{
			if(grid[start_pos[0]][start_pos[1]+i]->getCurrentState() == Tile::State::USED)
				return true;			
		}	
	}	
	else if(_dir == Direction::LEFT_RIGHT)
	{		
		if(start_pos[0]+ship_life > X)
			return true;			
		for(int i = 0; i < ship_life; i++)
		{
			if(grid[start_pos[0]+i][start_pos[1]]->getCurrentState() == Tile::State::USED)
				return true;
		}
	}
	return false;
}

void Map::clipShipToTile(Direction _dir, Ship * _ship, Tile * _tile)
{	
	glm::vec3 ship_pos = _ship->getTopAnchor();
	int life = _ship->getLife();
	if(_dir == Direction::TOP_BOTTOM)
	{		
		glm::vec3 tile_pos =  _tile->getTopAnchor();
		glm::vec3 offset (tile_pos.x-ship_pos.x, tile_pos.y-ship_pos.y, tile_pos.z-ship_pos.z);
		_ship->addTranslation(offset.x, offset.y, 0);		
		updateShipPositions(_tile, _ship, _dir);
		updateTileInGrid(_tile, life, _dir, Tile::State::USED);
	}
	else if(_dir == Direction::LEFT_RIGHT)
	{		
		glm::vec3 tile_pos =  _tile->getLeftAnchor();
		glm::vec3 offset (tile_pos.x-ship_pos.x, tile_pos.y-ship_pos.y, tile_pos.z-ship_pos.z);
		_ship->addTranslation(offset.x, offset.y, 0);		
		updateShipPositions(_tile, _ship, _dir);
		updateTileInGrid(_tile, life, _dir, Tile::State::USED);
	}
	_ship->setPlaced(true);
}

void Map::unclipShipFromGrid(Ship * _ship)
{	
	std::vector<int> start_pos = _ship->getStartPos();	
	Tile * start_tile = grid[start_pos[0]][start_pos[1]];	
	int life = _ship->getLife();
	updateTileInGrid(start_tile, life, _ship->getDirection(), Tile::State::FREE);	
	std::vector<int> def = {-1, -1};		
	_ship->setStartPos(def);
	_ship->setEndPos(def);  
	_ship->setPlaced(false);
}


void Map::setCurrentShipSelected(Ship * _ship)
{
	currentShipSelected = _ship;
}

Ship * Map::getCurrentShipSelected()
{
	return currentShipSelected;
}

Tile * Map::getTile(int letter, int number)
{
	return grid[letter][number];
}

void Map::Draw()
{
	drawNumbers();
	drawLetters();
	drawTiles();
	drawShips();
}

void Map::drawNumbers()
{
	glPushMatrix();
		glTranslatef(mapStartX, mapStartY+0.45, 0);
		N1.Draw(textureMode);
		N2.Draw(textureMode);
		N3.Draw(textureMode);
		N4.Draw(textureMode);
		N5.Draw(textureMode);
		N6.Draw(textureMode);
		N7.Draw(textureMode);
		N8.Draw(textureMode);
		N9.Draw(textureMode);
		N10.Draw(textureMode);
		N11.Draw(textureMode);
	glPopMatrix();
}

void Map::drawLetters()
{
	glPushMatrix();
		glTranslatef(mapStartX-0.5, -mapStartY-0.63, 0);
		A.Draw(textureMode);
		B.Draw(textureMode);
		C.Draw(textureMode);
		D.Draw(textureMode);
		E.Draw(textureMode);
		F.Draw(textureMode);
		G.Draw(textureMode);
		H.Draw(textureMode);
		I.Draw(textureMode);
		J.Draw(textureMode);
		K.Draw(textureMode);
	glPopMatrix();
}

void Map::drawTiles()
{
	glPushMatrix();		
		for(int i = 0; i < X; i++)
		{
			for(int j = 0; j < Y; j++)
			{ 
				grid[i][j]->Draw(textureMode);	
				if(debug)							
					grid[i][j]->DrawBoundingBox();					
			}
		}
	glPopMatrix();
}

bool Map::everyShipPlaced()
{
	for(int i = 0; i < ships.size(); i++)
	{
		if(!ships[i]->isPlaced())
			return false;
	}
	return true;
}

//Función para aplicar un color en específico a las figuras rendereadas 
void Map::ApplyColor(
   GLfloat ambr, GLfloat ambg, GLfloat ambb,
   GLfloat difr, GLfloat difg, GLfloat difb,
   GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine)
{  
    GLfloat mat[4];
    mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = difr; mat[1] = difg; mat[2] = difb;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = specr; mat[1] = specg; mat[2] = specb;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine * 128.0);  
}


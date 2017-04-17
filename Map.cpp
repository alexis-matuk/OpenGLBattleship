#include "Map.hpp"

Map::Map() : A("Objects/A.obj"),  B("Objects/B.obj"),  C("Objects/C.obj"),  D("Objects/D.obj"),  E("Objects/E.obj"),  F("Objects/F.obj"),  G("Objects/G.obj"),  H("Objects/H.obj"),  I("Objects/I.obj"),  J("Objects/J.obj"),  K("Objects/K.obj"),  N1("Objects/1.obj"),  N2("Objects/2.obj"),  N3("Objects/3.obj"),  N4("Objects/4.obj"),  N5("Objects/5.obj"),  N6("Objects/6.obj"),  N7("Objects/7.obj"),  N8("Objects/8.obj"),  N9("Objects/9.obj"),  N10("Objects/10.obj"),  N11("Objects/11.obj")
{	
		ship_2 = new Ship("Objects/Bladesong/Bladesong.obj", 0,0.4,0); 
		ship_5 = new Ship("Objects/Submarino/i400.obj", 0, 0.2, 0); 
		ship_3 = new Ship("Objects/Gunboat/Gunboat.obj", 0,0.25,0); 
		ship_3_2 = new Ship("Objects/Prestes/Prestes.obj", 0,0.08,0); 
		ship_4 = new Ship("Objects/Carrier/carrier.obj", 0,0.1,0);

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

		initTiles();
		initLetters();
		initNumbers();
		initShips();

		std::vector<std::vector<float>> tile_box = grid[0][0]->getBoundingBox();
		glm::vec3 v0(tile_box[0][0], tile_box[0][1], tile_box[0][2]);
		glm::vec3 v1(tile_box[1][0], tile_box[1][1], tile_box[1][2]);
		tileSideLength = glm::distance(v1,v0);
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
		ships[i]->Draw();
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
	return nullptr;
}

Ship * Map::getShipHit(glm::vec3 near, glm::vec3 far, float & distance)
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
		std::cout <<  "Distance: " << hitObjects[0].second << std::endl;
		distance = hitObjects[0].second;
		return hitObjects[0].first;
	}
	else
		return nullptr;
}

Tile * Map::getClosestTile(glm::vec3 ship)
{
	Tile * closestTile = nullptr;
	float closestDist = glm::distance(grid[0][0]->getTopAnchor(), ship);
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			float dist = glm::distance(grid[i][j]->getTopAnchor(), ship);
			if(dist <= tileSideLength)
			{				
				//Tile and ship are within reasonable distance
				if(dist < closestDist)
				{					
					closestTile = grid[i][j];
					closestDist = dist;
				}
			}
		}
	}
	return closestTile;
}

void Map::clipShipToTile(Direction _dir, Ship * _ship, Tile * _tile)
{
	std::map<std::string, float> ship_params = _ship->getParams();
	if(_dir == Direction::TOP_BOTTOM)
	{
		glm::vec3 ship_pos = _ship->getTopAnchor();
		glm::vec3 tile_pos =  _tile->getTopAnchor();
		glm::vec3 offset (-ship_pos.x+tile_pos.x, -ship_pos.y+tile_pos.y, -ship_pos.z+tile_pos.z);
		_ship->addTranslation(offset.x, offset.y, 0);
	}
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
		N1.Draw();
		N2.Draw();
		N3.Draw();
		N4.Draw();
		N5.Draw();
		N6.Draw();
		N7.Draw();
		N8.Draw();
		N9.Draw();
		N10.Draw();
		N11.Draw();
	glPopMatrix();
}

void Map::drawLetters()
{
	glPushMatrix();
		glTranslatef(mapStartX-0.5, -mapStartY-0.63, 0);
		A.Draw();
		B.Draw();
		C.Draw();
		D.Draw();
		E.Draw();
		F.Draw();
		G.Draw();
		H.Draw();
		I.Draw();
		J.Draw();
		K.Draw();
	glPopMatrix();
}

void Map::drawTiles()
{
	glPushMatrix();		
		for(int i = 0; i < X; i++)
		{
			for(int j = 0; j < Y; j++)
			{ 
				grid[i][j]->Draw();	
				if(debug)							
					grid[i][j]->DrawBoundingBox();					
			}
		}
	glPopMatrix();
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


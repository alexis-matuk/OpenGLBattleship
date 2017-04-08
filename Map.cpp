#include "Map.hpp"

Map::Map() : grid(X, std::vector<Tile>(Y)), ship_2("Objects/Bladesong/Bladesong.obj", 0,0.4,0), ship_5("Objects/Submarino/i400.obj", 0, 0.2, 0), ship_3("Objects/Gunboat/Gunboat.obj", 0,0.25,0), ship_3_2("Objects/Prestes/Prestes.obj", 0,0.08,0), ship_4("Objects/Carrier/carrier.obj", 0,0.1,0)
{	
	initTiles();
	initShips();
	loadObjects();		
}

Map::~Map()
{

}

Ship & Map::getShip(int pos)
{
	return ships[pos];
}

void Map::initShips()
{
	ship_2.setParams(0.37,0.37,0.37, 0.1,0.24,0, 0,0,0,0);
	ship_3.setParams(0.57,0.57,0.57, 0.1,0.3,0.2, 0,0,0,0);
	ship_3_2.setParams(0.57,0.57,0.57, 0.1,0.23,0.2, 90,0,1,0);
	ship_4.setParams(0.65,0.8,0.8, 0.1,0.2,0, 180,0,1,0);
	ship_5.setParams(1,0.57,1.2, 0.1,0.15,0.25, 90,0,1,0);	
	ships.push_back(ship_2);
	ships.push_back(ship_3);
	ships.push_back(ship_3_2);
	ships.push_back(ship_4);	
	ships.push_back(ship_5);
}

void Map::drawShips()
{
	for(int i = 0; i < ships.size(); i++)
	{
		ships[i].Draw();		
	}
}

void Map::initTiles()
{
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{ 
			grid[i][j].setParams(0.6,0.6,0.6, -2+(i*.42),0,-1.9+(j*.42), 0,0,0,0);						
		}
	}	
}

Tile & Map::getTile(int letter, int number)
{
	return grid[letter][number];
}

void Map::Draw()
{
	drawNumbers();
	drawLetters();
	drawTiles();
}

void Map::loadObjects()
{
	this->A = loadModel("Objects/A.obj");
	this->B = loadModel("Objects/B.obj");
	this->C = loadModel("Objects/C.obj");
	this->D = loadModel("Objects/D.obj");
	this->E = loadModel("Objects/E.obj");
	this->F = loadModel("Objects/F.obj");
	this->G = loadModel("Objects/G.obj");
	this->H = loadModel("Objects/H.obj");
	this->I = loadModel("Objects/I.obj");
	this->J = loadModel("Objects/J.obj");
	this->K = loadModel("Objects/K.obj");	

	this->N1 = loadModel("Objects/1.obj");
	this->N2 = loadModel("Objects/2.obj");
	this->N3 = loadModel("Objects/3.obj");
	this->N4 = loadModel("Objects/4.obj");
	this->N5 = loadModel("Objects/5.obj");
	this->N6 = loadModel("Objects/6.obj");
	this->N7 = loadModel("Objects/7.obj");
	this->N8 = loadModel("Objects/8.obj");
	this->N9 = loadModel("Objects/9.obj");
	this->N10 = loadModel("Objects/10.obj");
	this->N11 = loadModel("Objects/11.obj");
}

void Map::drawNumbers()
{
	glPushMatrix();
		glTranslatef(-2, 0, -2.5);
		DrawModel(N1, 0.5,0.5,0.5, 0,0,0.1, 0,0,0,0);
		DrawModel(N2, 1.7,1.7,1.7, 0.42,0,0.1, 0,0,0,0);
		DrawModel(N3, 1.1,1.1,1.1, 0.84,0,0.1, 0,0,0,0);
		DrawModel(N4, 1.5,1.5,1.5, 1.26,0,0.1, 0,0,0,0);
		DrawModel(N5, 2.2,2.2,2.2, 1.68,0,0.1, 0,0,0,0);
		DrawModel(N6, 1.1,1.1,1.1, 2.1,0,0.1, 0,0,0,0);
		DrawModel(N7, 1.1,1.1,1.1, 2.52,0,0.1, 0,0,0,0);
		DrawModel(N8, 1.3,1.3,1.3, 2.94,0,0.1, 0,0,0,0);
		DrawModel(N9, 1.7,1.7,1.7, 3.36,0,0.1, 0,0,0,0);
		DrawModel(N10, 1.7,1.7,1.7, 3.78,0,0.1, 0,0,0,0);
		DrawModel(N11, 2.3,2.3,2.3, 4.21,0,0.1, 0,0,0,0);
	glPopMatrix();
}

void Map::drawLetters()
{
	glPushMatrix();
		glTranslatef(-2.5, 0, -2.0);
		DrawModel(A, 0.5,0.5,0.5, 0,0,0.05, 0,0,0,0);
		DrawModel(B, 0.8,0.8,0.8, 0,0,0.5, 0,0,0,0);
		DrawModel(C, 1,1,1, 0,0,0.92, 0,0,0,0);		
		DrawModel(D, 1.3,1.3,1.3, 0.02,0,1.35, 0,0,0,0);
		DrawModel(E, 1.5,1.5,1.5, 0,0,1.78, 0,0,0,0);
		DrawModel(F, 1.5,1.5,1.5, 0,0,2.2, 0,0,0,0);
		DrawModel(G, 0.25,0.25,0.25, 0,0,2.62, 0,0,0,0);
		DrawModel(H, 0.5,0.5,0.5, 0,0,3.05, 0,0,0,0);
		DrawModel(I, 0.7,0.7,0.7, 0,0,3.46, 0,0,0,0);
		DrawModel(J, 1,1,1, 0,0,3.9, 0,0,0,0);
		DrawModel(K, 1.3,1.3,1.3, 0,0,4.3, 0,0,0,0);	
	glPopMatrix();
}

void Map::drawTiles()
{
	glPushMatrix();		
		for(int i = 0; i < X; i++)
		{
			for(int j = 0; j < Y; j++)
			{ 
				grid[i][j].Draw();					
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


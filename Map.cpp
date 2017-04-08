#include "Map.hpp"

Map::Map() : grid(X, std::vector<Tile>(Y)), ship_2("Objects/Bladesong/Bladesong.obj", 0,0.4,0), ship_5("Objects/Submarino/i400.obj", 0, 0.2, 0), ship_3("Objects/Gunboat/Gunboat.obj", 0,0.25,0), ship_3_2("Objects/Prestes/Prestes.obj", 0,0.08,0), ship_4("Objects/Carrier/carrier.obj", 0,0.1,0), A(0.5,0.5,0.5, 0,0,0.05, 0,0,0,0, "Objects/A.obj"), B(0.8,0.8,0.8, 0,0,0.5, 0,0,0,0, "Objects/B.obj"), C(1,1,1, 0,0,0.92, 0,0,0,0, "Objects/C.obj"), D(1.3,1.3,1.3, 0.02,0,1.35, 0,0,0,0, "Objects/D.obj"), E(1.5,1.5,1.5, 0,0,1.78, 0,0,0,0, "Objects/E.obj"), F(1.5,1.5,1.5, 0,0,2.2, 0,0,0,0, "Objects/F.obj"), G(0.25,0.25,0.25, 0,0,2.62, 0,0,0,0, "Objects/G.obj"), H(0.5,0.5,0.5, 0,0,3.05, 0,0,0,0, "Objects/H.obj"), I(0.7,0.7,0.7, 0,0,3.46, 0,0,0,0, "Objects/I.obj"), J(1,1,1, 0,0,3.9, 0,0,0,0, "Objects/J.obj"), K(1.3,1.3,1.3, 0,0,4.3, 0,0,0,0, "Objects/K.obj"), N1 (0.5,0.5,0.5, 0,0,0.1, 0,0,0,0, "Objects/1.obj"), N2 (1.7,1.7,1.7, 0.42,0,0.1, 0,0,0,0, "Objects/2.obj"), N3 (1.1,1.1,1.1, 0.84,0,0.1, 0,0,0,0, "Objects/3.obj"), N4 (1.5,1.5,1.5, 1.26,0,0.1, 0,0,0,0, "Objects/4.obj"), N5 (2.2,2.2,2.2, 1.68,0,0.1, 0,0,0,0, "Objects/5.obj"), N6 (1.1,1.1,1.1, 2.1,0,0.1, 0,0,0,0, "Objects/6.obj"), N7 (1.1,1.1,1.1, 2.52,0,0.1, 0,0,0,0, "Objects/7.obj"), N8 (1.3,1.3,1.3, 2.94,0,0.1, 0,0,0,0, "Objects/8.obj"), N9 (1.7,1.7,1.7, 3.36,0,0.1, 0,0,0,0, "Objects/9.obj"), N10 (1.7,1.7,1.7, 3.78,0,0.1, 0,0,0,0, "Objects/10.obj"), N11 (2.3,2.3,2.3, 4.21,0,0.1, 0,0,0,0, "Objects/11.obj")
{	
		
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
			grid[i][j].setParams(0.6,0.6,0.6, -2+(i*.42),-1.9+(j*.42),0, 0,0,0,0);						
		}
	}	
}

Tile & Map::getTile(int letter, int number)
{
	return grid[letter][number];
}

void Map::Draw()
{
	// drawNumbers();
	// drawLetters();
	drawTiles();
}

void Map::drawNumbers()
{
	glPushMatrix();
		glTranslatef(-2, 0, -2.5);
		N1.drawModel();
		N2.drawModel();
		N3.drawModel();
		N4.drawModel();
		N5.drawModel();
		N6.drawModel();
		N7.drawModel();
		N8.drawModel();
		N9.drawModel();
		N10.drawModel();
		N11.drawModel();
	glPopMatrix();
}

void Map::drawLetters()
{
	glPushMatrix();
		glTranslatef(-2.5, 0, -2.0);
		A.drawModel();
		B.drawModel();
		C.drawModel();
		D.drawModel();
		E.drawModel();
		F.drawModel();
		G.drawModel();
		H.drawModel();
		I.drawModel();
		J.drawModel();
		K.drawModel();
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


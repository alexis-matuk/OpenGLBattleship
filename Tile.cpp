/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "Tile.hpp"

/*
  Initialize tile
  Initialize points, bouding box and update to transorms
*/
Tile::Tile()
{	
	shipId = '0';
	model = tileModel;
	scaleX = 0.6;
	scaleY = 0.6;
	scaleZ = 0.6;
	transX = 0;
	transY = 0;
	transZ = 0;	
	rotX = 90;
	rotY = 0;
	rotZ = 0;	
	distance = 0;
	type = "Tile";
	white_pin = whitePinModel;	
	red_pin = redPinModel;
	initPoints();
	initBoundingBox();
	updateBoundingBoxToTransforms();
	glm::vec3 v0(vertexArray[0][0], vertexArray[0][1], vertexArray[0][2]);
	glm::vec3 v1(vertexArray[1][0], vertexArray[1][1], vertexArray[1][2]);
	tileSideLength = glm::distance(v1,v0);	
}

/*
  Get length of side of the tile.
  Used for ship clipping.
*/
float Tile::getTileSideLength()
{
	return tileSideLength;	
}

/*
  Initialize tile given initial params
*/
Tile::Tile(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ):Object(_scaleX, _scaleY, _scaleZ, _x, _y, _z, _rotX, _rotY, _rotZ, "Objects/tile.obj")
{	
	initPoints();
	shipId = '0';
	type = "Tile";
}

Tile::~Tile()
{

}

/*
  Update tile's state
*/
void Tile::updateState(State _newState)
{
	lastState = currentState;
	currentState = _newState;
}

/*
  Get current tile's state
*/
Tile::State Tile::getCurrentState()
{
	return currentState;
}

/*
  Get previous tile's state
*/
Tile::State Tile::getLastState()
{
	return lastState;
}

/*
  Check if tile is valid for shooting
*/
bool Tile::getValidTile()
{
	if(currentState == State::FREE || currentState == State::USED)
		return true;
	return false;
}

/*
  Hit the tile and update state if necessary
*/
bool Tile::hit()
{
	switch(currentState)
	{
		case State::FREE:{			
			updateState(State::MARKED);
			makeRipple();
			return true;
		break;}
		case State::USED:{			
			updateState(State::HIT);			
			return true;
		break;}
		case State::HIT:{
			return false;
		break;}
		case State::MARKED:{
			return false;
		break;}
		default:
			return false;
		break;
	}
	return false;
}

/*
  Draw the tile with given transforms
  Draw white pin or red pin depending on the state of the tile set beforehand
*/
void Tile::Draw(GLuint _mode)
{	
	glPushMatrix();		
		glPushAttrib(GL_ALL_ATTRIB_BITS);  
			glPushMatrix();		
				glTranslatef(transX,transY,transZ);  
			    glRotatef(rotX, 1, 0, 0);
				glRotatef(rotY, 0, 1, 0);
				glRotatef(rotZ, 0, 0, 1);
			    glScalef(scaleX, scaleY, scaleZ);     
			    glTranslatef(centerX, centerY, centerZ);
				drawModel(_mode);					
					glScalef(0.7, 0.6, 0.7);	
					glTranslatef(0,0.5,0);
				if(currentState == State::MARKED)
					DrawModel(white_pin, noTextureMode);
				if(currentState == State::HIT)
					DrawModel(red_pin, noTextureMode);				
			glPopMatrix();				
				drawWater();				
		glPopAttrib();		
	glPopMatrix();
}

/*
  Initialize points for the water animation
  Points are initialized with a sinoidal function
*/
void Tile::initPoints()
{
	float float_x, float_y; 
	for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )	{
    	for(float_y = 0.0f; float_y < 9.0f; float_y += 0.2f)		{
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][0] = float_x - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][1] = float_y - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin(sqrt(float_x*float_x + float_y*float_y))); 
    	}
    }
}

/*
  Change the sinoidal function to have more ripples, simulating that a missile hit the water
*/
void Tile::makeRipple()
{
	float float_x, float_y; 
	for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )	{
    	for(float_y = 0.0f; float_y < 9.0f; float_y += 0.2f)		{
    		points[ (int) (float_x*5) ][ (int) (float_y*5) ][0] = float_x - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][1] = float_y - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( 10 * (float_x*float_x + float_y*float_y)/50))/0.5;            
    	}
    }
}

/*
  Function that moves the points around the QUAD
*/
void Tile::movePoints(int x, int y)
{
	float_x  = (float) (x)/44;
    float_y  = (float) (y)/44;
    float_xb = (float) (x+1)/44;
    float_yb = (float) (y+1)/44;
    glTexCoord2f( float_x, float_y);
    glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );
    glTexCoord2f( float_x, float_yb );
    glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );
    glTexCoord2f( float_xb, float_yb );
    glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );
    glTexCoord2f( float_xb, float_y );
    glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
}

/*
	Draw the water and animate the waves  
*/
void Tile::drawWater()
{
	glPushMatrix();							
	    glScalef(0.042,0.041,0.08);
	    glTranslatef(transX*24,transY*24.5,1.5);	    
	    glBindTexture(GL_TEXTURE_2D, texture[0]);
	    glPolygonMode(GL_BACK, GL_FILL);
	    glPolygonMode(GL_FRONT, GL_LINE);
	    glBegin(GL_QUADS);
	    for (x=0; x<44; x++) {
	    	for (y=0; y<44; y++) {
	    	    movePoints(x, y);
	    	}
	    }
	    glEnd();
	    if (wiggle_count == 1) {
		for (y = 0; y <45; y++) {
		    points[44][y][2] = points[0][y][2];
		}
		for( x = 0; x < 44; x++ ) {
		    for( y = 0; y < 45; y++) {
	        points[x][y][2] = points[x+1][y][2];
		    }		
		}		
		wiggle_count = 0;
	    }    
	    wiggle_count++; 	
    glPopMatrix(); 
}

/*
  Set position of tile in grid
*/
void Tile::setGridPos(int _gridX, int _gridY)
{
	gridX = _gridX;
	gridY = _gridY;
}

/*
  Get position of tile in grid
*/
std::vector<int> Tile::getGridPos()
{
	std::vector<int> res = {gridX, gridY};
	return res;
}

/*
  Set ship id.
  This is used for communication with the server.
*/
void Tile::setShipId(char _id)
{
	shipId = _id;
}

/*
  Get the ship id
*/
char Tile::getShipId()
{
	return shipId;
}
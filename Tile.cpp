#include "Tile.hpp"

Tile::Tile()
{	
	model = loadModel("Objects/tile.obj");
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
	initPoints();
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

Tile::Tile(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ):Object(_scaleX, _scaleY, _scaleZ, _x, _y, _z, _rotX, _rotY, _rotZ, "Objects/tile.obj")
{	
	initPoints();
	type = "Tile";
}

Tile::~Tile()
{

}

void Tile::updateState(State _newState)
{
	lastState = currentState;
	currentState = _newState;
}

Tile::State Tile::getCurrentState()
{
	return currentState;
}

Tile::State Tile::getLastState()
{
	return lastState;
}


void Tile::Draw()
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
				drawModel();	
			glPopMatrix();				
				drawWater();				
		glPopAttrib();		
	glPopMatrix();
}

void Tile::initPoints()
{
	float float_x, float_y; 
	for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )	{
    	for(float_y = 0.0f; float_y < 9.0f; float_y += 0.2f)		{
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][0] = float_x - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][1] = float_y - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin(sqrt(float_x*float_x + float_y*float_y)));
            // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin(2*float_x)*cos(2*float_y))/0.5;            
            // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( 10 * (float_x*float_x + float_y*float_y)/50))/0.5;
    	    // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( ( (float_x*5*8)/360 ) * 3.14159 * 2 ));               
    	}
    }
}

void Tile::makeRipple()
{
	float float_x, float_y; 
	for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )	{
    	for(float_y = 0.0f; float_y < 9.0f; float_y += 0.2f)		{
    		points[ (int) (float_x*5) ][ (int) (float_y*5) ][0] = float_x - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][1] = float_y - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( 10 * (float_x*float_x + float_y*float_y)/50))/0.5;
            // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin(2*float_x)*cos(2*float_y))/2;            
            // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( 10 * (float_x*float_x + float_y*float_y)/50))/5;
    	    // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( ( (float_x*5*8)/360 ) * 3.14159 * 2 ));               
    	}
    }
}

void Tile::drawWater()
{
	glPushMatrix();							
	    glScalef(0.042,0.041,0.08);
	    glTranslatef(transX*24,transY*24.5,1.5);	    
	    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
	    glPolygonMode(GL_BACK, GL_FILL);
	    glPolygonMode(GL_FRONT, GL_LINE);
	    glBegin(GL_QUADS);
	    for (x=0; x<44; x++) {
	    	for (y=0; y<44; y++) {
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
	    }
	    glEnd();

	    if (wiggle_count == 1) { // cycle the sine values
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

void Tile::setGridPos(int _gridX, int _gridY)
{
	gridX = _gridX;
	gridY = _gridY;
}

std::vector<int> Tile::getGridPos()
{
	std::vector<int> res = {gridX, gridY};
	return res;
}
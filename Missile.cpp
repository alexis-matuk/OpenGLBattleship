#include "Missile.hpp"

Missile::Missile(Tile * _targetTile):Object()
{		
	tile = _targetTile;
	tileCentroid = tile->getCentroid();
	scaleX = 0.2f;
	scaleY = 0.6f;
	scaleZ = 0.6;
	rotY = 270;
	transX = tileCentroid.x;
	transY = tileCentroid.y;
	zPos = tile->getTileSideLength() * 15;
	transZ = zPos;
	model = missileModel;
	startTime = glutGet(GLUT_ELAPSED_TIME);	
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

bool Missile::DrawMissile(GLuint _mode)
{
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	if(transZ <= tileCentroid.z)
	{
		tile->hit();
		return false;
	}
	else
	{
		transZ -= (currTime - startTime) * missileSpeed;
		glPushMatrix();		
			glPushAttrib(GL_ALL_ATTRIB_BITS);  					
				glTranslatef(transX,transY,transZ);  
			    glRotatef(rotX, 1, 0, 0);
				glRotatef(rotY, 0, 1, 0);
				glRotatef(rotZ, 0, 0, 1);
			    glScalef(scaleX, scaleY, scaleZ);     
			    glTranslatef(centerX, centerY, centerZ);
				drawModel(_mode);			
			glPopAttrib();		
		glPopMatrix();
		startTime = currTime;
		return true;
	}
}

Missile::~Missile()
{	
	transZ = zPos;
}
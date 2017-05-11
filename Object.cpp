#include "Object.hpp"

void Object::Draw(GLuint _mode)
{
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
}

void Object::setName(std::string _name)
{
	name = _name;
}

std::string Object::getName()
{
	return name;
}

void Object::initBoundingBox()
{
	if (model->numvertices == 0)
		return;  
    max_x = min_x = model->vertices[3 + 0];
    max_y = min_y = model->vertices[3 + 1];
    max_z = min_z = model->vertices[3 + 2];
    for (int i = 1; i <= model->numvertices; i++) {
        if (max_x < model->vertices[3 * i + 0])
            max_x = model->vertices[3 * i + 0];
        if (min_x > model->vertices[3 * i + 0])
            min_x = model->vertices[3 * i + 0];       
        if (max_y < model->vertices[3 * i + 1])
            max_y = model->vertices[3 * i + 1];
        if (min_y > model->vertices[3 * i + 1])
            min_y = model->vertices[3 * i + 1];        
        if (max_z < model->vertices[3 * i + 2])
            max_z = model->vertices[3 * i + 2];
        if (min_z > model->vertices[3 * i + 2])
            min_z = model->vertices[3 * i + 2];
    }
	vertexArray.push_back({max_x, max_y, min_z});
	vertexArray.push_back({min_x, max_y, min_z});
	vertexArray.push_back({min_x, min_y, min_z});
	vertexArray.push_back({max_x, min_y, min_z});
	vertexArray.push_back({max_x, min_y, max_z});
	vertexArray.push_back({max_x, max_y, max_z});
	vertexArray.push_back({min_x, max_y, max_z});
	vertexArray.push_back({min_x, min_y, max_z});
}
/*
	   6--------5
	  /|	   /|
	 / |	  / |
	1--|-----0  |
	|  |	 |	|
	|  7-----|--4
	| / 	 | /
	|/		 |/
	2--------3
*/

void Object::updateReferencePoints()
{
	centroid = glm::vec3((vertexArray[6][0]+vertexArray[0][0])/2, (vertexArray[6][1]+vertexArray[0][1])/2, (vertexArray[6][2]+vertexArray[0][2])/2);
	leftAnchor = glm::vec3((vertexArray[6][0]+vertexArray[1][0])/2, (vertexArray[6][1]+vertexArray[1][1])/2, (vertexArray[6][2]+vertexArray[1][2])/2);
	topAnchor = glm::vec3((vertexArray[0][0]+vertexArray[1][0])/2, (vertexArray[0][1]+vertexArray[1][1])/2, (vertexArray[0][2]+vertexArray[1][2])/2);
}

void Object::updateVertexArray()
{	   
	for(int i = 0; i < vertexArray.size(); i++)
	{
		glm::vec4 vec(vertexArray[i][0], vertexArray[i][1], vertexArray[i][2], 1.0f);
		vec = transformationMatrix * vec;
		vertexArray[i][0] = vec.x;
		vertexArray[i][1] = vec.y;
		vertexArray[i][2] = vec.z;
	}
}

void Object::updateBoundingBoxToTransforms()
{	
	glm::vec4 inv;
	transformationMatrix = glm::inverse(transformationMatrix);
	updateVertexArray();
	updateReferencePoints();
	transformationMatrix = glm::mat4();
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(transX, transY, transZ));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotX), glm::vec3(1.0, 0.0, 0.0));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotY), glm::vec3(0.0, 1.0, 0.0)); 
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotZ), glm::vec3(0.0, 0.0, 1.0));	        
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scaleX, scaleY, scaleZ));  
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(centerX, centerY, centerZ));
    updateVertexArray();	
	updateReferencePoints();
}

bool Object::checkIntersection(glm::vec3 near, glm::vec3 far, float & distance)
{
	glm::mat4 sc;
	sc = glm::translate(sc, glm::vec3(transX, transY, transZ));
    sc = glm::rotate(sc, glm::radians(rotX), glm::vec3(1.0, 0.0, 0.0));
    sc = glm::rotate(sc, glm::radians(rotY), glm::vec3(0.0, 1.0, 0.0)); 
    sc = glm::rotate(sc, glm::radians(rotZ), glm::vec3(0.0, 0.0, 1.0));	        
    sc = glm::scale(sc, glm::vec3(scaleX, scaleY, scaleZ));  
    sc = glm::translate(sc, glm::vec3(centerX, centerY, centerZ));
	glm::vec3 origin = near;
	glm::vec3 direction(far.x-near.x, far.y-near.y, far.z-near.z);
	direction = glm::normalize(direction);
	glm::vec4 vec_min(min_x, min_y, min_z, 1.0f);
	glm::vec4 vec_max(max_x, max_y, max_z, 1.0f);
	vec_min = sc * vec_min;
	vec_max = sc * vec_max;
	glm::vec3 min(vec_min.x, vec_min.y, vec_min.z);
	glm::vec3 max(vec_max.x, vec_max.y, vec_max.z);
	
	return TestRayOBBIntersection(origin, direction, min, max, glm::mat4(), distance);
}

bool Object::testX(glm::mat4 ModelMatrix, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float & tMin, float & tMax)
{
	glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
	float e = glm::dot(xaxis, delta);
	float f = glm::dot(ray_direction, xaxis);

	if ( fabs(f) > 0.001f ){

		float t1 = (e+aabb_min.x)/f;
		float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
		if (t1>t2){
			float w=t1;t1=t2;t2=w; // swap t1 and t2
		}
		if ( t2 < tMax )
			tMax = t2;
		if ( t1 > tMin )
			tMin = t1;
		if (tMax < tMin )
			return false;
	}else{
		if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
			return false;
	}
	return true;
}

bool Object::testY(glm::mat4 ModelMatrix, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float & tMin, float & tMax)
{
	glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
	float e = glm::dot(yaxis, delta);
	float f = glm::dot(ray_direction, yaxis);
	if ( fabs(f) > 0.001f ){
		float t1 = (e+aabb_min.y)/f;
		float t2 = (e+aabb_max.y)/f;
		if (t1>t2){float w=t1;t1=t2;t2=w;}
		if ( t2 < tMax )
			tMax = t2;
		if ( t1 > tMin )
			tMin = t1;
		if (tMin > tMax)
			return false;
	}else{
		if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
			return false;
	}
	return true;
}

bool Object::testZ(glm::mat4 ModelMatrix, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float & tMin, float & tMax)
{
	glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
	float e = glm::dot(zaxis, delta);
	float f = glm::dot(ray_direction, zaxis);
	if ( fabs(f) > 0.001f ){
		float t1 = (e+aabb_min.z)/f;
		float t2 = (e+aabb_max.z)/f;
		if (t1>t2){float w=t1;t1=t2;t2=w;}
		if ( t2 < tMax )
			tMax = t2;
		if ( t1 > tMin )
			tMin = t1;
		if (tMin > tMax)
			return false;
	}else{
		if(-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
			return false;
	}
	return true;
}


bool Object::TestRayOBBIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix, float& intersection_distance)
{
	// Intersection method from Real-Time Rendering and Essential Mathematics for Games
	float tMin = 0.0f;
	float tMax = 100000.0f;
	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);
	glm::vec3 delta = OBBposition_worldspace - ray_origin;	

	if(testX(ModelMatrix, delta, ray_direction, aabb_min, aabb_max, tMin, tMax) && testY(ModelMatrix, delta, ray_direction, aabb_min, aabb_max, tMin, tMax) && testZ(ModelMatrix, delta, ray_direction, aabb_min, aabb_max, tMin, tMax))
		return true;	
	intersection_distance = tMin;
	return false;
}

std::vector<std::vector<float>> Object::getBoundingBox()
{
	return vertexArray;
}

void Object::front(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// front face =================
    glVertex3fv(v0);    // v0-v1-v2
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v2);    // v2-v3-v0
    glVertex3fv(v3);
    glVertex3fv(v0);
}

void Object::right(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// right face =================
    glVertex3fv(v0);    // v0-v3-v4
    glVertex3fv(v3);
    glVertex3fv(v4);
    glVertex3fv(v4);    // v4-v5-v0
    glVertex3fv(v5);
    glVertex3fv(v0);
}

void Object::top(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// top face ===================
    glVertex3fv(v0);    // v0-v5-v6
    glVertex3fv(v5);
    glVertex3fv(v6);
    glVertex3fv(v6);    // v6-v1-v0
    glVertex3fv(v1);
    glVertex3fv(v0);
}

void Object::left(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// left face ===================
    glVertex3fv(v6);    // 
    glVertex3fv(v7);
    glVertex3fv(v2);
    glVertex3fv(v2);    // 
    glVertex3fv(v1);
    glVertex3fv(v6);
}

void Object::back(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	 // back face ===================
    glVertex3fv(v5);    // 
    glVertex3fv(v6);
    glVertex3fv(v7);
    glVertex3fv(v7);    // 
    glVertex3fv(v4);
    glVertex3fv(v5);
}

void Object::bottom(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	 // bottom face ===================
    glVertex3fv(v7);    // 
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v3);    // 
    glVertex3fv(v4);
    glVertex3fv(v7);
}
void Object::DrawBoundingBox()
{	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Activar wireframe		
	glColor3f(1, 1, 0);
	float * v0 = &vertexArray[0][0];
	float * v1 = &vertexArray[1][0];
	float * v2 = &vertexArray[2][0];
	float * v3 = &vertexArray[3][0];
	float * v4 = &vertexArray[4][0];
	float * v5 = &vertexArray[5][0];
	float * v6 = &vertexArray[6][0];
	float * v7 = &vertexArray[7][0];
	glBegin(GL_TRIANGLES);  // draw a cube with 12 triangles	
    front(v0,v1,v2,v3,v4,v5,v6,v7);
    right(v0,v1,v2,v3,v4,v5,v6,v7);
    top(v0,v1,v2,v3,v4,v5,v6,v7);
    left(v0,v1,v2,v3,v4,v5,v6,v7);
    back(v0,v1,v2,v3,v4,v5,v6,v7);
    bottom(v0,v1,v2,v3,v4,v5,v6,v7);             
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  	
	disableParams();	
	glPointSize(5);
	glBegin(GL_POINTS);      
    glColor3f(1.0, 0.0, 0.0);        
    glVertex3f(centroid.x, centroid.y, centroid.z); //Centroid
    glColor3f(1.0, 1.0, 0.0);        
    glVertex3f(leftAnchor.x, leftAnchor.y, leftAnchor.z); //Left anchor
    glColor3f(0.0, 1.0, 0.0);        
    glVertex3f(topAnchor.x, topAnchor.y, topAnchor.z); //Right anchor
    glEnd();        
    enableParams();
}

Object::Object()
{
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	transX = 0;
	transY = 0;
	transZ = 0;	
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	centerX = 0;
	centerY = 0;
	centerZ = 0;	
	distance = 0;
}

Object::~Object()
{
	
}

Object::Object(const char * filename):Object()
{
	model = loadModel(filename);
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

Object::Object(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ, const char * filename) : scaleX(_scaleX), scaleY(_scaleY), scaleZ(_scaleZ), transX(_x), transY(_y), transZ(_z), rotX(_rotX), rotY(_rotY), rotZ(_rotZ)
{
	distance = 0;
	model = loadModel(filename);	
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

Object::Object(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ, const char * filename) : scaleX(_scaleX), scaleY(_scaleY), scaleZ(_scaleZ), transX(_x), transY(_y), transZ(_z), rotX(_rotX), rotY(_rotY), rotZ(_rotZ), centerX(_centerX), centerY(_centerY), centerZ(_centerZ)
{
	distance = 0;
	model = loadModel(filename);
	initBoundingBox();	
	updateBoundingBoxToTransforms();
}

void Object::drawModel(GLuint _mode)
{		
    glPushAttrib(GL_ALL_ATTRIB_BITS);     
        if (model)
            glmDraw(model, _mode);
    glPopAttrib();     	
}

void Object::setDistance(float _distance)
{
	distance = _distance;
}

float Object::getDistance()
{
	return distance;
}


void Object::setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	transX = _x;
	transY = _y;
	transZ = _z;	
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;
	centerX = _centerX;
	centerY = _centerY;
	centerZ = _centerZ;
	updateBoundingBoxToTransforms();
}

void Object::setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ)
{	
	if(initialParameterMap.size() <= 0)
	{
		initialParameterMap["scaleX"] = _scaleX;
		initialParameterMap["scaleY"] = _scaleY;
		initialParameterMap["scaleZ"] = _scaleZ;
		initialParameterMap["transX"] = _x;
		initialParameterMap["transY"] = _y;
		initialParameterMap["transZ"] = _z;
		initialParameterMap["rotX"] = _rotX;
		initialParameterMap["rotY"] = _rotY;
		initialParameterMap["rotZ"] = _rotZ;
		initialParameterMap["centerX"] = centerX;
		initialParameterMap["centerY"] = centerY;
		initialParameterMap["centerZ"] = centerZ;
	}	
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	transX = _x;
	transY = _y;
	transZ = _z;	
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;	
	updateBoundingBoxToTransforms();
}

void Object::setTranslation(float x, float y, float z)
{
	transX = x;
	transY = y;
	transZ = z;	
	updateBoundingBoxToTransforms();
}

void Object::setScale(float x, float y, float z)
{
	scaleX = x;
	scaleY = y;
	scaleZ = z;
	updateBoundingBoxToTransforms();
}

void Object::setRotation(float x, float y, float z)
{	
	rotX = x;
	rotY = y;
	rotZ = z;
	updateBoundingBoxToTransforms();
}

void Object::addTranslation(float x, float y, float z)
{
	transX += x;
	transY += y;
	transZ += z;
	updateBoundingBoxToTransforms();
}
void Object::addRotation(float x, float y, float z)
{
	rotX += x;
	rotY += y;
	rotZ += z;
	updateBoundingBoxToTransforms();
}
void Object::addScale(float x, float y, float z)
{
	scaleX += x;
	scaleY += y;
	scaleZ += z;
	updateBoundingBoxToTransforms();
}

std::map<std::string, float> Object::getParams()
{
	parameterMap["scaleX"] = scaleX;
	parameterMap["scaleY"] = scaleY;
	parameterMap["scaleZ"] = scaleZ;
	parameterMap["transX"] = transX;
	parameterMap["transY"] = transY;
	parameterMap["transZ"] = transZ;
	parameterMap["rotX"] = rotX;
	parameterMap["rotY"] = rotY;
	parameterMap["rotZ"] = rotZ;
	parameterMap["centerX"] = centerX;
	parameterMap["centerY"] = centerY;
	parameterMap["centerZ"] = centerZ;	
	return parameterMap;
}

std::map<std::string, float> Object::getInitialParams()
{
	return initialParameterMap;
}

void Object::setParamsByMap(std::map<std::string, float> _newParams)
{
	scaleX = _newParams["scaleX"];
	scaleY = _newParams["scaleY"];
	scaleZ = _newParams["scaleZ"];
	transX = _newParams["transX"];
	transY = _newParams["transY"];
	transZ = _newParams["transZ"];
	rotX = _newParams["rotX"];
	rotY = _newParams["rotY"];
	rotZ = _newParams["rotZ"];
	centerX = _newParams["centerX"];
	centerY = _newParams["centerY"];
	centerZ = _newParams["centerZ"];	
	updateBoundingBoxToTransforms();
}

glm::vec3 Object::getCentroid()
{
	return centroid;
}

glm::vec3 Object::getTopAnchor()
{
	return topAnchor;
}

glm::vec3 Object::getLeftAnchor()
{
	return leftAnchor;
}

GLMmodel * Object::getModel()
{
	return model;
}

void Object::resetParams()
{
	setParamsByMap(initialParameterMap);
}
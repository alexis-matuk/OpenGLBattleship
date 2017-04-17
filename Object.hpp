#ifndef Object_H
#define Object_H

#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
#endif
#include "aggregateFuncs.hpp"

class Object{	
protected:
	float scaleX;
	float scaleY;
	float scaleZ;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float centerX;
	float centerY;
	float centerZ;
	float distance;
	GLMmodel * model;	
	std::map<std::string, float> parameterMap;
	float min_x;
	float max_x;
    float min_y; 
    float max_y;
    float min_z; 
    float max_z;
    glm::vec3 centroid;
    glm::vec3 leftAnchor;
    glm::vec3 topAnchor;
   	std::vector<std::vector<float>> vertexArray;
   	glm::mat4 transformationMatrix; 
   	std::string name = "";
   	std::string type = "Object";
public:	
	virtual void Draw();
	Object();
	~Object();
	Object(const char * filename);
	Object(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ, const char * filename);	
	Object(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ, const char * filename);	
	void setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);
	void setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);
	void DrawAxis(float scale);
	void setTranslation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void addTranslation(float x, float y, float z);
	void addRotation(float x, float y, float z);
	void addScale(float x, float y, float z);
	GLMmodel * getModel();
	void drawModel();
	void initBoundingBox();	
	void DrawBoundingBox();
	void updateBoundingBoxToTransforms();
	void updateVertexArray();	
	virtual void updateReferencePoints();
	std::vector<std::vector<float>> getBoundingBox();
	std::map<std::string, float> getParams();
	void setName(std::string _name);
	std::string getName();
	bool TestRayOBBIntersection(
	glm::vec3 ray_origin,        // Ray origin, in world space
	glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
	glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
	glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
	glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
	);
	bool checkIntersection(glm::vec3 near, glm::vec3 far, float & distance);
	void setDistance(float _distance);
	float getDistance();
	glm::vec3 getCentroid();
	glm::vec3 getTopAnchor();
};

#endif

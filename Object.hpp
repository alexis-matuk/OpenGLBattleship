#ifndef Object_H
#define Object_H
#include "HeaderInclude.hpp"
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
	std::map<std::string, float> initialParameterMap;
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
	virtual void Draw(GLuint _mode);	
	Object();
	~Object();
	Object(const char * filename);
	Object(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ, const char * filename);	
	Object(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ, const char * filename);	
	void setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);
	void setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);	
	void setTranslation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void addTranslation(float x, float y, float z);
	void addRotation(float x, float y, float z);
	void addScale(float x, float y, float z);
	GLMmodel * getModel();
	void drawModel(GLuint _mode);	
	void initBoundingBox();	
	void DrawBoundingBox();
	void updateBoundingBoxToTransforms();
	virtual void updateVertexArray();	
	virtual void updateReferencePoints();
	std::vector<std::vector<float>> getBoundingBox();
	std::map<std::string, float> getParams();
	std::map<std::string, float> getInitialParams();
	void setParamsByMap(std::map<std::string, float> _newParams);
	void setName(std::string _name);
	std::string getName();
	bool testX(glm::mat4 ModelMatrix, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float & tMin, float & tMax);
	bool testY(glm::mat4 ModelMatrix, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float & tMin, float & tMax);
	bool testZ(glm::mat4 ModelMatrix, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float & tMin, float & tMax);
	bool TestRayOBBIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix, float& intersection_distance);
	bool checkIntersection(glm::vec3 near, glm::vec3 far, float & distance);
	void setDistance(float _distance);
	float getDistance();
	glm::vec3 getCentroid();
	glm::vec3 getTopAnchor();
	glm::vec3 getLeftAnchor();
	void resetParams();	
	void front(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void back(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void left(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void right(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void top(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void bottom(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
};

#endif

#include "aggregateFuncs.hpp"
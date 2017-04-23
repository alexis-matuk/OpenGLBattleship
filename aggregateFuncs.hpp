#include "HeaderInclude.hpp"
class Map;
class Ship;
class Object;
class Tile;
class UIHandler;
class SceneManager;

extern int frame;
extern int currenttime;
extern int timebase;
extern bool rotatingXUp;
extern bool rotatingXDown;
extern bool rotatingYLeft;
extern bool rotatingYRight;
extern bool rotatingZLeft;
extern bool rotatingZRight;
extern bool zoomingIn;
extern bool zoomingOut;
extern float xSpeed;
extern float ySpeed;
extern float zSpeed;
extern float camSpeed;
extern double _left;
extern double _right;
extern double _bottom;
extern double _top;
extern double _zNear;
extern double _zFar;
extern double fovy;
extern double prev_z;
extern int ww, wh;
extern float xRot;
extern float yRot;
extern float zRot;
extern float camZ;
extern int wireframe;
extern Map * map;
extern GLfloat light_ambient[4];
extern GLfloat light_diffuse[4];
extern GLfloat light_specular[4];
extern GLfloat light_position[4];
extern GLfloat mat_ambient[4];
extern GLfloat mat_diffuse[4];
extern GLfloat mat_specular[4];
extern GLfloat high_shininess[1];
extern int window; 
extern bool down;
extern float lastx;
extern float lasty;
extern std::vector<std::vector<float>> points;
extern GLint viewport[4];
extern GLdouble modelview[16];
extern GLdouble projection[16];
extern float nx;
extern float ny;
extern float nz;
extern float fx;
extern float fy;
extern float fz;
extern bool valid;

extern UIHandler* UI;
extern SceneManager * Scene;

extern GLuint viewMode;//Modo de visualización
extern GLuint texture[1];
extern bool debug;

extern char const* fontFile; // Just a string with the path to the font file    

void DrawModel(GLMmodel* model);
void DrawModel(GLMmodel* model, float centerX, float centerY, float centerZ, float scaleX, float scaleY, float scaleZ, float x, float y, float z, float angle, float rotX, float rotY, float rotZ);
GLMmodel* loadModel(const char* filename);
void LoadGLTextures();
void enableParams();
void disableParams();
void drawRaycast();
void disableUIParams();
void enableUIParams();
void setPanelViewPort();
void setButtonViewPort();
void setWorldViewPort();
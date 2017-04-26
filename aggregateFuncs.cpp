#include "aggregateFuncs.hpp"

GLuint viewMode = GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE | GLM_2_SIDED;
GLuint textureMode = GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE | GLM_2_SIDED;
GLuint noTextureMode = GLM_SMOOTH | GLM_MATERIAL | GLM_2_SIDED;
GLuint texture[1];
bool debug = false;

int frame = 0;
int currenttime = 0;
int timebase = 0;
bool rotatingXUp = false;
bool rotatingXDown = false;
bool rotatingYLeft = false;
bool rotatingYRight = false;
bool rotatingZLeft = false; 
bool rotatingZRight = false;
bool zoomingIn = false;
bool zoomingOut = false;
float xSpeed = 0.1f * SPEED_MULT;
float ySpeed = 0.05f * SPEED_MULT;
float zSpeed = 0.1f * SPEED_MULT;
float camSpeed = 0.005f * SPEED_MULT;
double _left = 0.0;
double _right = 0.0;
double _bottom = 0.0;
double _top = 0.0;
double _zNear = 0.1;
double _zFar = 20.0;
double fovy = 45.0;
double prev_z = 0;
float xRot = 0;
float yRot = 0;
float zRot = 0;
float camZ = 0;

float xRot_opponent = 0;
float yRot_opponent = 0;
float zRot_opponent = 0;
float camZ_opponent = 0;


int wireframe = 0;
Map * map = nullptr;
Map * opponentMap = nullptr;
GLfloat light_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[4] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat mat_ambient[4] = { 1, 1, 1, 1.0 };
GLfloat mat_diffuse[4] = { 1, 1, 1, 1.0 };
GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[1] = { 100.0 };
bool down = false;
int ww, wh;
int window; 
float lastx;
float lasty;
std::vector<std::vector<float>> points;
GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];
float nx;
float ny;
float nz;
float fx;
float fy;
float fz;
bool valid = false;

UIHandler* UI = nullptr;
SceneManager * Scene = nullptr;

char const* fontFile = FONT_FILE; // Just a string with the path to the font file  

Ship * menuShip = nullptr;

float menuShipRot = 0;

int animationCounter = 0;
int sceneStartTime = -1;

Object * object = nullptr;

GLMmodel * shipModel = nullptr;
GLMmodel * whitePinModel = nullptr;
GLMmodel * redPinModel = nullptr;
GLMmodel * missileModel = nullptr;

Missile * missile = nullptr;

bool shooting = false;

void DrawModel(GLMmodel* model, GLuint _mode)
{            
    glPushAttrib(GL_ALL_ATTRIB_BITS);     
        if (model)
            glmDraw(model, _mode);
    glPopAttrib();     
}


/* Función para cagar un modelo */
GLMmodel* loadModel(const char* filename)
{
	GLMmodel* model = nullptr;
    if (!model) {		/* load up the model */
	model = glmReadOBJ(filename);
	if (!model) {
	    std::cout << "\nUsage: objviewV2 <-s> <obj filename>\n" << std::endl;
	    exit(0);
	}
	glmUnitize(model);
	glmVertexNormals(model, 90.0, GL_TRUE);
    }
    return model;
}

// Load Bitmaps And Convert To Textures
void LoadGLTextures() { 
 
    // Create Texture   
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    int width, height;
    unsigned char* image =SOIL_load_image("water.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
};

void enableParams()
{
    glEnable(GL_LIGHTING);    
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
}

void disableParams()
{
    glDisable(GL_LIGHTING);    
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);
}

void drawRaycast()
{
    glDisable(GL_LIGHTING);    
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.5, 0.0);                
    glVertex3f(nx,ny,nz);
    glVertex3f(fx,fy,fz);
    glEnd();     
     
    glPointSize(5);
    glBegin(GL_POINTS);             
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(nx,ny,nz);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(fx,fy,fz);
    glEnd();
    glPointSize(1);
    glLineWidth(1);

    glEnable(GL_LIGHTING);    
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
}

void enableUIParams()
{    
    glEnable(GL_TEXTURE_2D);       
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
}

void disableUIParams()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


void setPanelViewPort()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, ww, 0, wh);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    
}

void setButtonViewPort()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,ww,wh,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setWorldViewPort()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();        
    gluPerspective(45.0f,(GLfloat)ww/(GLfloat)wh,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void modifyCamera()
{
    if(rotatingXUp)
    {
        xRot -= xSpeed * (currenttime - timebase);
    }
    if(rotatingXDown)
    {
        xRot += xSpeed * (currenttime - timebase);            
    }
    if(rotatingYLeft)
    {
        yRot -= ySpeed * (currenttime - timebase);
    }
    if(rotatingYRight)
    {
        yRot += ySpeed * (currenttime - timebase);            
    }
    if(rotatingZLeft)
    {
        zRot -= zSpeed * (currenttime - timebase);
    }
    if(rotatingZRight)
    {
        zRot += zSpeed * (currenttime - timebase);            
    }
    if(zoomingIn)
    {
        if(camZ >= MIN_CAM_Z)
            camZ -= camSpeed * (currenttime - timebase);            
    }
    if(zoomingOut)
    {
        if(camZ <= MAX_CAM_Z)
            camZ += camSpeed * (currenttime - timebase);            
    }    
}

void modifyCameraInGame()
{
    if(rotatingXUp)
    {
        xRot_opponent -= xSpeed * (currenttime - timebase);
    }
    if(rotatingXDown)
    {
        xRot_opponent += xSpeed * (currenttime - timebase);            
    }
    if(rotatingYLeft)
    {
        yRot_opponent -= ySpeed * (currenttime - timebase);
    }
    if(rotatingYRight)
    {
        yRot_opponent += ySpeed * (currenttime - timebase);            
    }
    if(rotatingZLeft)
    {
        zRot_opponent -= zSpeed * (currenttime - timebase);
    }
    if(rotatingZRight)
    {
        zRot_opponent += zSpeed * (currenttime - timebase);            
    }
    if(zoomingIn)
    {
        if(camZ_opponent >= MIN_CAM_Z)
            camZ_opponent -= camSpeed * (currenttime - timebase);            
    }
    if(zoomingOut)
    {
        if(camZ_opponent <= MAX_CAM_Z)
            camZ_opponent += camSpeed * (currenttime - timebase);            
    }    
}

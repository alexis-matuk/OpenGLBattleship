#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif	// Header File For The OpenGL32 Library

#include "Map.hpp"
#include "Ship.hpp"

#define START_Z 6.7
#define SPEED_MULT 0.5
// #define START_Z 1


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



/* Valores ortográficos para la perspectiva */
double _left = 0.0;
double _right = 0.0;
double _bottom = 0.0;
double _top = 0.0;
double _zNear = 0.1;
double _zFar = 20.0;
double fovy = 45.0;
double prev_z = 0;
int ww, wh;

/* Rotación de la escena y zoom de la cámara */
float xRot = 0;
float yRot = 0;
float zRot = 0;
float camZ = 0;
int wireframe = 0;

Map * map = nullptr;
GLMmodel * test = nullptr;
Tile * tile = nullptr;
Tile * tile_2 = nullptr;
Tile * tile_3 = nullptr;
Tile * tile_4 = nullptr;
Ship * ship = nullptr;

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };

/* The number of our GLUT window */
int window; 
bool down = false;
float lastx;
float lasty;
std::vector<std::vector<float>> points;

GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];

float nx,ny,nz,fx,fy,fz;
bool valid = false;;

/* Funciones de GLUT */
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Display(void);
void SpecialInput(int key, int x, int y);
void SpecialInputUp(int key, int x, int y);
void LoadGLTextures();
void mouseHandlerPickingScene(int button, int state, int x, int y);
void updateMatrices();
void shipMotion(int x, int y);

void updateMatrices()
{
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
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
        camZ -= camSpeed * (currenttime - timebase);            
    }
    if(zoomingOut)
    {
        camZ += camSpeed * (currenttime - timebase);            
    }
}

void idle()
{
   frame++;
   currenttime = glutGet(GLUT_ELAPSED_TIME);
   if (currenttime - timebase > 0.5) 
   {
        modifyCamera();
        timebase = currenttime;    
        frame = 0;        
        glutPostRedisplay();
   }  
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float float_x, float_y;                     // loop counters.
    LoadGLTextures();				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Clear The Background Color To Blue 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.2f,1000.0f);	// Calculate The Aspect Ratio Of The Window
    glMatrixMode(GL_MODELVIEW);        
}

/*Función principal*/
int main(int argc, char **argv)
{	
    glutInit(&argc, argv);       
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    glutInitWindowSize(1100, 768);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Battleship");
    glutDisplayFunc(&Display);
    // glutFullScreen();   
    glutIdleFunc(&Display); 
    glutReshapeFunc(&Reshape);
    InitGL(1100, 768);
    glutKeyboardFunc(&Keyboard);
    glutKeyboardUpFunc(&KeyboardUp);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialInputUp);
    glutMouseFunc(mouseHandlerPickingScene); 
    glutMotionFunc(shipMotion);   
    glutIdleFunc(idle);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1);           
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);  
	glEnable(GL_LIGHTING);    
	glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    map = new Map();  
    tile = new Tile();
    tile->setParams(0.6,0.6,0.6, 0,0,0, 90,0,0);    
    // tile_2 = new Tile();
    // tile_2->setParams(0.6,0.6,0.6, 0.42,0,0, 90,0,0);
    // tile_3 = new Tile();
    // tile_3->setParams(0.6,0.6,0.6, 0.42,0.42,0, 90,0,0);
    // tile_4 = new Tile();
    // tile_4->setParams(0.6,0.6,0.6, 0.42,0.84,0, 90,0,0);
    // ship = new Ship();
    // test = loadModel("Objects/tile.obj");

    // std::map<std::string,float> firstShipParams = map->getShip(0).getParams();
    // for (std::map<std::string,float>::iterator it=firstShipParams.begin(); it!=firstShipParams.end(); ++it)
    // std::cout << it->first << " => " << it->second << '\n';      
    /*
        Objects/Bladesong/Bladesong.obj - 2
        Objects/Gunboat/Gunboat.obj - 3
        Objects/Prestes/Prestes.obj - 3  
        Objects/Submarino/i400.obj - 4        
        Objects/Carrier/carrier.obj - 5            
    */     
    // sleep(1);  
    glutMainLoop();    
    return 0;        
}



/* Función de Reshape */
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    ww = w;
    wh = h;
    _top = 1.0;
    _bottom = -1.0;
    _left = -(double) w / (double) h;
    _right = -_left;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    // gluPerspective(fovy, (double) w / (double) h, _zNear, _zFar);
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{

    switch (key) {
    case ' ':{        
        Ship * hit = map->getCurrentShipSelected();
        if(hit != nullptr)
        {
            Map::Direction current_dir = hit->getDirection();                           
            if(current_dir == Map::Direction::TOP_BOTTOM)
            {
                hit->addRotation(0, 90, 0);
                hit->setDirection(Map::Direction::LEFT_RIGHT);
            }
            else
            {
                hit->addRotation(0, -90, 0);
                hit->setDirection(Map::Direction::TOP_BOTTOM);
            }                
        }
    break;}
	case 'w':
		// xRot-=5;
        rotatingXUp = true;
	break;
	case 's':
		// xRot+=5;
        rotatingXDown = true;
	break; 
	case 'a':
        rotatingYLeft = true;
		// yRot+=5;
	break;
	case 'd':
        rotatingYRight = true;
		// yRot-=5;
	break; 
	case 'e':
        rotatingZLeft = true;
		// zRot-=5;
	break; 
	case 'q':
        rotatingZRight = true;
		// zRot+=5;
	break; 
    case 'p':{
	    wireframe = !wireframe;
	    break;
	}
    case 27:
	exit(0);
	break;
    default:{
	    break;
	}			/* flush all other input                                 */
    }    
    glutPostRedisplay();	/* redisplay afterword */
}

void KeyboardUp(unsigned char key, int x, int y)
{
    switch (key) {   
    case 'w':
        rotatingXUp = false;
    break;
    case 's':
        rotatingXDown = false;
    break; 
    case 'a':
        rotatingYLeft = false;
    break;
    case 'd':
        rotatingYRight = false;
    break; 
    case 'e':
        rotatingZLeft = false;
    break; 
    case 'q':
        rotatingZRight = false;
    break; 
    default:{
        break;
    }           /* flush all other input                                 */
    }
    glutPostRedisplay();    /* redisplay afterword */
}

/* Función para detectar las flechas */
void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			zoomingIn = true;
		break;	
		case GLUT_KEY_DOWN:
			zoomingOut = true;
		break;
	}    
	glutPostRedisplay();
}

/* Función para detectar las flechas */
void SpecialInputUp(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            zoomingIn = false;
        break;  
        case GLUT_KEY_DOWN:
            zoomingOut = false;
        break;
    }
    glutPostRedisplay();
}

void shipMotion(int x, int y)
{
    Ship * currentShipSelected = map->getCurrentShipSelected();
    if( currentShipSelected!= nullptr && valid)
    {        
        float z = currentShipSelected->getParams()["centerZ"] + currentShipSelected->getParams()["transZ"];

        float winX = (float)x;
        float winY = viewport[1] + (float)viewport[3] - (float)y;

        GLdouble near[3], far[3];  // already computed as above
        // 0.1 is for giving a depth offset from the eye position
        gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
        gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);   

        if(near[2] == far[2])     // this means we have no solutions
           return;

        GLfloat t = (near[2] - z) / (near[2] - far[2]);

        // so here are the desired (x, y) coordinates
        GLfloat world_x = near[0] + (far[0] - near[0]) * t,
                world_y = near[1] + (far[1] - near[1]) * t;
        currentShipSelected->setTranslation(world_x, world_y, z);
    }    
}

void mouseHandlerPickingScene(int button, int state, int x, int y)
{
    //Code from http://nehe.gamedev.net/article/using_gluunproject/16013/    
    GLfloat winX, winY, winZ;    
    GLdouble near[3];
    GLdouble far[3];
    std::vector<float> res;    
    
    /*Obtenido de http://stackoverflow.com/questions/113352/opengl-projecting-mouse-click-onto-geometry*/

    winX = (float)x;
    winY = viewport[1] + (float)viewport[3] - (float)y;
    
    // 0.1 is for giving a depth offset from the eye position
    gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
    gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);    

    glm::vec3 vec_near(near[0], near[1], near[2]);
    glm::vec3 vec_far(far[0], far[1], far[2]);

    float dist;
    Ship * hit = map->getShipHit(vec_near, vec_far, dist);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        valid = true;    
        if(hit !=  nullptr)
        {                               
            if(hit->isPlaced())
            {
                std::cout << "Unclipping " << hit->getName() << std::endl;
                map->unclipShipFromGrid(hit);
            }   
            map->setCurrentShipSelected(hit);
            std::cout << "I clicked: \"" << hit->getName() << "\"" << std::endl;            
        }
    }
    // if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    // {
    //     if(hit != nullptr)
    //     {
    //         if(hit->isPlaced())
    //         {
    //             Map::Direction current_dir = hit->getDirection();
    //             map->unclipShipFromGrid(hit);                            
    //             if(current_dir == Map::Direction::TOP_BOTTOM)
    //             {
    //                 hit->addRotation(0, 90, 0);
    //                 hit->setDirection(Map::Direction::LEFT_RIGHT);
    //             }
    //             else
    //             {
    //                 hit->addRotation(0, -90, 0);
    //                 hit->setDirection(Map::Direction::TOP_BOTTOM);
    //             }
    //             map->clipAndUpdateShip(hit);
    //         }
    //     }
    // }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {        
        Ship * current_ship = map->getCurrentShipSelected();
        map->clipAndUpdateShip(current_ship);        
        valid = false;
        map->setCurrentShipSelected(nullptr);
    }    
    glutPostRedisplay();
}
/* Función de display */
void Display(void)
{				 				    
	glLoadIdentity();	
	gluLookAt(0, 0, START_Z+camZ, 0, 0, camZ, 0, 1, 0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      
	glPushMatrix();
		if (wireframe)
		    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Activar wireframe
		else
		    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        
		glRotatef(xRot,1,0,0);	
		glRotatef(yRot,0,1,0);	
		glRotatef(zRot,0,0,1);
        updateMatrices();        

        if(debug)
        {
            // glDisable(GL_LIGHTING);    
            // glDisable(GL_LIGHT0);
            // glDisable(GL_DEPTH_TEST);
            // glDisable(GL_NORMALIZE);
            // glDisable(GL_TEXTURE_2D);

            // glLineWidth(2);
            // glBegin(GL_LINES);
            // glColor3f(0.0, 0.0, 1.0);                
            // glVertex3f(nx,ny,nz);
            // glVertex3f(fx,fy,fz);
            // glEnd();     
             
            // glPointSize(5);
            // glBegin(GL_POINTS);             
            // glColor3f(0.0, 1.0, 0.0);
            // glVertex3f(nx,ny,nz);
            // glColor3f(1.0, 0.0, 0.0);
            // glVertex3f(fx,fy,fz);
            // glEnd();

            // glLineWidth(1);

            // glEnable(GL_LIGHTING);    
            // glEnable(GL_LIGHT0);
            // glEnable(GL_DEPTH_TEST);
            // glEnable(GL_NORMALIZE);
            // glEnable(GL_TEXTURE_2D); 
        }        
        // tile->Draw();            
        // tile->DrawBoundingBox();             
       map->Draw();               
          // ship->Draw();
          // ship->DrawAxis(1.0f);	         
    glPopMatrix(); 
    glFlush();
    glutSwapBuffers();
}

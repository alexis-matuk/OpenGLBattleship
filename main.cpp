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
#define SPEED_MULT 2
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

/* Funciones de GLUT */
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Display(void);
void SpecialInput(int key, int x, int y);
void SpecialInputUp(int key, int x, int y);
void LoadGLTextures();

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
        yRot += ySpeed * (currenttime - timebase);
    }
    if(rotatingYRight)
    {
        yRot -= ySpeed * (currenttime - timebase);            
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
   if (currenttime - timebase > 2.739726) 
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
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    glMatrixMode(GL_MODELVIEW);    
}

GLint viewport[4];
GLdouble mvmatrix[16];
GLdouble projmatrix[16];
float realy;
GLdouble wx1;
GLdouble wy1;
GLdouble wz1;
GLdouble wx2;
GLdouble wy2;
GLdouble wz2;
/* ARGSUSED3 */
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastx = x;
            lasty = y;
            std::cout << "=== 2D ===" << std::endl;
            std::cout << "x: " << x << ", y: " << y << std::endl;

            glGetIntegerv( GL_VIEWPORT, viewport );            
            glGetDoublev( GL_MODELVIEW_MATRIX, mvmatrix );
            glGetDoublev( GL_PROJECTION_MATRIX, projmatrix );
            gluUnProject( (GLdouble) x, (GLdouble) y, 1, mvmatrix, projmatrix, viewport, &wx1, &wy1, &wz1 );
            gluUnProject( (GLdouble) x, (GLdouble) y, 0, mvmatrix, projmatrix, viewport, &wx2, &wy2, &wz2 );
            
            std::cout << "=== 3D ===" << std::endl;
            std::cout << "x: " << wx1 << ", y: " << wy1 << " z: " << wz1 << std::endl;
            std::vector<float> temp;
            temp.push_back(wx1);            
            temp.push_back(0);
            temp.push_back(wy1);
            points.push_back(temp);

            int curr_tile_x = floor((float) wx1 / (0.42f));
            // int curr_tile_y = floor((float) wz1 / (0.42f*3)) - 4;
            std::cout << "Tile: " << curr_tile_x << std::endl;
            down = true;
        } else {
            down = false;
        }
    }
}

/* ARGSUSED1 */
void motion(int x, int y)
{
    if (down) {
        // angulo = lastx - x;
        // anguloy = lasty - y;
        // lastx = x;
        glutPostRedisplay();
    }
}

/*Función principal*/
int main(int argc, char **argv)
{	
    glutInit(&argc, argv);       
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Battleship");
    glutDisplayFunc(&Display);
    // glutFullScreen();   
    glutIdleFunc(&Display); 
    glutReshapeFunc(&Reshape);
    InitGL(1024, 768);
    glutKeyboardFunc(&Keyboard);
    glutKeyboardUpFunc(&KeyboardUp);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialInputUp);
    glutMouseFunc(mouse);    
    glutIdleFunc(idle);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0);           
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
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    map = new Map();  
    tile = new Tile();
    tile->setParams(0.6,0.6,0.6, 0,0,0, 0,0,0,0);
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
    gluPerspective(fovy, (double) w / (double) h, _zNear, _zFar);
    glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{

    switch (key) {   
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
    case ' ':{
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
float point[3] = {-0.21, 0, -0.21};
/* Función de display */
void Display(void)
{								
	glLoadIdentity();	
	gluLookAt(0, START_Z+camZ, 0, 0, camZ, 0, 0, 0, -1);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    
	glPushMatrix();
		if (wireframe)
		    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Activar wireframe
		else
		    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // glTranslatef(-1,0,0);
		glRotatef(xRot,1,0,0);	
		glRotatef(yRot,0,1,0);	
		glRotatef(zRot,0,0,1);
		// map->Draw();
        tile->Draw();    
       //  glPushAttrib(GL_LIGHTING_BIT);
       //    glColor3f(1, 1, 0);
       //    glPointSize(3.0);
       //    glColor3f(1.0, 1.0, 0.0);
       //    glBegin(GL_POINTS);
       //       for (int i = 0; i < 1; i++) 
       //          glVertex3fv(&point[0]);
       //    glEnd();
       // glPopAttrib(); 

       //  glPushAttrib(GL_LIGHTING_BIT);
       //    glColor3f(1, 1, 0);
       //    glPointSize(3.0);
       //    glColor3f(1.0, 1.0, 0.0);
       //    glBegin(GL_POINTS);
       //       for (int i = 0; i < points.size(); i++) 
       //          glVertex3fv(&points[i][0]);
       //    glEnd();
       // glPopAttrib();   
          // map->getShip(0).Draw();
          // map->getShip(0).DrawAxis(1.0f);
          // ship->Draw();
          // ship->DrawAxis(1.0f);	         
    glPopMatrix(); 
    glutSwapBuffers();
}

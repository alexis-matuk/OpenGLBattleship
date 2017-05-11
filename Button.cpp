#include "Button.hpp"

Button::Button()
{
	xTopLeft = 0;
	yTopLeft = 0;
	width = 100;
	height = 50;
	state = false;
	highlighted = false;
	label = nullptr;
	font = nullptr;
	name = "";
	callbackFunction = NULL;
	active = true;
}

Button::Button(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, ButtonCallback _callbackFunction, std::string _name, void* _font) : xTopLeft(_xTopLeft), yTopLeft(_yTopLeft), width(_width), height(_height), label(_label), callbackFunction(_callbackFunction), name(_name), font(_font)
{
	state = false;
	highlighted = false;
	active = true;
}

void Button::Font(void *font,char *text,int x,int y)
{
	glRasterPos2i(x, y);

	while( *text != '\0' )
	{
		glutBitmapCharacter( font, *text );
		++text;
	}
}

bool Button::ButtonClickTest(int x,int y) 
{
    if(x > xTopLeft && x < xTopLeft+width && y > yTopLeft && y < yTopLeft+height) {
    	if(active)
    	{    		
			return true;
    	}
	}	
	return false;
}

void Button::ButtonPress(int x,int y)
{
	if( ButtonClickTest(x,y) )
	{
		state = true;
	}
}

void Button::ButtonRelease(int x,int y)
{
		if( ButtonClickTest(x,y))
		{
			if (callbackFunction) {				
				callbackFunction();
			}
		}
		state = false;
}

void Button::ButtonPassive(int x,int y)
{
	if( ButtonClickTest(x,y) )
	{
		if( highlighted == false ) {
			highlighted = true;
			glutPostRedisplay();
		}
	}
	else if( highlighted == true )
	{
		highlighted = false;
		glutPostRedisplay();
	}	
}

void Button::draw1()
{
	glBegin(GL_QUADS);
		glVertex2i(xTopLeft, yTopLeft);
		glVertex2i(xTopLeft, yTopLeft+height);
		glVertex2i(xTopLeft+width, yTopLeft+height);
		glVertex2i(xTopLeft+width, yTopLeft);
	glEnd();
}

void Button::draw2()
{
	glBegin(GL_LINE_STRIP);
		glVertex2i(xTopLeft+width,yTopLeft);
		glVertex2i(xTopLeft,yTopLeft);
		glVertex2i(xTopLeft,yTopLeft+height);
	glEnd();
}

void Button::draw3()
{
	glBegin(GL_LINE_STRIP);
		glVertex2i(xTopLeft, yTopLeft+height);
		glVertex2i(xTopLeft+width, yTopLeft+height);
		glVertex2i(xTopLeft+width, yTopLeft);
	glEnd();
}

void Button::checkHighlight(int fontx, int fonty)
{
	if(highlighted)
	{
		glColor3f(0,0,0);
		Font(font,label,fontx,fonty);
		fontx--;
		fonty--;
	}
}

void Button::Draw()
{
	int fontx;
	int fonty;
	if (highlighted) 
		glColor3f(0.2f,0.2f,1.0f);
	else 
		glColor3f(0.6f,0.6f,0.6f);
	draw1();
	glLineWidth(3);
	if (state) 
		glColor3f(0.4f,0.4f,0.4f);
	else 
		glColor3f(0.8f,0.8f,0.8f);
	draw2();
	if (state) 
		glColor3f(0.8f,0.8f,0.8f);
	else 
		glColor3f(0.4f,0.4f,0.4f);
	draw3();
	glLineWidth(1);
	fontx = xTopLeft + (width - glutBitmapLength(font,(const unsigned char*) label)) / 2 ;
	fonty = yTopLeft + (height+10)/2;
	if (state) {
		fontx+=2;
		fonty+=2;
	}
	checkHighlight(fontx, fonty);
	glColor3f(1,1,1);
	Font(font,label,fontx,fonty);
}

std::string Button::getName()
{
	return name;
}

void Button::setPosition(int x, int y)
{
	xTopLeft = x;
	yTopLeft = y;
}

void Button::setScale(int x, int y)
{
	width = x;
	height = y;
}

void Button::setActive(bool _active)
{
	active = _active;
}

bool Button::getActive()
{
	return active;
}


Button::~Button()
{

}
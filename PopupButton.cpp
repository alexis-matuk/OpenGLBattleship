#include "PopupButton.hpp"

PopupButton::PopupButton(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, PopupButtonCallback _callbackFunction, std::string _name, void* _font, Popup * _p) : Button()
{
	xTopLeft = _xTopLeft;
	yTopLeft = _yTopLeft;
	width = _width;
	height = _height;
	label = _label;
	callbackFunction = _callbackFunction;
	name = _name;
	font = _font;
	state = false;
	highlighted = false;
	active = true;
	p = _p;
}

void PopupButton::ButtonRelease(int x,int y)
{	
	if( ButtonClickTest(x,y))
	{		
		(p->*callbackFunction)();		
	}
	state = false;
}
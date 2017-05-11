/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "PopupButton.hpp"

/*
  Popupbutton has a different type of callback, that's why it needs to inherit from Popup and add a new type of callback
*/
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

/*
  Call the special callback of the popup
*/
void PopupButton::ButtonRelease(int x,int y)
{	
	if( ButtonClickTest(x,y))
	{		
		(p->*callbackFunction)();		
	}
	state = false;
}
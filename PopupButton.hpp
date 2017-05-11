/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef PopupButton_H
#define PopupButton_H

#include "HeaderInclude.hpp"
#include "Button.hpp"
#include "Popup.hpp"

typedef void (Popup::*PopupButtonCallback)();
class PopupButton : public Button{	
private:
	PopupButtonCallback callbackFunction;
	Popup * p;
public:
	PopupButton(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, PopupButtonCallback _callbackFunction, std::string _name, void* _font, Popup* _p);
	void ButtonRelease(int x,int y);
};

#endif

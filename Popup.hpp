#ifndef Popup_H
#define Popup_H

#include "HeaderInclude.hpp"
#include "Panel.hpp"

class PopupButton;

class Popup : public Panel{	
protected:
	PopupButton * button;		
	int buttonWidth = 80;
	int buttonHeight = 30;
	float min_x, min_y, min_z, max_x, max_y, max_z;
	bool showing = false;
public:	
	Popup(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int r, int g, int b, const FTGL::TextAlignment _alignment);
	void Draw(bool background);
	PopupButton * getButton();
	void activateButton();
	bool getShowing();
	void setShowing(bool _showing);
	void center(int _ww, int _wh, int _posRelativeToWh);
	~Popup();
	void accept();
};


#endif

#include "PopupButton.hpp"
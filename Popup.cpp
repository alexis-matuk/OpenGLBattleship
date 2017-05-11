/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "Popup.hpp"

/*
  Callback for closing the popup
*/
void Popup::accept()
{ 	
	showing = false;
	button->setActive(false);
}

/*
  Create a popup with a default red color and some transparency
  Every popup has a button that calls back to accept on their instance.
*/
Popup::Popup(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int r, int g, int b, const FTGL::TextAlignment _alignment):Panel(_xTopLeft, _yTopLeft, _width, _name, _content, _fontSize, r, g, b, _alignment)
{
	panel_r = 255;
	panel_g = 0;
	panel_b = 0;
	panel_a = 0.8f;
	button = new PopupButton(_xTopLeft, _yTopLeft, buttonWidth, buttonHeight, (char *) "Accept", &Popup::accept, (char *) "accept", GLUT_BITMAP_HELVETICA_12, this);	
	FTBBox bbox = layout->BBox(content.c_str());	  
    min_x = bbox.Lower().Xf(); min_y = bbox.Lower().Yf(); min_z = bbox.Lower().Zf();
    max_x = bbox.Upper().Xf(); max_y = bbox.Upper().Yf(); max_z = bbox.Upper().Zf();
    setExtras(0,50,0,0);
}

/*
  Draw the popup
*/
void Popup::Draw(bool background)
{
	if(showing)
	{
		Panel::Draw(background);
		setButtonViewPort();			
		button->Draw();
	}	
}

/*
  Get the button assigned to the popup
*/
PopupButton * Popup::getButton()
{
	return button;
}

/*
  Activate button in popup
*/
void Popup::activateButton()
{
	button->setActive(true);
}

/*
  Get if the popup is showing
*/
bool Popup::getShowing()
{
	return showing;
}

/*
  Set if the popup is showing
*/
void Popup::setShowing(bool _showing)
{
	showing = _showing;
}

/*
  Center the popup
*/
void Popup::center(int _ww, int _wh, int _posRelativeToWh)
{
	setww(_ww);
    setwh(_wh);
    FTBBox bbox = layout->BBox(content.c_str());    
    // float off = (bbox.Upper().X() - bbox.Lower().X())/2;   
    setPosition((float)ww/2 - (min_x+max_x)/2, _posRelativeToWh);
    button->setPosition(xTopLeft + (min_x+max_x)/2 - buttonWidth/2,(int)_wh - _posRelativeToWh + (max_y-min_y) );
}

Popup::~Popup()
{

}
/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "UIHandler.hpp"

UIHandler::UIHandler()
{

}

UIHandler::~UIHandler()
{

}

/*
	Create a new button managed by the UIHandler
*/
void UIHandler::createButton(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, ButtonCallback _callbackFunction, std::string _name, void* _font)
{
	Button * b = new Button(_xTopLeft, _yTopLeft, _width, _height, _label, _callbackFunction, _name, _font);
	buttons.push_back(b);
}

/*
	Create a new panel managed by the UIHandler
*/
void UIHandler::createPanel(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alginment)
{
	Panel * p = new Panel(_xTopLeft, _yTopLeft, _width, _name, _content, _fontSize, _r, _g, _b, _alginment);
	panels.push_back(p);
}

/*
	Create a new popup managed by the UIHandler	
*/
void UIHandler::createPopup(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alginment)
{
	Popup * p = new Popup(_xTopLeft, _yTopLeft, _width, _name, _content, _fontSize, _r, _g, _b, _alginment);	
	buttons.push_back(p->getButton());
	popups.push_back(p);
}

/*
	Custom struct for finding buttons
*/
struct isValueButton
{
    std::string m_value;

    isValueButton(std::string value) : m_value(value) {}

    bool operator()(Button *b) const
    {
        return (b->getName() == m_value);
    }
};

/*
	Custom struct for finding panels	
*/
struct isValuePanel
{
    std::string m_value;

    isValuePanel(std::string value) : m_value(value) {}

    bool operator()(Panel *p) const
    {
        return (p->getName() == m_value);
    }
};

/*
	Draw a button initialized in the handler given a unique name
*/
void UIHandler::drawButtonByName(std::string _name)
{
	Button * b = findButtonByName(_name);
	if(b != nullptr)
	{				
		b->Draw();
	}
	else
	{
		std::cout << "Button not found" << std::endl;
	}
}

/*
	Draw a panel initialized in the handler.
	_background specifies if the bounding box should be drawn.
*/
void UIHandler::drawPanelByName(std::string _name, bool _background)
{
	Panel * p = findPanelByName(_name);
	if(p != nullptr)
	{		
		p->Draw(_background);
	}
	else
	{
		std::cout << "Panel not found" << std::endl;
	}
}

/*
	Check if any of the initialized buttons are being pressed	
*/
void UIHandler::buttonPress(int x, int y)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ButtonPress(x,y);
	}
}

/*
	Check if any of the initialized buttons are being released
*/
void UIHandler::buttonRelease(int x, int y)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ButtonRelease(x,y);
	}
}

/*
	Check if any of the initialized buttons are being hovered
*/
void UIHandler::passiveButton(int x, int y)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ButtonPassive(x,y);
	}
}

/*
	Set position of a button given its name
*/
void UIHandler::setButtonPositionByName(std::string _name, int x, int y)
{
	Button * b = findButtonByName(_name);
	if(b != nullptr)
	{
		b->setPosition(x, y);
	}
}

/*
	Find an initialized button by name
*/
Button * UIHandler::findButtonByName(std::string _name)
{
	std::vector<Button*>::iterator it;
	it = std::find_if(buttons.begin(), buttons.end(), isValueButton(_name));
	if(it != buttons.end())
	{		
		return (*it);
	}
	else
	{
		return nullptr;
	}
}

/*
	Find an initialized panel by name	
*/
Panel * UIHandler::findPanelByName(std::string _name)
{
	std::vector<Panel*>::iterator it;
	it = std::find_if(panels.begin(), panels.end(), isValuePanel(_name));
	if(it != panels.end())
	{		
		return (*it);
	}
	else
	{
		return nullptr;
	}
}

/*
	Set scale of a button by name	
*/
void UIHandler::setScaleByName(std::string _name, int x, int y)
{
	Button * b = findButtonByName(_name);
	if(b != nullptr)
	{
		b->setScale(x, y);
	}
}

/*
	Find an initialized popup by name
*/
Popup * UIHandler::findPopupByName(std::string _name)
{
	std::vector<Popup*>::iterator it;
	it = std::find_if(popups.begin(), popups.end(), isValuePanel(_name));
	if(it != popups.end())
	{		
		return (*it);
	}
	else
	{
		return nullptr;
	}
}

/*
	Draw an initialized popup by name
*/
void UIHandler::drawPopupByName(std::string _name)
{
	Popup * p = findPopupByName(_name);
	if(p != nullptr)
	{		
		p->activateButton();
		p->Draw(true);
	}
	else
	{
		std::cout << "Popup not found" << std::endl;
	}
}

/*
	Draw all active popups	
*/
void UIHandler::drawActivePopups()
{
	for(int i = 0;i < popups.size(); i++)
	{
		if(popups[i]->getShowing())
		{
			popups[i]->activateButton();
			popups[i]->Draw(true);
		}
	}
}

/*
	Activate a specific popup by name	
*/
void UIHandler::activatePopup(std::string _name)
{
	Popup * p = findPopupByName(_name);
	if(p != nullptr)
	{
		p->setShowing(true);
	}
}

/*
	Deactivate all buttons to avoid presses even when they are not rendered	
*/
void UIHandler::deactivateButtons()
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->setActive(false);
	}
}

/*
	Draw debug lines in ending scene to check positioning	
*/
void UIHandler::drawDebugLines()
{
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(ww/2, -wh, 0);
		glVertex3f(ww/2, wh, 0);

		glVertex3f(ww/4, -wh, 0);
		glVertex3f(ww/4, wh, 0);

		glVertex3f(3*ww/4, -wh, 0);
		glVertex3f(3*ww/4, wh, 0);
	glEnd();
}

/*
	Set window width
*/
void UIHandler::setww(int _ww)
{
	ww = _ww;
}

/*
	Set window height	
*/
void UIHandler::setwh(int _wh)
{
	wh = _wh;
}


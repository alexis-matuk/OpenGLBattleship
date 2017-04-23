#include "UIHandler.hpp"

UIHandler::UIHandler()
{

}

void UIHandler::createButton(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, ButtonCallback _callbackFunction, std::string _name, void* _font)
{
	Button * b = new Button(_xTopLeft, _yTopLeft, _width, _height, _label, _callbackFunction, _name, _font);
	buttons.push_back(b);
}

void UIHandler::createPanel(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alginment)
{
	Panel * p = new Panel(_xTopLeft, _yTopLeft, _width, _name, _content, _fontSize, _r, _g, _b, _alginment);
	panels.push_back(p);
}

struct isValueButton
{
    std::string m_value;

    isValueButton(std::string value) : m_value(value) {}

    bool operator()(Button *b) const
    {
        return (b->getName() == m_value);
    }
};

struct isValuePanel
{
    std::string m_value;

    isValuePanel(std::string value) : m_value(value) {}

    bool operator()(Panel *p) const
    {
        return (p->getName() == m_value);
    }
};

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

void UIHandler::buttonPress(int x, int y)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ButtonPress(x,y);
	}
}

void UIHandler::buttonRelease(int x, int y)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ButtonRelease(x,y);
	}
}

void UIHandler::passiveButton(int x, int y)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ButtonPassive(x,y);
	}
}

void UIHandler::setButtonPositionByName(std::string _name, int x, int y)
{
	Button * b = findButtonByName(_name);
	if(b != nullptr)
	{
		b->setPosition(x, y);
	}
}

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

void UIHandler::setScaleByName(std::string _name, int x, int y)
{
	Button * b = findButtonByName(_name);
	if(b != nullptr)
	{
		b->setScale(x, y);
	}
}

void UIHandler::createPopup(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alginment)
{
	Popup * p = new Popup(_xTopLeft, _yTopLeft, _width, _name, _content, _fontSize, _r, _g, _b, _alginment);	
	buttons.push_back(p->getButton());
	popups.push_back(p);
}

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

void UIHandler::activatePopup(std::string _name)
{
	Popup * p = findPopupByName(_name);
	if(p != nullptr)
	{
		p->setShowing(true);
	}
}

UIHandler::~UIHandler()
{

}

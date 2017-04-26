#ifndef UIHandler_H
#define UIHandler_H

#include "HeaderInclude.hpp"
#include "Button.hpp"
#include "Panel.hpp"
#include "Popup.hpp"
#include "PopupButton.hpp"

class UIHandler{	
private:
	std::vector<Button*> buttons;
	std::vector<Panel*> panels;
	std::vector<Popup*> popups;	
	std::vector<PopupButton*> buttons_p;
public:	
	UIHandler();
	~UIHandler();
	void createButton(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, ButtonCallback _callbackFunction, std::string _name, void* _font);
	void createPanel(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alginment);	
	void drawButtonByName(std::string _name);
	void drawPanelByName(std::string _name, bool _background);
	void drawPopupByName(std::string _name);
	void buttonPress(int x, int y);
	void buttonRelease(int x, int y);
	void passiveButton(int x, int y);
	void setButtonPositionByName(std::string _name, int x, int y);
	void setScaleByName(std::string _name, int x, int y);	
	Button * findButtonByName(std::string _name);
	Panel * findPanelByName(std::string _name);
	Popup * findPopupByName(std::string _name);
	void createPopup(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alginment);
	void drawActivePopups();
	void activatePopup(std::string _name);
	void deactivateButtons();
};

#endif

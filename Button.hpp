#ifndef Button_H
#define Button_H

#include "HeaderInclude.hpp"
typedef void (*ButtonCallback)();
class Button{	
protected:	
	int xTopLeft;
	int yTopLeft;
	int width;
	int height;
	bool state;
	bool highlighted;
	char* label;
	void* font;
	std::string name;
	ButtonCallback callbackFunction;
	bool active;
public:	
	Button();
	Button(int _xTopLeft, int _yTopLeft, int _width, int _height, char* _label, ButtonCallback _callbackFunction, std::string _name, void* _font);
	~Button();
	void Font(void *font,char *text,int x,int y);
	virtual bool ButtonClickTest(int x,int y);
	virtual void ButtonPress(int x,int y);
	virtual void ButtonRelease(int x,int y);
	virtual void ButtonPassive(int x,int y);
	void Draw();
	std::string getName();	
	void setPosition(int x, int y);
	void setScale(int x, int y);
	void setActive(bool _active);
	bool getActive();
};
#endif

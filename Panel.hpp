#ifndef Panel_H
#define Panel_H

#include "HeaderInclude.hpp"
#include "aggregateFuncs.hpp"
class Panel{	
protected:	
	int xTopLeft;
	int yTopLeft;
	int width;	
	std::string content;
	std::string name;
	FTFont* font;
	FTSimpleLayout* layout;
	int fontSize;
	int r;
	int g;
	int b;
	FTGL::TextAlignment alignment;
	int ww;
	int wh;
	float borderX = 15;
	float borderY = 15;

	int panel_r = 153;
	int panel_g = 153;
	int panel_b = 153;
	float panel_a = 0.4f;

	int extraBottom = 0;
	int extraTop = 0;
	int extraLeft = 0;
	int extraRight = 0;
public:	
	Panel(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int r, int g, int b, const FTGL::TextAlignment _alignment);
	void setColor(int _r, int _g, int _b);
	void setContent(std::string _content);
	void setFontSize(int _size);
	void Draw(bool withBackground);
	void setAlignment(const FTGL::TextAlignment _alignment);
	void addPositionFromCenter(int x, int y);
	std::string getName();
	std::string getContent();
	FTSimpleLayout * getLayout();
	FTFont* getFont();
	void setww(int _ww);
	void setwh(int _wh);
	void setPanelColor(int _r, int _g, int _b, float _a);
	void setExtras(int _extraTop, int _extraBottom, int _extraLeft, int _extraRight);
	~Panel();
};
#endif

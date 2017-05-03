#include "Panel.hpp"

Panel::Panel(int _xTopLeft, int _yTopLeft, int _width, std::string _name, std::string _content, int _fontSize, int _r, int _g, int _b, const FTGL::TextAlignment _alignment): xTopLeft(_xTopLeft), yTopLeft(_yTopLeft), width(_width), name(_name), content(_content), fontSize(_fontSize), r(_r), g(_g), b(_b), alignment(_alignment)
{
	layout = new FTSimpleLayout();
	font =  new FTBitmapFont(fontFile);
	if (font->Error()) 
	{ 
		std::cerr << "Failed to open font: " << fontFile << std::endl;
		exit(1);		
	}    
	if (!font->FaceSize(fontSize)) 
    { 
    	std::cerr << "Failed to set size" << std::endl;    	
    }
	layout->SetLineLength(width);
	layout->SetFont(font);	
	layout->SetAlignment(_alignment);
}

void Panel::setColor(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
}

void Panel::setFontSize(int _size)
{
	fontSize = _size;
	if (!font->FaceSize(fontSize)) 
    { 
    	std::cerr << "Failed to set size" << std::endl;    	
    }    
}

void Panel::setContent(std::string _content)
{
	content = _content;
}

void Panel::setAlignment(const FTGL::TextAlignment _alignment)
{
	layout->SetAlignment(_alignment);
}

void Panel::setPosition(int x, int y)
{
	xTopLeft = x;
	yTopLeft = y;
}

std::string Panel::getName()
{
	return name;
}

std::string Panel::getContent()
{
	return content;
}

FTSimpleLayout * Panel::getLayout()
{
	return layout;
}

FTFont* Panel::getFont()
{
	return font;
}

void Panel::setww(int _ww)
{
	ww = _ww;
}

void Panel::setwh(int _wh)
{
	wh = _wh;
}

void Panel::setPanelColor(int _r, int _g, int _b, float _a)
{
	panel_r = _r;
	panel_g = _g;
	panel_b = _b;
	panel_a = _a;
}

void Panel::setExtras(int _extraTop, int _extraBottom, int _extraLeft, int _extraRight)
{
	extraBottom = _extraBottom;
	extraTop = _extraTop;
	extraLeft = _extraLeft;
	extraRight = _extraRight;
}

void Panel::Draw(bool withBackground)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);	
		FTBBox bbox = layout->BBox(content.c_str());
		float min_x, min_y, min_z, max_x, max_y, max_z;	    
	    min_x = bbox.Lower().Xf(); min_y = bbox.Lower().Yf(); min_z = bbox.Lower().Zf();
	    max_x = bbox.Upper().Xf(); max_y = bbox.Upper().Yf(); max_z = bbox.Upper().Zf();
		if(withBackground)
		{			
			glPushMatrix();	
				glTranslatef(xTopLeft, yTopLeft, 0);
				// glTranslatef(ww/2, wh/2, 0);								    
			    glBegin(GL_QUADS);
			    	glColor4f((float) panel_r/255.05, (float) panel_g/255.0f, (float) panel_b/255.0f, panel_a);
			        glVertex3f(min_x - borderX - extraLeft, min_y - borderY - extraBottom, 0);
			        glVertex3f(min_x - borderX - extraLeft, max_y + borderY + extraTop, 0);
			        glVertex3f(max_x + borderX + extraRight, max_y + borderY + extraTop, 0);
			        glVertex3f(max_x + borderX + extraRight, min_y - borderY - extraBottom, 0);
			    glEnd();
			glPopMatrix();		
		}
		glPushMatrix();
			glTranslatef(xTopLeft, yTopLeft, 0);
			// glTranslatef(ww/2, wh/2, 0);	
			glColor3f((float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
			glRasterPos2i(0,0);
			layout->Render((const char*)content.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
		glPopMatrix();
	glPopAttrib();
}

void Panel::center(int _ww, int _wh, int _posRelativeToWh)
{
	setww(_ww);
    setwh(_wh);
    FTBBox bbox = layout->BBox(content.c_str());    
    float off = (bbox.Upper().X() - bbox.Lower().X())/2;   
    setPosition((float)ww/2 - off, _posRelativeToWh);
}

void Panel::left(int _ww, int _wh, int _posRelativeToWh)
{
	setww(_ww);
    setwh(_wh);
    FTBBox bbox = layout->BBox(content.c_str());    
    float off = (bbox.Upper().X() - bbox.Lower().X());   
    setPosition(0 + extraLeft + borderX, _posRelativeToWh);
}

void Panel::right(int _ww, int _wh, int _posRelativeToWh)
{
	setww(_ww);
    setwh(_wh);
    FTBBox bbox = layout->BBox(content.c_str());    
    float off = (bbox.Upper().X() - bbox.Lower().X());   
    setPosition(ww - (off + borderX + extraRight), _posRelativeToWh);
}

void Panel::setWidth(int _width)
{
	width = _width;
}

Panel::~Panel()
{

}
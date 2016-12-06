#ifndef __TEXT_H__
#define __TEXT_H__

#include <string>
#include "define.h"
#include "DeviceManager.h"
#include "Transformable.h"

class Text : public Transformable
{
public:
	Text(LPCWSTR fontName, string text, float x = 0, float y = 0, int fontSize = 21);
	~Text();

	void draw();

	void setText(string text);
	string getText();

	void setFontHeight(int fontheight);
	int getFontHeight();
	
	
	void setFontWeight(UINT fontW);
	UINT getFontWeight();

	void setItalic(bool i);
	bool isItalic();

	void setTextAlign(DWORD align);
	DWORD getTextAlign();

	void setColor(D3DCOLOR color);
	D3DCOLOR getColor();

private:
	ID3DXFont *_font;
	LPCWSTR _fontName;
	string _text;

	int _fontHeight;
	UINT _fontWeight;
	bool _italic;
	DWORD _textAlign;				
	D3DCOLOR _color;

	RECT _textRect;

	void updateFont();
};

#endif // !__TEXT_H__

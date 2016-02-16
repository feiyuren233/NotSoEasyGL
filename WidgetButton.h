/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WidgetButton.h
 * Author: renfeiyu
 *
 * Created on February 9, 2016, 4:47 PM
 */

#ifndef WIDGETBUTTON_H
#define WIDGETBUTTON_H
#include "GUIComponentBase.h"

class Button: public GUIComponentBase {
private:
	Point2i TLPosition, BRPosition;
	int width, height;

	bool pressed, focused;

	//void (*ButtonCallback)(void);

	void (*clickCallback)(Button *button, int x, int y);
	void (*buttonPressCallback)(Button *button, int x, int y, int buttonCode);
	void (*drawCallBack)(Button *button, cairo_t *context);
	void (*dragCallBack)(Button *button, int x, int y);

	void drawDefaultButton(cairo_t *context);
protected:

public:
	Point2i getTLPosition();
	void setTLPosition(int x, int y);

	Button(int TLx, int TLy, int BRx, int BRy);
	void regOnButtonpress(void (*buttonPressCB)(Button*, int, int));
	void regOnClick(void (*clickCB)(Button*, int, int));
	void regOnDraw(void (*drawCB)(Button*, cairo_t*));
	void regOnDrag(void (*dragCB)(Button*, int x, int y));

	virtual void onButtonPress(int x, int y, int buttonCode);

	virtual void onClick(int x, int y);

	virtual void onDraw(cairo_t*);

	virtual void onRemap(uint_fast8_t*);

	virtual void onDrag(int x, int y);

	virtual void onDrop(int x, int y);

	virtual void onEnter();

	virtual void onLeave();

	//virtual void onUnmap(uint8_t *map);

};

#endif /* WIDGETBUTTON_H */


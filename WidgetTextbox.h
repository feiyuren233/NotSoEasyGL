/*
 * WidgetTextbox.h
 *
 *  Created on: Feb 16, 2016
 *      Author: feiyu
 */

#ifndef WIDGETTEXTBOX_H_
#define WIDGETTEXTBOX_H_

#include "GUIComponentBase.h"
#include <string>

class Textbox: public GUIComponentBase {
private:
	std::string textBuffer;
	int cursorLocation;

	bool pressed;
protected:

public:
	Textbox(int x, int y);
	virtual ~Textbox();

	virtual void onFocus();
	virtual void onUnFocus();

	virtual void onButtonPress(int x, int y, int buttonCode);
	virtual void onKeyPress(int keyAscii);
	virtual void onKeyRelease(int keyAscii);

	virtual void onRemap(uint_fast8_t* map);

	virtual void onDraw(cairo_t* context);
};

#endif /* WIDGETTEXTBOX_H_ */

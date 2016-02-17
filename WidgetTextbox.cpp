/*
 * WidgetTextbox.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: feiyu
 */

#include "WidgetTextbox.h"
#include <X11/extensions/XInput.h>
#include <linux/input.h>

Textbox::Textbox(int x, int y):GUIComponentBase(x, y) {
	// TODO Auto-generated constructor stub
	cursorLocation = 0;
	pressed = false;
}

Textbox::~Textbox() {
	// TODO Auto-generated destructor stub
	textBuffer.clear();
}

void Textbox::onFocus() {
	focused = true;
}

void Textbox::onUnFocus() {
	focused = false;
}

void Textbox::onButtonPress(int x, int y, int buttonCode) {
	if(buttonCode == 1)
		pressed = true;
}

void Textbox::onKeyPress(int keyAscii) {

	if (keyAscii == 8 && cursorLocation > 0) {
		textBuffer.erase(cursorLocation - 1, 1);
	} else if (keyAscii == 127 && cursorLocation < textBuffer.length()) {
		textBuffer.erase(cursorLocation, 1);
	} else if ((keyAscii >= 48 && keyAscii <= 57) || (keyAscii >= 65 && keyAscii <= 90) || (keyAscii >= 97 && keyAscii <= 122) || keyAscii == 32 || keyAscii == 9) {
		textBuffer.insert(cursorLocation, 1, (char) (keyAscii));
	}
	std::cout<<textBuffer<<std::endl;
}

void Textbox::onKeyRelease(int keyAscii) {

}

void Textbox::onRemap(uint_fast8_t* map) {
	for(unsigned i = 0; i<winWidth * winHeight; i++)
			map[i]=componentID;

}



void Textbox::onDraw(cairo_t* context) {
}

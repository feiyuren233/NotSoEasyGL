/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "WidgetButton.h"

void Button::onButtonPress(int x, int y, int buttonCode) {
	pressed = true;
    std::cout << "Button pressed ID = " << componentID << std::endl;
}

Button::Button(int TLx, int TLy, int BRx, int BRy) : TLPosition(TLx, TLy), BRPosition(BRx, BRy) {
	width = BRPosition.x - TLPosition.x;
	height = BRPosition.y - TLPosition.y;
	pressed = false;
	focused = false;
}

Point2i Button::getTLPosition() {
    return TLPosition;
}

void Button::setTLPosition(int x, int y) {
    TLPosition.x = x;
    TLPosition.y = y;
}

void Button::drawDefaultButton(cairo_t *context) {
	if(pressed)
		cairo_set_source_rgba(context, 0.5, 0.5, 1, 1);
	else if(focused)
		cairo_set_source_rgba(context, 0.5, 0.8, 1, 1);
	else
		cairo_set_source_rgba(context, 0.5, 0.5, 1, 0.5);
	cairo_rectangle(context, TLPosition.x, TLPosition.y, width, height);
	cairo_fill(context);
}

void Button::onClick(int x, int y) {
	pressed = false;
    if (clickCallback)
        clickCallback(this, x, y);
    std::cout << "Button clicked ID = " << componentID << std::endl;
}

void Button::onDraw(cairo_t* context) {
    if (drawCallBack)
        drawCallBack(this, context);
    else{
		drawDefaultButton(context);
    }
    //std::cout<<"Button virtually drawn ID = "<<componentID<<std::endl;
}

void Button::onRemap(uint_fast8_t* map) {
    for (int i = TLPosition.x; i < BRPosition.x; i++) {
        for (int j = TLPosition.y; j < BRPosition.y; j++) {
            map[TranslateMap(i, j)] = componentID;
        }
    }
}

void Button::regOnDraw(void(*drawCB)(Button*, cairo_t*)) {
    drawCallBack = drawCB;
}

void Button::regOnDrag(void(*dragCB)(Button*, int, int)) {
    dragCallBack = dragCB;
}

void Button::onDrag(int x, int y) {
    if(dragCallBack)
        dragCallBack(this, x, y);
	else {
		if(x>TLPosition.x && x<BRPosition.x && y>TLPosition.y && y<BRPosition.y)
    		pressed = true;
		else
			pressed = false;
    }
}
void Button::onDrop(int x, int y){
	if(idAtGUImapLocation(x, y) == componentID)
		onClick(x, y);
}

void Button::onEnter(){
	focused = true;


}
void Button::onLeave(){
	focused = false;
}


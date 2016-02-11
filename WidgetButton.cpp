/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "WidgetButton.h"

void Button::onButtonPress(int x, int y, int buttonCode) {
    std::cout << "Button pressed ID = " << componentID << std::endl;
}

Button::Button(int TLx, int TLy, int BRx, int BRy) : TLPosition(TLx, TLy), BRPosition(BRx, BRy) {

}

Point2i Button::getTLPosition() {
    return TLPosition;
}

void Button::setTLPosition(int x, int y) {
    TLPosition.x = x;
    TLPosition.y = y;
}


void Button::onClick(int x, int y) {
    if (clickCallback)
        clickCallback(this, x, y);
    std::cout << "Button clicked ID = " << componentID << std::endl;
}

void Button::onDraw(cairo_t* context) {
    if (drawCallBack)
        drawCallBack(this, context);
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
}



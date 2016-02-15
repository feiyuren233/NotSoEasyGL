/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "GUIComponentBase.h"
GUIManager* GUIComponentBase::Gmanager;

GUIComponentBase::GUIComponentBase() {
}

GUIComponentBase::~GUIComponentBase() {
}

void GUIComponentBase::registerGUImanager(GUIManager* arg) {
    Gmanager = arg;
}

int GUIComponentBase::getComponentID() {
    return componentID;
}

void GUIComponentBase::setComponentID(int ID) {
    componentID = ID;
}

//Deleate later

void GUIComponentBase::onRemap(uint_fast8_t* map) {
    for (int i = 0; i < 1000 * 400; i++)
        map[i] = componentID;
    std::cout << "Remap" << std::endl;
}

void GUIComponentBase::onUnmap(uint8_t *map){
	for(unsigned i = 0; i<winWidth*winHeight; i++)
		if(map[i] == componentID)
			map[i] = 0;
}

void GUIComponentBase::onCreate() {
    std::cout << "I'm created!!" << std::endl;
}

void GUIComponentBase::onKeyPress(int keycode) {
    std::cout << keycode << std::endl;
}

void GUIComponentBase::onEnter() {
    std::cout << "Entered " << componentID << std::endl;
}

void GUIComponentBase::onLeave() {
    std::cout << "Left " << componentID << std::endl;
}

void GUIComponentBase::onClick(int x, int y) {
    std::cout << "Click  x = " << x << "; Y = " << y << std::endl;
}

void GUIComponentBase::onDrag(int x, int y) {

}

void GUIComponentBase::onDraw(cairo_t*) {

}

void GUIComponentBase::onDrop(int x, int y) {

}

void GUIComponentBase::onKeyRelease(int keycode) {

}

void GUIComponentBase::onButtonPress(int x, int y, int buttonCode) {

}

void GUIComponentBase::onDestory() {

}

//Functions exposed to GUIcomponents

uint8_t GUIComponentBase::idAtGUImapLocation(int x, int y){
	return Gmanager->checkIDatGUImap(x, y);
}


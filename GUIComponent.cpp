/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "GUIComponent.h"

GUIComponent::GUIComponent() {
}

GUIComponent::~GUIComponent() {
}

void GUIComponent::setEventDispatcher(EventDispatcher* arg) {
    eventDispatcher = arg;
}

int GUIComponent::getComponentID() {
    return componentID;
}

void GUIComponent::setComponentID(int ID) {
    componentID = ID;
}

//Deleate later

void GUIComponent::onRemap(uint_fast8_t* map) {
    for (int i = 0; i < 1000 * 400; i++)
        map[i] = componentID;
    std::cout << "Remap" << std::endl;
}

void GUIComponent::onCreate() {
    std::cout << "I'm created!!" << std::endl;
}

void GUIComponent::onKeyPress(int keycode) {
    std::cout << keycode << std::endl;
}

void GUIComponent::onEnter() {
    std::cout << "Entered " << componentID << std::endl;
}

void GUIComponent::onLeave() {
    std::cout << "Left " << componentID << std::endl;
}

void GUIComponent::onClick(int x, int y) {
    std::cout << "Click  x = " << x << "; Y = " << y << std::endl;
}

void GUIComponent::onDrag(int x, int y) {

}

void GUIComponent::onDraw(cairo_t*) {

}

void GUIComponent::onDrop(int x, int y) {

}

void GUIComponent::onKeyRelease(int keycode) {

}

void GUIComponent::onButtonPress(int x, int y, int buttonCode) {

}

void GUIComponent::onDestory() {

}










/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUIManager.cpp
 * Author: renfeiyu
 * 
 * Created on February 9, 2016, 6:54 PM
 */

#include "GUIManager.h"

GUIManager::GUIManager(cairo_t *GUIcontext) {
    GUIManager::GUIcontext = GUIcontext;
}

GUIManager::GUIManager(const GUIManager& orig) {
}

GUIManager::~GUIManager() {
    for(int i=0; i<vecGUIComponents.size(); i++)
        delete vecGUIComponents[i];
}

void GUIManager::registerEventDispatcher(EventDispatcher* eventDispatcher, uint8_t *GUImap) {
    GUIManager::eventDispatcher = eventDispatcher;
    GUIManager::GUImap = GUImap;

    GUIComponentBase *zeroComponent = new GUIComponentBase();
    zeroComponent->registerGUImanager(this);
    addComponent(zeroComponent);
}

void GUIManager::addComponent(GUIComponentBase* component) {
    vecGUIComponents.push_back(component);
    component->setComponentID(vecGUIComponents.size() - 1);

    component->GUImap = GUImap;
    component->onCreate();
    component->onRemap(eventDispatcher->getGUImap());
}

void GUIManager::globalRemap(uint8_t* map) {
    for (long int i = 0; i < winWidth * winHeight; i++)
        map[i] = 0;
    for (int i = 0; i < vecGUIComponents.size(); i++)
        vecGUIComponents[i]->onRemap(map);
}

GUIComponentBase* GUIManager::operator[](int index) {
    return vecGUIComponents[index];
}

void GUIManager::DrawAll() {
    for(int i=0; i<vecGUIComponents.size(); i++){
        vecGUIComponents[i]->onDraw(GUIcontext);
        
    }
}

uint8_t GUIManager::checkIDatGUImap(int x, int y) {
	if(x<0||x>winWidth||y<0||y>winHeight)
		return 0;
	return GUImap[TranslateMap(x, y)];

}

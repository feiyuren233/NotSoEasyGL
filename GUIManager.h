/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUIManager.h
 * Author: renfeiyu
 *
 * Created on February 9, 2016, 6:54 PM
 */

#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "GUIComponentBase.h"
#include <stdint.h>
#include "mEventDispatcher.h"
class EventDispatcher;
class GUIComponentBase;
class GUIManager {
private:
    std::vector<GUIComponentBase*> vecGUIComponents;
    EventDispatcher *eventDispatcher;
    cairo_t *GUIcontext;
public:

    GUIManager(cairo_t*);
    GUIManager(const GUIManager& orig);
    ~GUIManager();
    void registerEventDispatcher(EventDispatcher* eventDispatcher);
    
    void addComponent(GUIComponentBase*);
    void removeComponent(GUIComponentBase*);
    void globalRemap(uint8_t *map);
    
    void DrawAll(void);
    
    GUIComponentBase* operator[](int index);
};

#endif /* GUIMANAGER_H */


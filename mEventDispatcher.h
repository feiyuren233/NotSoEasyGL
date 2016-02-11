/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mEventDispatcher.h
 * Author: renfeiyu
 *
 * Created on February 8, 2016, 4:44 PM
 */

#ifndef MEVENTDISPATCHER_H
#define MEVENTDISPATCHER_H
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <vector>

#include "GUIComponentBase.h"
#include "GUIUtil.h"
#include "Config.h"
#include "GUIManager.h"
class GUIComponentBase;
class GUIManager;

class EventDispatcher {
private:
    uint8_t *componentMap;

    struct state{
        int lastActiveComp;
        bool buttonPressed;
        bool pointerMovedAfterPress;
        int dragEventOwner;
        int currentActiveWidget;
        state(){
            lastActiveComp = 0;
            buttonPressed = false;
            pointerMovedAfterPress = false;
            int dragEventOwner = 0;
            currentActiveWidget = 0;
        }
    }eventState;
    
    GUIManager *GManager;
    
protected:
public:
    inline unsigned TranslatePosition(int x, int y);
    EventDispatcher(int winWidth, int winHeight);
    ~EventDispatcher();
    void registerGUImanager(GUIManager* Gmanager);
    
    uint8_t* getGUImap();
    
    void fetchAndDispatchEvent(XEvent*);

    void requestGlobalRemapComponent();

};


#endif /* MEVENTDISPATCHER_H */


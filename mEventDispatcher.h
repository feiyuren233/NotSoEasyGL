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

#include "GUIComponent.h"
#include "GUIUtil.h"
class GUIComponent;

class EventDispatcher {
private:
    uint8_t *componentMap;
    int winWidth, winHeight;

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
    
    
    
    
    std::vector<GUIComponent*> vecGUIComponents;
protected:
public:
    inline unsigned TranslatePosition(int x, int y);
    EventDispatcher(int winWidth, int winHeight);
    ~EventDispatcher();

    void addComponent(GUIComponent*);
    void removeComponent(GUIComponent*);


    void fetchAndDispatchEvent(XEvent*);

    void globalRemapComponent();

};


#endif /* MEVENTDISPATCHER_H */


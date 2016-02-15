/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUIcomponent.h
 * Author: renfeiyu
 *
 * Created on February 8, 2016, 4:40 PM
 */

#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H
#include <stdlib.h>
#include <iostream>

#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <stdint.h>
#include "mEventDispatcher.h"
class EventDispatcher;


class GUIComponent {
private:
    EventDispatcher *eventDispatcher;
    
    unsigned componentID;
    enum BoundType {
        Circle,
        Redtangle
    } BoundType;

protected:

public:
    GUIComponent();
    virtual ~GUIComponent();
    
    void setComponentID(int ID);
    int getComponentID();
    
    void setEventDispatcher(EventDispatcher*);
    
    virtual void onDraw(cairo_t*);
    virtual void onRemap(uint_fast8_t*);
    virtual void onCreate();
    virtual void onDestory();
    virtual void onEnter();
    virtual void onLeave();
    virtual void onButtonPress(int x, int y, int buttonCode);
    virtual void onClick(int x, int y);
    virtual void onKeyPress(int keycode);
    virtual void onKeyRelease(int keycode);
    virtual void onDrag(int x, int y);
    virtual void onDrop(int x, int y);
};


#endif /* GUICOMPONENT_H */


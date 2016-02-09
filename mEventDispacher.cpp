/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdint.h>

#include "mEventDispatcher.h"

EventDispatcher::EventDispatcher(int winWidth, int winHeight) : winWidth(winWidth), winHeight(winHeight) {
    componentMap = new uint_fast8_t[winWidth * winHeight];
    for (long int i = 0; i < winWidth * winHeight; i++)
        componentMap[i] = 0;

    addComponent(new GUIComponent());

}

EventDispatcher::~EventDispatcher() {
    free(componentMap);
}

inline unsigned EventDispatcher::TranslatePosition(int x, int y) {
    if (x > winWidth || y > winHeight || x < 0 || y < 0)
        return 0;
    return (unsigned) componentMap[winWidth * y + x];
}

void EventDispatcher::addComponent(GUIComponent* component) {
    vecGUIComponents.push_back(component);
    component->setComponentID(vecGUIComponents.size() - 1);
    component->setEventDispatcher(this);
    component->onCreate();
    component->onRemap(componentMap);
}

void EventDispatcher::globalRemapComponent() {
    for (long int i = 0; i < winWidth * winHeight; i++)
        componentMap[i] = 0;
    for (int i = 0; i < vecGUIComponents.size(); i++)
        vecGUIComponents[i]->onRemap(componentMap);
}

void EventDispatcher::fetchAndDispatchEvent(XEvent *event) {
    unsigned curMapValue = TranslatePosition(event->xmotion.x, event->xmotion.y);

    int pointerX = event->xmotion.x;
    int pointerY = event->xmotion.y;
    int buttonCode = event->xbutton.button;
    int keyCode = event->xkey.keycode;
    switch (event->type) {
        case MotionNotify:
            if (eventState.buttonPressed) {
                eventState.pointerMovedAfterPress = true;
                eventState.dragEventOwner = eventState.lastActiveComp;
                vecGUIComponents[eventState.dragEventOwner]->onDrag(pointerX, pointerY);
                std::cout << "onDrag() called on ID = " << eventState.dragEventOwner << " x: " << pointerX << " y: " << pointerY << std::endl;
                break;
            }

            if (curMapValue != eventState.lastActiveComp) {
                eventState.currentActiveWidget = curMapValue;
                vecGUIComponents[eventState.lastActiveComp ]->onLeave();
                vecGUIComponents[curMapValue]->onEnter();
            }
            eventState.lastActiveComp = curMapValue;
            break;

        case ButtonPress:
            vecGUIComponents[curMapValue]->onButtonPress(pointerX, pointerY, buttonCode);
            eventState.lastActiveComp = curMapValue;
            std::cout << "onButtonPress() called on ID = " << unsigned(curMapValue) << " x: " << pointerX << " y: " << pointerY << " ButtonCode: " << buttonCode << std::endl;
            eventState.pointerMovedAfterPress = false;
            eventState.buttonPressed = true;
            break;

        case ButtonRelease:
            if (eventState.pointerMovedAfterPress) {
                vecGUIComponents[eventState.dragEventOwner]->onDrop(pointerX, pointerY);
                std::cout << "onDrop() called on ID = " << eventState.dragEventOwner << " x: " << pointerX << " y: " << pointerY << std::endl;
                if(curMapValue != eventState.dragEventOwner){
                    vecGUIComponents[eventState.dragEventOwner]->onLeave();
                    vecGUIComponents[curMapValue]->onEnter();
                    eventState.lastActiveComp = curMapValue;
                }
                    
                eventState.pointerMovedAfterPress = false;
                eventState.buttonPressed = false;
                break;
            }

            vecGUIComponents[curMapValue]->onClick(pointerX, pointerY);
            std::cout << "onClick() called on ID = " << unsigned(curMapValue) << " x: " << pointerX << " y: " << pointerY << std::endl;
            eventState.buttonPressed = false;
            eventState.pointerMovedAfterPress = false;

            break;

        case KeyPress:
            vecGUIComponents[eventState.currentActiveWidget]->onKeyPress(keyCode);
            break;
        case KeyRelease:
            vecGUIComponents[eventState.currentActiveWidget]->onKeyRelease(keyCode);

            break;
        case ConfigureNotify:
            std::cout<<"ReConfigured"<<std::endl;
            break;
        default:
            std::cout << "Event not handled ID = " << event->type << std::endl;
            break;
    }
}

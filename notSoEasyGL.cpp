/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "mEventDispatcher.h"


#include <stdlib.h>

#include <X11/Xlib.h>

#include <cairo/cairo.h>
#include <stdlib.h>
#include <iostream>

#include "notSoEasyGL.h"
#include "Config.h"

mWindow::mWindow() {
    looping = false;

    if (!(display = XOpenDisplay(NULL)))
        exit(1);
    screenID = DefaultScreen(display);
    topWin = XCreateSimpleWindow(display, DefaultRootWindow(display),
            0, 0, winWidth, winHeight, 0, 100, 0xfffacd);
    XSelectInput(display, topWin, ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask | ExposureMask);

    frontSurface = cairo_xlib_surface_create(display, topWin,
            DefaultVisual(display, screenID), winWidth, winHeight);
    frontContext = cairo_create(frontSurface);

    GUI_surface = cairo_surface_create_similar(cairo_get_target(frontContext),
            CAIRO_CONTENT_COLOR_ALPHA, winWidth, winHeight);

    //    MAP_surface = cairo_surface_create_similar(cairo_get_target(frontContext),
    //            CAIRO_CONTENT_COLOR_ALPHA, winWidth, winHeight);

    GUI_context = cairo_create(GUI_surface);
    //MAP_context = cairo_create(MAP_surface);

    Gmanager = new GUIManager(GUI_context);
    eventDispatcher = new EventDispatcher(winWidth, winHeight);
    Gmanager->registerEventDispatcher(eventDispatcher);
    eventDispatcher->registerGUImanager(Gmanager);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer);

    //    Eventthread = new std::thread(&mWindow::startEventLoop, this);
    //    GUIthread = new std::thread(&mWindow::updateGUI, this);

}

mWindow::~mWindow() {
    cairo_destroy(GUI_context);
    cairo_destroy(frontContext);
    cairo_surface_destroy(GUI_surface);
    cairo_surface_destroy(frontSurface);
    delete eventDispatcher;
    delete Gmanager;
    //XDestroyWindow(display, topWin);
    //XCloseDisplay(display);
}

void mWindow::showWindow() {
    XMapWindow(display, topWin);
    return;
}

void mWindow::startEventLoop() {
    looping = true;
    timespec cur;

    std::cout << "hello from event thread" << std::endl;
    while (looping) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cur);

        //        if((cur.tv_sec - timer.tv_sec)>5) 
        //            looping = false;
        //std::cout << 1e9 / (cur.tv_nsec - timer.tv_nsec) << std::endl;

        //std::cout << "hello" << std::endl;

        //if (XCheckWindowEvent(display, topWin, ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask | ExposureMask, &event)) {
            XNextEvent(display, &event);
            eventDispatcher->fetchAndDispatchEvent(&event);

        //}
        //std::cout<<"update"<<std::endl;
        updateGUI();
        //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer);
    }
}

void mWindow::stopEventLoop() {
    looping = false;
}

void mWindow::registerDrawGuiFunc(void (*drawGui)(cairo_t*)) {
    callbackFunc.drawGui = drawGui;
}

void mWindow::registerDrawMapFunc(void (*drawMap)(cairo_t*)) {
    callbackFunc.drawMap = drawMap;
}

void mWindow::registerResizeFunc(void (*resize)(int, int)) {
    callbackFunc.resize = resize;
}

void mWindow::updateGUI() {
    
    //cairo_save(frontContext);
//    cairo_set_source_rgb(frontContext, 1, 1, 1);
//    cairo_paint(frontContext);


    if (callbackFunc.drawGui)
        callbackFunc.drawGui(GUI_context);

    Gmanager -> DrawAll();
    //    if (callbackFunc.drawMap)
    //        callbackFunc.drawMap(MAP_context);

    cairo_set_operator(GUI_context, CAIRO_OPERATOR_DEST_OVER);
    //    cairo_set_source_surface(GUI_context, MAP_surface, 0, 0);
    //    cairo_paint(GUI_context);
    cairo_set_source_surface(frontContext, GUI_surface, 0, 0);
    cairo_paint(frontContext);
    
    //cairo_set_source_rgb(GUI_context, 1, 1, 1);
    //cairo_paint(GUI_context);

    //cairo_restore(frontContext);   


}

void mWindow::addGUIComponent(GUIComponentBase* com) {
    Gmanager->addComponent(com);
}

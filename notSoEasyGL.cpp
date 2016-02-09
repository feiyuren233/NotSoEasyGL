/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>

#include <X11/Xlib.h>

#include <cairo/cairo.h>
#include <stdlib.h>
#include <iostream>

#include "notSoEasyGL.h"
#define winWidth 1000
#define winHeight 800

mWindow::mWindow() {
    looping = false;

    if (!(display = XOpenDisplay(NULL)))
        exit(1);
    screenID = DefaultScreen(display);
    topWin = XCreateSimpleWindow(display, DefaultRootWindow(display),
            0, 0, winWidth, winHeight, 0, 0, 0);
    XSelectInput(display, topWin, ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask | ExposureMask);

    frontSurface = cairo_xlib_surface_create(display, topWin,
            DefaultVisual(display, screenID), 1000, 800);
    frontContext = cairo_create(frontSurface);

    GUI_surface = cairo_surface_create_similar(cairo_get_target(frontContext),
            CAIRO_CONTENT_COLOR_ALPHA, winWidth, winHeight);

    MAP_surface = cairo_surface_create_similar(cairo_get_target(frontContext),
            CAIRO_CONTENT_COLOR_ALPHA, winWidth, winHeight);

    GUI_context = cairo_create(GUI_surface);
    MAP_context = cairo_create(MAP_surface);

    eventDispatcher = new EventDispatcher(winWidth, winHeight);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer);

    //    Eventthread = new std::thread(&mWindow::startEventLoop, this);
    //    GUIthread = new std::thread(&mWindow::updateGUI, this);

}

void mWindow::addGUIComponent(GUIComponent* obj) {
    eventDispatcher->addComponent(obj);
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

        if((cur.tv_nsec - timer.tv_nsec)<1000) continue;
        //std::cout << 1e9 / (cur.tv_nsec - timer.tv_nsec) << std::endl;

        //std::cout << "hello" << std::endl;
        
        if (XCheckWindowEvent(display, topWin, ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask | ExposureMask, &event)) {
            //XNextEvent(display, &event);
            eventDispatcher->fetchAndDispatchEvent(&event);

        }
        updateGUI();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer);
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

    if (callbackFunc.drawGui)
        callbackFunc.drawGui(GUI_context);
    //    if (callbackFunc.drawMap)
    //        callbackFunc.drawMap(MAP_context);

    cairo_set_operator(GUI_context, CAIRO_OPERATOR_DEST_OVER);
    //    cairo_set_source_surface(GUI_context, MAP_surface, 0, 0);
    //    cairo_paint(GUI_context);
    cairo_set_source_surface(frontContext, GUI_surface, 0, 0);
    cairo_paint(frontContext);


}


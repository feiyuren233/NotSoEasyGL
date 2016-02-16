/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   notSoEasyGL.h
 * Author: feiyu
 *
 * Created on February 7, 2016, 1:44 AM
 */

#ifndef NOTSOEASYGL_H
#define NOTSOEASYGL_H
#include <X11/keysym.h> 
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/X.h>
#include <time.h>

#include <thread>

#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

#include "mEventDispatcher.h"
#include "GUIComponentBase.h"
#include "GUIManager.h"
#include "Animator.h"
#include "Animatable.h"

class mWindow {
private:
	Display *display;
	int screenID, displayWidth, displayHeight;
	XVisualInfo visual_info;
	Colormap mColorMap;
	Window topWin;

	EventDispatcher *eventDispatcher;
	GUIManager *Gmanager;
	Animator *animator;

	cairo_surface_t *GUI_surface, *MAP_surface, *frontSurface;
	cairo_t *GUI_context, *MAP_context, *frontContext;

	//Multithreading
	//std::thread *GUIthread;
	//std::thread *Eventthread;

	//Pixmap buffer;
	//Event handling
	bool looping;
	XEvent event;


	//Callback functions;
	struct callbackFunc {
		void (*drawMap)(cairo_t *MAP_context);
		void (*drawGui)(cairo_t *GUI_context);
		void (*resize)(int newWidth, int newHeight);

		callbackFunc() :
				drawMap(NULL), drawGui(NULL), resize(NULL) {
		}
	} callbackFunc;

protected:
public:
	mWindow();
	~mWindow();
	void registerDrawMapFunc(void (*drawMap)(cairo_t*));
	void registerDrawGuiFunc(void (*drawGui)(cairo_t*));
	void registerResizeFunc(void (*resize)(int, int));

	void updateGUI();

	void addGUIComponent(GUIComponentBase*);

	void startEventLoop();
	void stopEventLoop();
	void showWindow();
};

#endif /* NOTSOEASYGL_H */


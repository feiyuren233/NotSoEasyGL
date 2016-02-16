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
#include "GUIUtil.h"
#include "Config.h"

#include "GUIManager.h"
class EventDispatcher;
class GUIManager;

class GUIComponentBase {
private:
	static void registerGUImanager(GUIManager*);
	void setComponentID(int ID);
protected:

	static GUIManager *Gmanager;
	uint8_t *GUImap;
	unsigned componentID;

	enum BoundType {
		Circle, Redtangle
	} BoundType;

	//Callbacks
	virtual void onDraw(cairo_t* context);
	virtual void onRemap(uint_fast8_t* map);
	virtual void onUnmap(uint_fast8_t *map);
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

	//Functions exposed to GUIcomponets
	virtual uint8_t idAtGUImapLocation(int x, int y);

public:
	GUIComponentBase();
	virtual ~GUIComponentBase();


	int getComponentID();



	friend class EventDispatcher;
	friend class GUIManager;
};

#endif /* GUICOMPONENT_H */

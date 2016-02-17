/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdint.h>

#include "mEventDispatcher.h"
#include <linux/input.h>
#include <X11/extensions/XInput.h>


EventDispatcher::EventDispatcher(int winWidth, int winHeight) {
	::winWidth = winWidth;
	::winHeight = winHeight;

	//EventDispatcher::GManager = GUImanager;
	//GUImanager->setEventDispatcher(this);
	GUImap = new uint_fast8_t[winWidth * winHeight + 1];
	for (long int i = 0; i < winWidth * winHeight; i++)
		GUImap[i] = 0;
}

EventDispatcher::~EventDispatcher() {
	delete[] GUImap;
}

void EventDispatcher::registerGUImanager(GUIManager* Gmanager) {
	EventDispatcher::GManager = Gmanager;
}

inline unsigned EventDispatcher::TranslatePosition(int x, int y) {
	if (x > winWidth || y > winHeight || x < 0 || y < 0)
		return 0;
	return (unsigned) GUImap[winWidth * y + x];
}

uint8_t* EventDispatcher::getGUImap() {
	return GUImap;
}

void EventDispatcher::fetchAndDispatchEvent(XEvent *event) {
	unsigned curMapValue;
	int pointerX;
	int pointerY;
	int buttonCode;
	switch (event->type) {
	case MotionNotify:
		pointerX = event->xmotion.x;
		pointerY = event->xmotion.y;
		curMapValue = TranslatePosition(event->xmotion.x, event->xmotion.y);
		if (eventState.buttonPressed) {
			eventState.pointerMovedAfterPress = true;
			eventState.dragEventOwner = eventState.activeComp;
			GManager->operator[](eventState.dragEventOwner)->onDrag(pointerX, pointerY);
			//[eventState.dragEventOwner]->onDrag(pointerX, pointerY);
			std::cout << "onDrag() called on ID = " << eventState.dragEventOwner << " x: " << pointerX << " y: " << pointerY << std::endl;
			break;
		}
		if (curMapValue != eventState.activeComp) {
			eventState.currentActiveWidget = curMapValue;
			GManager->operator[](eventState.activeComp)->onUnFocus();
			GManager->operator[](curMapValue)->onFocus();
		}
		eventState.activeComp = curMapValue;
		break;

	case ButtonPress:
		buttonCode = event->xbutton.button;
		pointerX = event->xmotion.x;
				pointerY = event->xmotion.y;
		curMapValue = TranslatePosition(event->xmotion.x, event->xmotion.y);
		GManager->operator[](curMapValue)->onButtonPress(pointerX, pointerY, buttonCode);
		eventState.activeComp = curMapValue;
		std::cout << "onButtonPress() called on ID = " << unsigned(curMapValue) << " x: " << pointerX << " y: " << pointerY
				<< " ButtonCode: " << buttonCode << std::endl;
		eventState.pointerMovedAfterPress = false;
		eventState.buttonPressed = true;
		break;

	case ButtonRelease:
		pointerX = event->xmotion.x;
				pointerY = event->xmotion.y;
		curMapValue = TranslatePosition(event->xmotion.x, event->xmotion.y);
		if (eventState.pointerMovedAfterPress) {
			GManager->operator[](eventState.dragEventOwner)->onDrop(pointerX, pointerY);
			std::cout << "onDrop() called on ID = " << eventState.dragEventOwner << " x: " << pointerX << " y: " << pointerY << std::endl;
			if (curMapValue != eventState.dragEventOwner) {
				GManager->operator[](eventState.dragEventOwner)->onUnFocus();
				GManager->operator[](curMapValue)->onFocus();
				eventState.activeComp = curMapValue;
			}

			eventState.pointerMovedAfterPress = false;
			eventState.buttonPressed = false;
			break;
		}

		GManager->operator[](curMapValue)->onClick(pointerX, pointerY);
		std::cout << "onClick() called on ID = " << unsigned(curMapValue) << " x: " << pointerX << " y: " << pointerY << std::endl;
		eventState.buttonPressed = false;
		eventState.pointerMovedAfterPress = false;

		break;
	case KeyPress:
		inputLength = XLookupString(&event->xkey, buffer, 1, &keysym, NULL);
		GManager->operator[](eventState.currentActiveWidget)->onKeyPress(buffer[0]);
		//std::cout<<keyCode<<std::endl;
		break;
	case KeyRelease:
		inputLength = XLookupString(&event->xkey, buffer, 1, &keysym, NULL);
		GManager->operator[](eventState.currentActiveWidget)->onKeyRelease(buffer[0]);
		break;
	case ConfigureNotify:
		std::cout << "ReConfigured" << std::endl;
		std::cout << event->xconfigure.width << "  " << event->xconfigure.height << std::endl;
		//std::cout<<event->xclient.data.<<"  "<<event->xresizerequest.height<<std::endl;
		break;
	default:
		std::cout << "Event not handled ID = " << event->type << std::endl;
		break;
	}
}


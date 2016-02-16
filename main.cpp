/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: feiyu
 *
 * Created on February 7, 2016, 1:43 AM
 */

#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <X11/Xlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

#include "Config.h"
#include "notSoEasyGL.h"
#include "mEventDispatcher.h"
#include "WidgetButton.h"

#define M_PI 3.1415

int width, height;

void draw(cairo_t *cr) {

	//std::cout << "DrawGUI" << std::endl;

	double x = 25.6, /* parameters like cairo_rectangle */
	y = 25.6, width = 204.8, height = 204.8, aspect = 1.0, /* aspect ratio */
	corner_radius = height / 10.0; /* and corner curvature radius */

	double radius = corner_radius / aspect;
	double degrees = M_PI / 180.0;

	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees,
			0 * degrees);
	cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees,
			90 * degrees);
	cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees,
			180 * degrees);
	cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);

	cairo_set_source_rgb(cr, 0.5, 0.5, 1);
	cairo_fill_preserve(cr);
	cairo_set_source_rgba(cr, 0.5, 0, 0, 0.5);
	cairo_set_line_width(cr, 10.0);
	cairo_stroke(cr);
}

void draw2(Button *b, cairo_t *cr) {

	//std::cout << "Draw2!!!" << std::endl;

	double x0 = b->getTLPosition().x, /* parameters like cairo_rectangle */
	y0 = b->getTLPosition().y, rect_width = 500, rect_height = 500, radius =
			102.4; /* and an approximate curvature radius */

	double x1, y1;

	x1 = x0 + rect_width;
	y1 = y0 + rect_height;
	if (!rect_width || !rect_height)
		return;
	if (rect_width / 2 < radius) {
		if (rect_height / 2 < radius) {
			cairo_move_to(cr, x0, (y0 + y1) / 2);
			cairo_curve_to(cr, x0, y0, x0, y0, (x0 + x1) / 2, y0);
			cairo_curve_to(cr, x1, y0, x1, y0, x1, (y0 + y1) / 2);
			cairo_curve_to(cr, x1, y1, x1, y1, (x1 + x0) / 2, y1);
			cairo_curve_to(cr, x0, y1, x0, y1, x0, (y0 + y1) / 2);
		} else {
			cairo_move_to(cr, x0, y0 + radius);
			cairo_curve_to(cr, x0, y0, x0, y0, (x0 + x1) / 2, y0);
			cairo_curve_to(cr, x1, y0, x1, y0, x1, y0 + radius);
			cairo_line_to(cr, x1, y1 - radius);
			cairo_curve_to(cr, x1, y1, x1, y1, (x1 + x0) / 2, y1);
			cairo_curve_to(cr, x0, y1, x0, y1, x0, y1 - radius);
		}
	} else {
		if (rect_height / 2 < radius) {
			cairo_move_to(cr, x0, (y0 + y1) / 2);
			cairo_curve_to(cr, x0, y0, x0, y0, x0 + radius, y0);
			cairo_line_to(cr, x1 - radius, y0);
			cairo_curve_to(cr, x1, y0, x1, y0, x1, (y0 + y1) / 2);
			cairo_curve_to(cr, x1, y1, x1, y1, x1 - radius, y1);
			cairo_line_to(cr, x0 + radius, y1);
			cairo_curve_to(cr, x0, y1, x0, y1, x0, (y0 + y1) / 2);
		} else {
			cairo_move_to(cr, x0, y0 + radius);
			cairo_curve_to(cr, x0, y0, x0, y0, x0 + radius, y0);
			cairo_line_to(cr, x1 - radius, y0);
			cairo_curve_to(cr, x1, y0, x1, y0, x1, y0 + radius);
			cairo_line_to(cr, x1, y1 - radius);
			cairo_curve_to(cr, x1, y1, x1, y1, x1 - radius, y1);
			cairo_line_to(cr, x0 + radius, y1);
			cairo_curve_to(cr, x0, y1, x0, y1, x0, y1 - radius);
		}
	}
	cairo_close_path(cr);

	cairo_set_source_rgba(cr, 1, 0.5, 1.0, 0.1);
	cairo_fill_preserve(cr);
	cairo_set_source_rgba(cr, 0.5, 0, 0, 0.5);
	cairo_set_line_width(cr, 10.0);
	cairo_stroke(cr);
}

void ondrag(Button* b, int x, int y) {
	b->setTLPosition(x, y);
}

int winWidth, winHeight;

int main() {
	initGUISys(1280, 960);
	mWindow win;
	win.addGUIComponent(new GUIComponentBase(0, 0));
	Button *zeroButton = new Button(400, 400, 500, 460);
	//zeroButton->regOnDraw(draw2);
	win.addGUIComponent(zeroButton);

	win.registerDrawGuiFunc(draw);

	win.showWindow();

	win.startEventLoop();

	return 0;

}

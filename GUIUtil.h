/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUIUtil.h
 * Author: renfeiyu
 *
 * Created on February 8, 2016, 6:12 PM
 */

#ifndef GUIUTIL_H
#define GUIUTIL_H
//#include "GUIComponentBase.h"
#include "Config.h"
#include <time.h>

struct Point2i {
	int x, y;

	Point2i(int x, int y);

	Point2i();

	Point2i operator+(Point2i other);

	Point2i operator-(Point2i other);

};

unsigned TranslateMap(int x, int y);
void initGUISys(int winWidth, int winHeight);
int operator-(timespec p1, timespec p2);
#endif /* GUIUTIL_H */


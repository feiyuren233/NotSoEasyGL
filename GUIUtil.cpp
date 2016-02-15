/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GUIUtil.h"
#include "WidgetButton.h"

#include "Config.h"


unsigned TranslateMap(int x, int y){
	if (x < 0 || x > winWidth || y < 0 || y > winHeight)
		return winWidth * winHeight;
	return y * winWidth + x;
}

Point2i::Point2i(int x, int y) : x(x), y(y) {
}

Point2i::Point2i() {
    x = y = 0;
}

Point2i Point2i::operator+(Point2i other) {
    return Point2i(x + other.x, y + other.y);
}

Point2i Point2i::operator-(Point2i other) {
    return Point2i(x - other.x, y - other.y);
}

void initGUISys(int winWid, int winHei){
    winWidth = winWid;
    winHeight = winHei;
    
    
}

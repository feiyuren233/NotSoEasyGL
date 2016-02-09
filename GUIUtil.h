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

struct Point2i {
    int x, y;

    Point2i(int x, int y) : x(x), y(y) {
    }

    Point2i operator+(Point2i other) {
        return Point2i(x + other.x, y + other.y);
    }
    Point2i operator-(Point2i other) {
        return Point2i(x - other.x, y - other.y);
    }

};

#endif /* GUIUTIL_H */


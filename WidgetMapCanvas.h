/*
 * WidgetMapCanvas.h
 *
 *  Created on: Feb 15, 2016
 *      Author: feiyu
 */

#ifndef WIDGETMAPCANVAS_H_
#define WIDGETMAPCANVAS_H_

#include "GUIComponentBase.h"

class WidgetMapCanvas: public GUIComponentBase {
private:
	int viewPortWidth, viewPortHeight;
	Point2i center;
protected:

public:
	WidgetMapCanvas(int x, int y);
	virtual ~WidgetMapCanvas();



};

#endif /* WIDGETMAPCANVAS_H_ */

/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef ROUTETOOL_H
#define ROUTETOOL_H
#include "tool.h"
#include "eaglewire.h"
class QMainWindow;
class QMouseEvent;
class QKeyEvent;

class RouteTool : public Tool {
	Q_OBJECT;
public:
	RouteTool(EDATool *);
	void install();
	void uninstall();
	void activate();
	void deactivate();
protected:
	bool eventFilter(QObject *obj, QEvent *event);
public slots:
	void trigger(bool);
private:
	bool routing;
	void updateWayPoint();
	QPointF start, stop, wayPoint;
	EagleWire *tempSegment1;
	EagleWire *tempSegment2;
	bool exitortho;
};

#endif

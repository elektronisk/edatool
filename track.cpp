/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "track.h"
#include <QPainterPath>
#include <math.h>
#include <QMatrix>
Track::Track(double x1, double y1, double x2, double y2, double w) {
	//polygon = new Polygon();
	QPainterPath p;
	double r = w/2.0;
	double dx = x2 - x1;
	double dy = y2 - y1;
	double l = sqrt(dx*dx + dy*dy);
	double angle;
	
	angle = atan2(dy, dx);

	p.moveTo(0, r);
	p.arcTo(l+r, r, -w, -w, 90, 180);
	p.arcTo(r, -r, -w, w, 90, -180);
	
	QMatrix m;
	m.translate(x1, y1);
	m.rotate(angle*(180.0/M_PI));
	this->shell = p.toFillPolygon(m);
	this->generateGeometry();
}
Track::~Track() {
	//delete polygon;
}


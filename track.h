/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef TRACK_H
#define TRACK_H

#include "polygon.h"

class Track : public PCB::Polygon {
public:
	Track(double x1, double y1, double x2, double y2, double w);
	~Track();
	PCB::Polygon *polygon;
private:
};


#endif
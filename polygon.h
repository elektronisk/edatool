/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <geos.h>
#include <QPolygonF>
#include <QPointF>
#include <QList>

namespace PCB {
	class Polygon {
	public:
		Polygon();
		~Polygon();
		
		QPolygonF shell;
		//todo hole support
		int generateGeometry();
		geos::geom::Geometry *geo;
		geos::geom::Geometry *envelope;
	private:
		void clean();
		
		
	};
}
#endif
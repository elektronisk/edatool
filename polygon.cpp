/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "polygon.h"

namespace PCB {
	Polygon::Polygon() {
		//qDebug("Instantiating a polygon");
		this->geo = 0;
		this->envelope = 0;
	}

	Polygon::~Polygon() {
		//qDebug("Destroying a polygon");
		geos::geom::GeometryFactory factory;
		this->clean();
	}
	void Polygon::clean() {
		geos::geom::GeometryFactory factory;
		if (this->geo != 0) {
			factory.destroyGeometry(this->geo);
		}
		if (this->envelope != 0) {
			factory.destroyGeometry(this->envelope);
		}
	}
	int Polygon::generateGeometry() {
		if (this->shell.size() == 0) {
			qDebug("Attempted to generate with shellsize = 0");
			return 0;
		}
		
		this->clean(); // remove potentially existing geometries or envelopes
		
		geos::geom::GeometryFactory factory;
		geos::geom::CoordinateSequence *seq = new geos::geom::CoordinateArraySequence();

		for (int i = 0; i < shell.size(); i++) {
			seq->add(geos::geom::Coordinate(shell[i].x(), shell[i].y()));
		}
		geos::geom::LinearRing *ring = factory.createLinearRing(seq);
		std::vector<Geometry*> *holes = 0;
		this->geo = factory.createPolygon(ring, holes);
		this->envelope = this->geo->getEnvelope();

		// TODO: implement holes
		return 0;
	}
}
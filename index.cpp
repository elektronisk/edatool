/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGlobal>
#include <QPoint>
#include "index.h"

namespace Index {
	void insertItem(quadtree::Quadtree *tree, PCB::Polygon *poly) {
		if (poly->envelope == 0) {
			qDebug("Index: tried inserting null polygon (non-generated). Ignoring.");
			return;
		}
		tree->insert(poly->geo->getEnvelopeInternal(), (void *) poly);
	}
	
	// search in rectangle
	void searchItem(quadtree::Quadtree *tree, double x1, double y1, double x2, double y2, std::vector<void *>& result) {
		Envelope e(x1,y1,x2,y2);
		tree->query(&e,result);
	}
	void searchItem(quadtree::Quadtree *tree, QPoint& p1, QPoint& p2, std::vector<void *>& result) {
		Envelope e(p1.x(),p1.y(),p2.x(),p2.y());
		tree->query(&e,result);
	}
	
	// search using point
	void searchItem(quadtree::Quadtree *tree, double x, double y, std::vector<void *>& result) {
		Coordinate c(x,y);
		Envelope e(c);
		tree->query(&e,result);
	}
	void searchItem(quadtree::Quadtree *tree, QPoint& p, std::vector<void *>& result) {
		Coordinate c(p.x(),p.y());
		Envelope e(c);
		tree->query(&e,result);
	}
	void searchItem(quadtree::Quadtree *tree, const geos::geom::Envelope *env, std::vector<void *>& result) {
		tree->query(env, result);
	}
}
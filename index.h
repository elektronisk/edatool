/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef INDEX_H
#define INDEX_H

#include <geos.h>
#include "polygon.h"
#include <geos/indexQuadtree.h>

// inteded as a wrapper and convenience layer around GEOS
using namespace geos::index;
namespace Index {
	void insert(quadtree::Quadtree *tree, PCB::Polygon *poly);
	void search_poly(quadtree::Quadtree *tree, const geos::geom::Envelope *env, std::vector<void *>& result);
}

#endif
#ifndef EAGLEPOLYGON_H
#define EAGLEPOLYGON_H

#include <QPolygonF>
#include "clipper.h"

#include "pcbgraphicsitem.h"
class EaglePolygon : public PCBGraphicsItem {
public:
	EaglePolygon(QPolygonF _vertices, qreal _width, int _layer, qreal _spacing);
	QRectF boundingRect() const;
	void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w);
	enum { Type = UserType + 5 };
	int type() const {
		return Type;
	}
private:
	QPolygonF vertices;
	ClipperLib::Polygons sourcePoly, buffedPoly;
	qreal width;
	int layer;
	qreal spacing;
};

#endif // EAGLEPOLYGON_H

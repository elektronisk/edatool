#include <QPainter>
#include <QDebug>
#include "eaglepolygon.h"
#include "edatool.h"
#include "clipper.h"

#define RES 1000.0

EaglePolygon::EaglePolygon(QPolygonF _vertices, qreal _width, int _layer, qreal _spacing) {
	width = _width; layer = _layer; spacing = _spacing;
	sourcePoly.resize(_vertices.count());
	for (int i = 0; i < _vertices.count(); i++) {
		ClipperLib::long64 x = (ClipperLib::long64)(_vertices.at(i).x()*RES);
		ClipperLib::long64 y = (ClipperLib::long64)(_vertices.at(i).y()*RES);
		sourcePoly[0].push_back(ClipperLib::IntPoint(x,y));
	}

	ClipperLib::Clipper c;
	c.AddPolygons(sourcePoly, ClipperLib::ptSubject);
	c.Execute(ClipperLib::ctUnion,sourcePoly); // only makes sure polys orientation is correct

	ClipperLib::OffsetPolygons(sourcePoly,buffedPoly, width*RES/2, ClipperLib::jtRound); // offset

	for (unsigned int i = 0; i < buffedPoly[0].size(); i++) {
		vertices.append(QPointF(buffedPoly[0].at(i).X/RES, buffedPoly[0].at(i).Y/RES));
	}
}

QRectF EaglePolygon::boundingRect() const {
	const qreal halfwidth = width/2;
	return vertices.boundingRect().adjusted(-halfwidth, -halfwidth, halfwidth, halfwidth);
	// TODO: cache bounding rectangle
}
void EaglePolygon::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) {
	QBrush brush; QPen pen;
	EDATool::layerToPenBrush(layer, pen, brush);
	p->setBrush(brush);
	p->setPen(pen);

	p->drawPolygon(vertices);

}

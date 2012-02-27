#include <QRectF>
#include <QPainter>
#include <QDebug>
#include <QtCore/qmath.h>
#include "eaglepad.h"
#include "edatool.h"
#include <cmath>
EaglePad::EaglePad(qreal _x, qreal _y, qreal _drill, qreal _diameter, PadShape _shape, bool stop, bool thermals, bool first) {
	x = _x; y = _y; drill = _drill; diameter = _diameter; shape = _shape;
	if (diameter < 0) {
		diameter = drill*1.5;
	}
	generateOctagon();
	snapPoints.append(QPointF(x,y));
}

void EaglePad::generateOctagon() {
	const qreal r = diameter/2;
	const qreal rcos = r/**qCos(22.5*M_PI/180)*/;
	const qreal rsin = r*qSin(22.5*M_PI/180)/qCos(22.5*M_PI/180); // TODO: optimize
	// TODO: check if i should use inner or outer diameter
	octagon.clear();
	octagon.append(QPointF(x+rcos, y+rsin)); // first quadrant, go anti-clockwise
	octagon.append(QPointF(x+rsin, y+rcos));
	octagon.append(QPointF(x-rsin, y+rcos)); // second quadrant
	octagon.append(QPointF(x-rcos, y+rsin));
	octagon.append(QPointF(x-rcos, y-rsin)); // third
	octagon.append(QPointF(x-rsin, y-rcos));

	octagon.append(QPointF(x+rsin, y-rcos));// fourth
	octagon.append(QPointF(x+rcos, y-rsin));
}

QRectF EaglePad::boundingRect() const {
	const qreal halfdiameter = diameter/2;
	return QRectF(QPointF(x-halfdiameter, y-halfdiameter), QPointF(x+halfdiameter, y+halfdiameter));
}

void EaglePad::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) {
	const qreal r = diameter/2;

	QBrush brush; QPen pen;
	EDATool::layerToPenBrush(layer, pen, brush);
	p->setBrush(brush);
	p->setPen(pen);

	switch(shape) {
	case EaglePad::Square:
		p->drawRect(QRectF(QPointF(x-r, y-r), QPointF(x+r, y+r)));
		break;
	case EaglePad::Round:
		p->drawEllipse(QPointF(x,y), (qreal)r, (qreal)r);
		break;
	case EaglePad::Octagon:
		p->drawPolygon(octagon);
		break;
	default:
		break;
	}
	if (drill != 0.0) {
		p->drawEllipse(QPointF(x,y), drill/2, drill/2);
	}

}

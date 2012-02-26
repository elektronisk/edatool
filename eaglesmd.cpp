#include <QPainter>
#include "eaglesmd.h"
#include "edatool.h"

EagleSmd::EagleSmd(qreal _x, qreal _y, qreal _dx, qreal _dy, int _layer, int _roundness, QString _rot, bool _stop, bool _thermals, bool _cream) {
	x = _x; y = _y;	dx = _dx; dy = _dy; layer = _layer; roundness = _roundness;
	rot = _rot; stop = _stop; thermals = _thermals; cream = _cream;
	// TODO: handle rotations properly

	snapPoints.append(QPointF(x,y));
}

QRectF EagleSmd::boundingRect() const {
	qreal sidehalf = qMax(dx,dy)/2;
	return QRectF(QPointF(x-sidehalf, y-sidehalf), QPointF(x+sidehalf, y+sidehalf));
}
void EagleSmd::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) {
	qreal xhalf = dx/2;
	qreal yhalf = dy/2;

	p->translate(QPointF(x,y));
	if (rot == "R90" || rot == "R270") {
		p->rotate(90);
	}
	QBrush b(EDATool::layerToColor(layer), Qt::SolidPattern);
	p->setBrush(b);
	p->setPen(QPen(EDATool::layerToColor(layer)));
	p->drawRect(QRectF(QPointF(-xhalf, -yhalf), QPointF(+xhalf, +yhalf)));
}

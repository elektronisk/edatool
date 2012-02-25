#include <QPainter>
#include "smd.h"

Smd::Smd(qreal _x, qreal _y, qreal _dx, qreal _dy) {
	x = _x; y = _y;	dx = _dx; dy = _dy;

	snapPoints.append(QPointF(x,y));
}

QRectF Smd::boundingRect() const {
	qreal xhalf = dx/2;
	qreal yhalf = dy/2;
	return QRectF(QPointF(x-xhalf, y-yhalf), QPointF(x+xhalf, y+yhalf));
}
void Smd::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) {
	qreal xhalf = dx/2;
	qreal yhalf = dy/2;
	QBrush b(QColor::fromRgba(qRgba(255, 0, 0, 128)), Qt::SolidPattern);
	p->setBrush(b);
	p->setPen(QPen(QColor(QColor::fromRgba(qRgba(255, 0, 0, 128)))));
	p->drawRect(QRectF(QPointF(x-xhalf, y-yhalf), QPointF(x+xhalf, y+yhalf)));
}

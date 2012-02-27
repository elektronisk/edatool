#include <QPainter>
#include "eaglerectangle.h"
#include "edatool.h"

EagleRectangle::EagleRectangle(qreal _x1, qreal _y1, qreal _x2, qreal _y2, int _layer, QString _rot)
{
	x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2; layer = _layer; rot = _rot;
}

QRectF EagleRectangle::boundingRect() const {
	// TODO: take rotation into consideration
	return QRectF(QPointF(x1,y1), QPointF(x2,y2));
}
void EagleRectangle::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w) {
	if (rot == "R90" || rot == "R270") {
		p->rotate(90);
	}
	QBrush brush; QPen pen;
	EDATool::layerToPenBrush(layer, pen, brush);
	p->setBrush(brush);
	p->setPen(pen);
	p->drawRect(QRectF(QPointF(x1,y1), QPointF(x2,y2)));
}

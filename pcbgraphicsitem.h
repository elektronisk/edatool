#ifndef PCBGRAPHICSITEM_H
#define PCBGRAPHICSITEM_H

#include <QGraphicsItem>

class PCBGraphicsItem : public QGraphicsItem
{
public:
	PCBGraphicsItem(QGraphicsItem *parent = 0);
	QList<QPointF> snapPoints;
	bool snapIgnore;
signals:
	
public slots:
	
};

#endif // PCBGRAPHICSITEM_H

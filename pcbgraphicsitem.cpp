#include "pcbgraphicsitem.h"

PCBGraphicsItem::PCBGraphicsItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
	 snapIgnore = false;
	 layer = 1;
}

#ifndef EAGLEFORMAT_H
#define EAGLEFORMAT_H

#include <QtXml>
#include "eaglepad.h"
class QIODevice;
class QGraphicsScene;
class EaglePad;
class EagleWire;
class EagleSmd;
class EagleRectangle;
class EaglePolygon;

class EagleFormat {
public:
	EagleFormat();
	bool read(QIODevice*, QGraphicsScene *scene);
private:
	QDomDocument domDocument;
	EagleRectangle *CreateRectangle(QDomElement *e);
	EaglePad *CreatePad(QDomElement *e);
	EagleSmd *CreateSmd(QDomElement *e);
	EagleWire *CreateWire(QDomElement *e);
	EaglePolygon *CreatePolygon(QDomElement *e);
	EaglePad::PadShape stringToPadShape(QString _shape);
};

#endif // EAGLEFORMAT_H

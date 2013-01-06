#include <QGraphicsScene>
#include <QHash>
#include "eagleformat.h"
#include "board.h"
#include "eaglewire.h"
#include "eaglesmd.h"
#include "eaglepad.h"
#include "eaglerectangle.h"
#include "eaglepolygon.h"

EagleFormat::EagleFormat()
{
}

bool EagleFormat::read(QIODevice *device, QHash<QString, QGraphicsItemGroup*> *cache) {
	QString errorStr;
	int errorLine;
	int errorColumn;
	cache->clear();
	if (!domDocument.setContent(device, true, &errorStr, &errorLine, &errorColumn)) {
		qDebug() << QString("parse error: %1 %2 %3").arg(errorStr).arg(errorLine).arg(errorColumn);
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if (root.tagName() != "eagle") {
		qDebug() << "File is not Eagle file";
		return false;
	} else if (root.hasAttribute("version")) {
		QString ver = root.attribute("version");
		if (!(ver == "6.1" || ver == "6.0" )) {
			qDebug() << "File is not version 6";
			return false;
		}
	}

	QDomElement libraries = root.firstChildElement("drawing").firstChildElement("board").firstChildElement("libraries");
	QDomElement library = libraries.firstChildElement("library");
	for (; !library.isNull(); library = library.nextSiblingElement("library")) {
		qDebug() << library.attribute("name");
		QDomElement packages = library.firstChildElement("packages");
		QDomElement package = packages.firstChildElement("package");
		for (; !package.isNull(); package = package.nextSiblingElement("package")) {
			qDebug() << " " << package.attribute("name");
			QGraphicsItemGroup *group = new QGraphicsItemGroup();
			QDomElement child = package.firstChildElement();
			while (!child.isNull()) {
				if (child.tagName() == "wire") {
					group->addToGroup(CreateWire(&child));
				} else if (child.tagName() == "rectangle") {
					group->addToGroup(CreateRectangle(&child));
				} else if (child.tagName() == "smd") {
					group->addToGroup(CreateSmd(&child));
				} else if (child.tagName() == "pad") {
					group->addToGroup(CreatePad(&child));
				} else if (child.tagName() == "polygon") {
					group->addToGroup(CreatePolygon(&child));
				} else if (child.tagName() == "text") {
					//QGraphicsTextItem *text = scene->addText(child.text());
					//text->setFont(QFont("ISOCPEUR", 1));
					//text->setPos(x, y);
				}

				child = child.nextSiblingElement();
			}
			cache->insert(package.attribute("name"), group);
		}
	}

	return true;
}

bool stringToBool(QString b) {
	if (b == "yes")
		return true;
	else
		return false;
}

EaglePad *EagleFormat::CreatePad(QDomElement *e) { // construct directly from XML element
	qreal x, y, drill, diameter; // TODO: Implement rotation
	EaglePad::PadShape shape;
	bool stop, thermals, first;
	x = e->attribute("x", "0").toFloat();
	y = e->attribute("y", "0").toFloat();
	drill = e->attribute("drill", "0").toFloat();
	diameter = e->attribute("diameter", "-1").toFloat();
	shape = stringToPadShape(e->attribute("shape", "round"));
	stop = stringToBool(e->attribute("stop", "yes"));
	thermals = stringToBool(e->attribute("thermals", "yes"));
	first = stringToBool(e->attribute("first", "no"));
	return(new EaglePad(x,y,drill,diameter,shape, stop,thermals,first));
}

EagleSmd *EagleFormat::CreateSmd(QDomElement *e) {
	qreal x, y, dx, dy;
	int layer, roundness;
	QString rot;
	bool stop, thermals, cream;
	x = e->attribute("x", "0").toFloat();
	y = e->attribute("y", "0").toFloat();
	dx = e->attribute("dx", "0.1").toFloat();
	dy = e->attribute("dy", "0.1").toFloat();
	layer = e->attribute("layer", "1").toInt();
	roundness = e->attribute("roundness", "0").toInt();
	rot = e->attribute("rot", "R0");
	stop = stringToBool(e->attribute("stop", "yes"));
	thermals = stringToBool(e->attribute("thermals", "yes"));
	cream = stringToBool(e->attribute("cream", "yes"));
	return(new EagleSmd(x,y,dx,dy,layer,roundness,rot,stop,thermals,cream));
}

EagleWire *EagleFormat::CreateWire(QDomElement *e) {
	qreal x1, y1, x2, y2, width;
	int layer;
	// TODO extent, implement style, curve, cap
	x1 = e->attribute("x1", "0").toFloat();
	y1 = e->attribute("y1", "0").toFloat();
	x2 = e->attribute("x2", "0").toFloat();
	y2 = e->attribute("y2", "0").toFloat();
	width = e->attribute("width", "0.1").toFloat();
	layer = e->attribute("layer", "1").toInt();
	return(new EagleWire(QPointF(x1,y1), QPointF(x2,y2), width, layer));
}

EagleRectangle *EagleFormat::CreateRectangle(QDomElement *e) {
	qreal x1, y1, x2, y2;
	int layer;
	QString rot;
	// TODO extent, implement style, curve, cap
	x1 = e->attribute("x1", "0").toFloat();
	y1 = e->attribute("y1", "0").toFloat();
	x2 = e->attribute("x2", "0").toFloat();
	y2 = e->attribute("y2", "0").toFloat();
	layer = e->attribute("layer", "1").toInt();
	rot = e->attribute("rot", "R0");
	return(new EagleRectangle(x1, y1, x2,y2, layer, rot));
}

EaglePolygon *EagleFormat::CreatePolygon(QDomElement *e) {
	QPolygonF vertices; qreal width; int layer; qreal spacing;
	width = e->attribute("width", "0.1").toFloat();
	layer = e->attribute("layer", "1").toInt();
	spacing = e->attribute("spacing","0").toFloat();
	QDomElement vertex = e->firstChildElement("vertex");
	while (!vertex.isNull()) {
		qreal x = vertex.attribute("x", "0").toFloat();
		qreal y = vertex.attribute("y", "0").toFloat();
		vertices.append(QPointF(x,y));
		vertex = vertex.nextSiblingElement("vertex");
	}
	return (new EaglePolygon(vertices, width, layer, spacing));

}

EaglePad::PadShape EagleFormat::stringToPadShape(QString _shape) {
	if (_shape == "square") {
		return EaglePad::Square;
	} else if (_shape == "round"){
		return EaglePad::Round;
	} else if (_shape == "octagon") {
		return EaglePad::Octagon;
	} else {
		qDebug() << "Unsupported shape " << _shape;
		return EaglePad::Round;
	}
}

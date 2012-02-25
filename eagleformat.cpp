#include <QMessageBox>
#include <QGraphicsScene>

#include "eagleformat.h"
#include "board.h"
#include "wire.h"
#include "smd.h"

EagleFormat::EagleFormat()
{
}

bool EagleFormat::read(QIODevice *device, QGraphicsScene *scene) {
	QString errorStr;
	int errorLine;
	int errorColumn;

	if (!domDocument.setContent(device, true, &errorStr, &errorLine, &errorColumn)) {
		qDebug() << QString("parse error: %1 %2 %3").arg(errorStr).arg(errorLine).arg(errorColumn);
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if (root.tagName() != "eagle") {
		qDebug() << "File is not Eagle file";
		return false;
	} else if (root.hasAttribute("version")
			   && root.attribute("version") != "6.0") {
		qDebug() << "File is not version 6";
		return false;
	}

	QDomElement libraries = root.firstChildElement("drawing").firstChildElement("board").firstChildElement("libraries");
	QDomElement library = libraries.firstChildElement("library");
	for (; !library.isNull(); library = library.nextSiblingElement("library")) {
		qDebug() << library.attribute("name");
		QDomElement packages = library.firstChildElement("packages");
		QDomElement package = packages.firstChildElement("package");
		for (; !package.isNull(); package = package.nextSiblingElement("package")) {
			qDebug() << " " << package.attribute("name");
			if (package.attribute("name") == "TQFP100") {

				QDomElement child = package.firstChildElement("wire");
				while (!child.isNull()) {
					float x, y, dx, dy, x1, x2, y1, y2, w, size;
					x1 = child.attribute("x1", "0").toFloat();
					x2 = child.attribute("x2", "0").toFloat();
					y1 = child.attribute("y1", "0").toFloat();
					y2 = child.attribute("y2", "0").toFloat();
					x = child.attribute("x", "0").toFloat();
					y = child.attribute("y", "0").toFloat();
					dx = child.attribute("dx", "0.1").toFloat();
					dy = child.attribute("dy", "0.1").toFloat();
					w = child.attribute("width", "0.1").toFloat();
					size = child.attribute("width", "1").toFloat();

					if (child.tagName() == "wire") {
						scene->addItem(new Wire(QPoint(x1, y1), QPoint(x2, y2), w));
					} else if (child.tagName() == "rectangle") {
						scene->addRect(x1, y1, x2-x1, y2-y1);
					} else if (child.tagName() == "smd") {
						scene->addItem(new Smd(x,y,dx,dy));
					} else if (child.tagName() == "polygon") {
						QDomElement vertex = child.firstChildElement("vertex");
						QPolygonF poly;
						while (!vertex.isNull()) {
							x = vertex.attribute("x", "0").toFloat();
							y = vertex.attribute("y", "0").toFloat();
							poly.append(QPointF(x,y));
							vertex = vertex.nextSiblingElement("vertex");
						}
						scene->addPolygon(poly);
					} else if (child.tagName() == "text") {
						QGraphicsTextItem *text = scene->addText(child.text());
						text->setFont(QFont("ISOCPEUR", 1));
						text->setPos(x, y);
					}

					child = child.nextSiblingElement();
				}
			}
		}
	}

	return true;
}

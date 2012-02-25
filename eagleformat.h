#ifndef EAGLEFORMAT_H
#define EAGLEFORMAT_H
#include <QtXml>
class QGraphicsScene;

class EagleFormat
{
public:
	EagleFormat();
	bool read(QIODevice*, QGraphicsScene *scene);
private:
	QDomDocument domDocument;
};

#endif // EAGLEFORMAT_H

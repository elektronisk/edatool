#ifndef ROUTETOOL_H
#define ROUTETOOL_H
#include "tool.h"
#include "track.h"
class QMainWindow;
class QMouseEvent;
class QKeyEvent;

class RouteTool : public Tool {
	Q_OBJECT;
public:
	RouteTool(EDATool *);
	void install();
	void uninstall();
	void activate();
	void deactivate();
protected:
	bool eventFilter(QObject *obj, QEvent *event);
public slots:
	void trigger(bool);
private:
	void updateWayPoint();
	QPointF start, stop, wayPoint;
	Track *tempSegment1;
	Track *tempSegment2;
	bool exitortho;
};

#endif
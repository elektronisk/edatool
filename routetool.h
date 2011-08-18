#ifndef ROUTETOOL_H
#define ROUTETOOL_H
#include "tool.h"
class QMainWindow;
class RouteTool : public Tool {
	Q_OBJECT;
public:
	RouteTool(EDATool *);
	void install();
	void uninstall();
public slots:
	void showmessage();
};

#endif
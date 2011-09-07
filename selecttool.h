/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tool.h"

class SelectTool : public Tool {
	Q_OBJECT
public:
	SelectTool(EDATool *);
	void install();
	void uninstall();
	void activate();
	void deactivate();
protected:
	bool eventFilter(QObject *obj, QEvent *event);
public slots:
	void trigger(bool);

};

#endif
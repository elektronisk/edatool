/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef EDATOOL_H
#define EDATOOL_H

#include <QMainWindow>
#include "polygon.h"
#include "board.h"
#include "tool.h"

class EditorArea;

class EDATool : public QMainWindow {
	Q_OBJECT
public:
	EDATool();
	friend class Tool;
private slots:
private:
	QMenu *fileMenu;
	QMenu *editMenu;
};

#endif
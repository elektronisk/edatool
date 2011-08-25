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
#include "boardview.h"

class EditorArea;
class QGraphicsScene;

class EDATool : public QMainWindow {
	Q_OBJECT
public:
	EDATool();
	friend class Tool;
private slots:
private:
	QToolBar *toolBar;
	QGraphicsScene *boardScene;
	BoardView *boardView;
	QMenu *fileMenu;
	QMenu *editMenu;
};

#endif
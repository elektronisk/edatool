/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef TOOL_H
#define TOOL_H

#include <QObject>
class QAction;
class QMainWindow;
class QMenu;
class EDATool;
class QGraphicsView;
class BoardView;
class QGraphicsScene;
class QToolBar;

class Tool : public QObject {
	Q_OBJECT
public:
	Tool(EDATool *mainWindow);
	~Tool();
	virtual void install() = 0; /* Implemented by tool itself */
	virtual void uninstall() = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;
	
	QMenu *getFileMenu();
	QMenu *getEditMenu();
	QMenu *getPlaceMenu();
	BoardView *getBoardView();
	QGraphicsScene *getBoardScene();
	QToolBar *getToolBar();
protected:
	bool active;
	EDATool *mainWindow;
	QAction *action; /* pointer to created action, that triggers the tool */
	/* other state information for the tool */
	
};


#endif
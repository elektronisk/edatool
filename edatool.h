/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef EDATOOL_H
#define EDATOOL_H

#include <QMainWindow>
#include "board.h"
#include "tool.h"
#include "boardview.h"

class EditorArea;
class QGraphicsScene;
class QTreeWidgetItem;
class EDATool : public QMainWindow {
	Q_OBJECT
public:
	EDATool();
	friend class Tool;
	friend class BoardView;
	//static QColor layerToColor(int layer);
	//static Qt::BrushStyle layerToBrushStyle(int layer);
	static void layerToPenBrush(int layer, QPen &pen, QBrush &brush);
	QHash<QString, QGraphicsItemGroup*> *cache;
public slots:
	void itemClicked(QTreeWidgetItem* ,QTreeWidgetItem * previous);
private:
	QActionGroup *toolActionGroup;
	QToolBar *toolBar;
	QGraphicsScene *boardScene;
	BoardView *boardView;
	QMenu *fileMenu, *editMenu, *placeMenu;
};

#endif

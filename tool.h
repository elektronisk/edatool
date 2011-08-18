#ifndef TOOL_H
#define TOOL_H

#include <QObject>
class QAction;
class QMainWindow;
class QMenu;
class EDATool;


class Tool : public QObject {
	Q_OBJECT
public:
	Tool(EDATool *mainWindow);
	~Tool();
	virtual void install() = 0; /* Implemented by tool itself */
	virtual void uninstall() = 0;
	
	QMenu *getFileMenu();
	QMenu *getEditMenu();
protected:
	EDATool *mainWindow;
	QAction *action; /* pointer to created action, that triggers the tool */
	/* other state information for the tool */
	
};


#endif
#ifndef IHHCOMMANDMANAGER_H
#define IHHCOMMANDMANAGER_H

#include <QObject>

class IHHCommand;
class IHHCommandManager {
public:
    virtual ~IHHCommandManager(){}

	// ����ֵ��undo����ջsize
    virtual int undoCommand() = 0;

	// ����ֵ��redo����ջsize
	virtual int redoCommand() = 0;

	//
	virtual void resetCommand() = 0;
    
	//
	virtual void addCommand( IHHCommand *cmd ) = 0;
};
Q_DECLARE_INTERFACE( IHHCommandManager, "com.hht.qtWhiteBoard.IHHCommandManager/1.0" )
Q_DECLARE_METATYPE( IHHCommandManager* )

#endif // IHHCOMMANDMANAGER_H

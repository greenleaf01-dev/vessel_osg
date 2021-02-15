#ifndef IHHCOMMAND_H
#define IHHCOMMAND_H

#include <QObject>

class IHHCommand {
public:
    virtual ~IHHCommand(){}
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void remove() = 0;
};

Q_DECLARE_INTERFACE( IHHCommand, "com.hht.qtWhiteBoard.IHHCommand/1.0" )
Q_DECLARE_METATYPE( IHHCommand* )

#endif // IHHCOMMAND_H

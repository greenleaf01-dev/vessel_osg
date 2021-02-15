#ifndef HHCOMMAND_H
#define HHCOMMAND_H

#include "lib_global.h"
#include "ihhcommand.h"
#include <QVariantMap>
#include <QVector>

class HHPresentation;
class HHSlide;

class HHCommand : public IHHCommand
{
    Q_INTERFACES( IHHCommand )
public:
    HHCommand();
    virtual ~HHCommand();

public:
    virtual void execute();
    virtual void undo();
    virtual void redo();
    virtual void remove();
    virtual bool isDirtyPresentation();
};

#endif // HHCOMMAND_H

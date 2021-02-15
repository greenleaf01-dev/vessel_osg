#ifndef IHHFRAMESUBJECTCONTROLLER_H
#define IHHFRAMESUBJECTCONTROLLER_H

#include <QObject>

class IHHFrameSubjectController {
public:
        ~IHHFrameSubjectController() {}
    virtual QObject *getObject() = 0;
    virtual void    subjectModeSwitched(QString itemid) = 0;
};
Q_DECLARE_INTERFACE( IHHFrameSubjectController, "com.hht.qtWhiteBoard.IHHFrameSubjectController/1.0" )
Q_DECLARE_METATYPE( IHHFrameSubjectController* )
#endif // IHHFRAMESUBJECTCONTROLLER_H

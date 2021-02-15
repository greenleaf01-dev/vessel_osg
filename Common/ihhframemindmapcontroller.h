#pragma once

#include <QObject>

class IHHCanvas;

class IHHFrameMindMapController{
public:
    virtual ~IHHFrameMindMapController(){}

    virtual QObject *getObject() = 0;
    virtual void switchIHHCanvas(IHHCanvas *pIHHCanvas) = 0;

    virtual void createMindMap(const QString &sType) = 0;
    virtual void setMindMapModuleData(const QJsonObject &info) = 0;
};

Q_DECLARE_INTERFACE( IHHFrameMindMapController,
                     "com.hht.qtWhiteBoard.IHHFrameMindMapController/1.0" )
Q_DECLARE_METATYPE( IHHFrameMindMapController* )

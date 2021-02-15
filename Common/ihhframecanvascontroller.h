#pragma once

#include <QObject>

// 界面Canvas控制
class IHHSlide;
class IHHCanvas;

class IHHFrameCanvasController{
public:
    ~ IHHFrameCanvasController() {}
    virtual QObject *getObject() = 0;

    virtual void setCurrentIHHCanvas(IHHCanvas *pIHHCanvas) = 0;

    virtual void showNext() = 0;
    virtual void showForward() = 0;
    // Note: -1 -----最后一页
    virtual void showSlide(int nIndex) = 0;

    virtual void showSlide(IHHSlide *pSlide) = 0;

    // 获取当前页码信息
    virtual QString getPageInfo() = 0;

    // 获取当前页索引
    virtual int getActiveSlideIndex() = 0;

    // 切换画布到漫游模式
    virtual int switchCanvasRoamModule() = 0;
    // 切换画布到选择模式
    virtual int switchCanvasSelectModule(bool bIsHolderModule = false) = 0;

};
Q_DECLARE_INTERFACE( IHHFrameCanvasController, "com.hht.qtWhiteBoard.IHHFrameCanvasController/1.0" )
Q_DECLARE_METATYPE( IHHFrameCanvasController* )

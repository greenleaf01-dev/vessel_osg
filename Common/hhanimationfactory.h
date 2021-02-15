#ifndef HHANIMATION_H
#define HHANIMATION_H

#include "lib_animation.h"

class IHHItemAnimationController;
class IHHItemAnimationManager;
class IHHItemAnimationsSlideManager;
class IHHItemAnimationCanvasManager;
class IHHSlide;
class IHHScenario;

class HHANIMATIONSHARED_EXPORT HHAnimationFactory
{
public:
    // UI通过Controller控制Item特效.
    static IHHItemAnimationController *getIHHItemAnimationController(IHHScenario *&pCurScenario);

    // 页面中特效顺序管理器.
//    static IHHItemAnimationsSlideManager *getIHHItemAnimationsSlideManager(IHHSlide* slide);

    // canvas 中处理消息及绘制.
    static IHHItemAnimationCanvasManager *getIHHItemAnimationCanvasManager();
};

#endif // HHANIMATION_H

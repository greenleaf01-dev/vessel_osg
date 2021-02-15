#ifndef HHUIELEMENTSFACTORY_H
#define HHUIELEMENTSFACTORY_H

#include <QObject>

#include "uielement_global.h"

class IHHToolBar;
class IHHSwitchToolBar;
class IHHCustomMenu;
class IHHRubberBox;
class IHHSimplePenBox;
class IHHToolButton;
class IHHImageViewer;
class IHHThumbnailView;
class IHHActivityUI;

class UIELEMENTSHARED_EXPORT HHUIElementsFactory : public QObject
{
    Q_OBJECT
public:

    static IHHToolBar *createToolBar(QWidget *parent = nullptr);
    static IHHSwitchToolBar *createSwitchToolBar(QWidget *parent = nullptr);

    static IHHCustomMenu * createCustomMenu(QWidget *parent = nullptr);

    static IHHSimplePenBox *createSimplePenBox(QWidget *parent = nullptr);
    static IHHRubberBox *  createRubberBox(QWidget *parent = nullptr);
    static IHHToolButton *  createToolButton(QWidget *parent = nullptr);
    static IHHImageViewer * createImageViewer(QWidget *parent = nullptr);
    static IHHThumbnailView * createThumbnailView(QWidget *parent = nullptr);
    static IHHActivityUI *createActivityUI(QWidget *parent = nullptr);
    static IHHActivityUI *createActivityUserEditUI(QWidget *parent = nullptr);
};

#endif // HHUIELEMENTSFACTORY_H

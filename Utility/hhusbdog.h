#ifndef HHUSBDOG_H
#define HHUSBDOG_H

#include <QObject>
#include <QLibrary>

typedef bool (*usbDogCheck)();

class HHUsbDog : public QObject
{
    Q_OBJECT
public:
    explicit HHUsbDog(QObject *parent = 0);
    ~HHUsbDog();
    bool checkUsbDog();

private:
    QLibrary        *m_lib;
    usbDogCheck     m_funUsbDogCheck;
};

#endif // HHUSBDOG_H

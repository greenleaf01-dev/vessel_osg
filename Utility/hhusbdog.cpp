#include "hhusbdog.h"
#include <QDebug>

HHUsbDog::HHUsbDog(QObject *parent) : QObject(parent)
{
    m_funUsbDogCheck = NULL;
#ifdef WIN32
    m_lib = new QLibrary("DeviceCheck");
    if(m_lib->load())
    {
        m_funUsbDogCheck = (usbDogCheck)m_lib->resolve("UsbDogCheck");
    }
#else
    m_lib = NULL;
#endif

}

HHUsbDog::~HHUsbDog()
{
    if(NULL != m_lib)
    {
        if(m_lib->isLoaded())
            m_lib->unload();

        delete m_lib;
        m_lib = NULL;
    }
}

bool HHUsbDog::checkUsbDog()
{
#ifdef WIN32
    if(NULL == m_lib || !m_lib->isLoaded())
        return false;

    if(NULL == m_funUsbDogCheck)
        return false;

    return m_funUsbDogCheck();
#else
    return false;
#endif
}


#ifndef HHGLOBALDEFINE_H
#define HHGLOBALDEFINE_H

#include <QString>
#include <QVector>
#include <QVariant>
namespace HHGlobalDefine {
    enum PresentationType {
        HHT =  0x0,
        HHTX = 0x1
    };


    enum AttachFileType { filelibrary, attachments };
}

struct  HHPropertyRange {
    QString lable;
    QVariant value;
    QString id;
};

// text: QObject::tr(m_strTooltip)
struct  HHEditProperty {
    QString                         property;
    QString                         propertyType;
    QString                         m_strTooltip;
    QString                         text;
    QString                         id;
    int                             m_State;        
    bool                            m_HideMenu;
    QVector< HHPropertyRange >  m_pRange;
};


enum HHEidtPropertyState {
    COMBOBOX = 0,
    MENU
};

#define NULL 0

#endif

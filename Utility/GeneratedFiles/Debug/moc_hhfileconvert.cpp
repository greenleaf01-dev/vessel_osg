/****************************************************************************
** Meta object code from reading C++ file 'hhfileconvert.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Common/hhfileconvert.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hhfileconvert.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HHFileConvert_t {
    QByteArrayData data[7];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HHFileConvert_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HHFileConvert_t qt_meta_stringdata_HHFileConvert = {
    {
QT_MOC_LITERAL(0, 0, 13), // "HHFileConvert"
QT_MOC_LITERAL(1, 14, 18), // "sigFinishedConvert"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "source"
QT_MOC_LITERAL(4, 41, 4), // "dest"
QT_MOC_LITERAL(5, 46, 11), // "sltFinished"
QT_MOC_LITERAL(6, 58, 8) // "exitCode"

    },
    "HHFileConvert\0sigFinishedConvert\0\0"
    "source\0dest\0sltFinished\0exitCode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HHFileConvert[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void HHFileConvert::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HHFileConvert *_t = static_cast<HHFileConvert *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigFinishedConvert((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sltFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HHFileConvert::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HHFileConvert::sigFinishedConvert)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject HHFileConvert::staticMetaObject = {
    { &QProcess::staticMetaObject, qt_meta_stringdata_HHFileConvert.data,
      qt_meta_data_HHFileConvert,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HHFileConvert::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HHFileConvert::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HHFileConvert.stringdata0))
        return static_cast<void*>(const_cast< HHFileConvert*>(this));
    return QProcess::qt_metacast(_clname);
}

int HHFileConvert::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProcess::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void HHFileConvert::sigFinishedConvert(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

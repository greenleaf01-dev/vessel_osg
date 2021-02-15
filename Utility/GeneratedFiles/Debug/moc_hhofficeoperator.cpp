/****************************************************************************
** Meta object code from reading C++ file 'hhofficeoperator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Common/hhofficeoperator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hhofficeoperator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OfficeThread_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OfficeThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OfficeThread_t qt_meta_stringdata_OfficeThread = {
    {
QT_MOC_LITERAL(0, 0, 12) // "OfficeThread"

    },
    "OfficeThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OfficeThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void OfficeThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject OfficeThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_OfficeThread.data,
      qt_meta_data_OfficeThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OfficeThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OfficeThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OfficeThread.stringdata0))
        return static_cast<void*>(const_cast< OfficeThread*>(this));
    return QThread::qt_metacast(_clname);
}

int OfficeThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_HHOfficeOperator_t {
    QByteArrayData data[9];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HHOfficeOperator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HHOfficeOperator_t qt_meta_stringdata_HHOfficeOperator = {
    {
QT_MOC_LITERAL(0, 0, 16), // "HHOfficeOperator"
QT_MOC_LITERAL(1, 17, 13), // "sigHaveOffice"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "officeType"
QT_MOC_LITERAL(4, 43, 23), // "sigPPTPlayingSlideIndex"
QT_MOC_LITERAL(5, 67, 5), // "index"
QT_MOC_LITERAL(6, 73, 20), // "sigRefreshPPTPlaying"
QT_MOC_LITERAL(7, 94, 15), // "sltDetectOffice"
QT_MOC_LITERAL(8, 110, 20) // "sltRefreshPPTPlaying"

    },
    "HHOfficeOperator\0sigHaveOffice\0\0"
    "officeType\0sigPPTPlayingSlideIndex\0"
    "index\0sigRefreshPPTPlaying\0sltDetectOffice\0"
    "sltRefreshPPTPlaying"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HHOfficeOperator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   46,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HHOfficeOperator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HHOfficeOperator *_t = static_cast<HHOfficeOperator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigHaveOffice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigPPTPlayingSlideIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sigRefreshPPTPlaying(); break;
        case 3: _t->sltDetectOffice(); break;
        case 4: _t->sltRefreshPPTPlaying(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HHOfficeOperator::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HHOfficeOperator::sigHaveOffice)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (HHOfficeOperator::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HHOfficeOperator::sigPPTPlayingSlideIndex)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (HHOfficeOperator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HHOfficeOperator::sigRefreshPPTPlaying)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject HHOfficeOperator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HHOfficeOperator.data,
      qt_meta_data_HHOfficeOperator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HHOfficeOperator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HHOfficeOperator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HHOfficeOperator.stringdata0))
        return static_cast<void*>(const_cast< HHOfficeOperator*>(this));
    return QObject::qt_metacast(_clname);
}

int HHOfficeOperator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void HHOfficeOperator::sigHaveOffice(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HHOfficeOperator::sigPPTPlayingSlideIndex(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HHOfficeOperator::sigRefreshPPTPlaying()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

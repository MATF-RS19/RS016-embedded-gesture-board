/****************************************************************************
** Meta object code from reading C++ file 'tetrisigra.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tetris2/tetrisigra.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tetrisigra.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tetrisigra_t {
    QByteArrayData data[10];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tetrisigra_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tetrisigra_t qt_meta_stringdata_tetrisigra = {
    {
QT_MOC_LITERAL(0, 0, 10), // "tetrisigra"
QT_MOC_LITERAL(1, 11, 12), // "scoreChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "score"
QT_MOC_LITERAL(4, 31, 12), // "levelChanged"
QT_MOC_LITERAL(5, 44, 5), // "level"
QT_MOC_LITERAL(6, 50, 19), // "linesRemovedChanged"
QT_MOC_LITERAL(7, 70, 8), // "numLines"
QT_MOC_LITERAL(8, 79, 5), // "start"
QT_MOC_LITERAL(9, 85, 5) // "pause"

    },
    "tetrisigra\0scoreChanged\0\0score\0"
    "levelChanged\0level\0linesRemovedChanged\0"
    "numLines\0start\0pause"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tetrisigra[] = {

 // content:
       8,       // revision
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
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   48,    2, 0x0a /* Public */,
       9,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tetrisigra::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tetrisigra *_t = static_cast<tetrisigra *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scoreChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->levelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->linesRemovedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->start(); break;
        case 4: _t->pause(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tetrisigra::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tetrisigra::scoreChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tetrisigra::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tetrisigra::levelChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tetrisigra::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tetrisigra::linesRemovedChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tetrisigra::staticMetaObject = { {
    &QFrame::staticMetaObject,
    qt_meta_stringdata_tetrisigra.data,
    qt_meta_data_tetrisigra,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tetrisigra::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tetrisigra::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tetrisigra.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int tetrisigra::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
void tetrisigra::scoreChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tetrisigra::levelChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void tetrisigra::linesRemovedChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

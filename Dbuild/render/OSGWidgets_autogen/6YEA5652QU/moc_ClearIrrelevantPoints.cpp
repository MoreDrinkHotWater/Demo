/****************************************************************************
** Meta object code from reading C++ file 'ClearIrrelevantPoints.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../render/include/ClearIrrelevantPoints.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClearIrrelevantPoints.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClearIrrelevantPoints_t {
    QByteArrayData data[7];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClearIrrelevantPoints_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClearIrrelevantPoints_t qt_meta_stringdata_ClearIrrelevantPoints = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ClearIrrelevantPoints"
QT_MOC_LITERAL(1, 22, 25), // "clearIrrelevantPointsSlot"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 26), // "osg::ref_ptr<osg::Switch>&"
QT_MOC_LITERAL(4, 76, 8), // "rootnode"
QT_MOC_LITERAL(5, 85, 30), // "osg::ref_ptr<osgViewer::View>&"
QT_MOC_LITERAL(6, 116, 8) // "mainview"

    },
    "ClearIrrelevantPoints\0clearIrrelevantPointsSlot\0"
    "\0osg::ref_ptr<osg::Switch>&\0rootnode\0"
    "osg::ref_ptr<osgViewer::View>&\0mainview"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClearIrrelevantPoints[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void ClearIrrelevantPoints::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClearIrrelevantPoints *_t = static_cast<ClearIrrelevantPoints *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearIrrelevantPointsSlot((*reinterpret_cast< osg::ref_ptr<osg::Switch>(*)>(_a[1])),(*reinterpret_cast< osg::ref_ptr<osgViewer::View>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClearIrrelevantPoints::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ClearIrrelevantPoints.data,
    qt_meta_data_ClearIrrelevantPoints,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClearIrrelevantPoints::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClearIrrelevantPoints::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClearIrrelevantPoints.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClearIrrelevantPoints::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

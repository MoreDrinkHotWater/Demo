/****************************************************************************
** Meta object code from reading C++ file 'GenerateOctreeWorker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../PointCloudApplication/include/GenerateOctreeWorker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerateOctreeWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GenerateOctreeWorker_t {
    QByteArrayData data[6];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GenerateOctreeWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GenerateOctreeWorker_t qt_meta_stringdata_GenerateOctreeWorker = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GenerateOctreeWorker"
QT_MOC_LITERAL(1, 21, 28), // "doneGenerateOctreeDataSignal"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 18), // "generateOctreeData"
QT_MOC_LITERAL(4, 70, 8), // "filePath"
QT_MOC_LITERAL(5, 79, 6) // "hasRGB"

    },
    "GenerateOctreeWorker\0doneGenerateOctreeDataSignal\0"
    "\0generateOctreeData\0filePath\0hasRGB"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GenerateOctreeWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    4,    5,

       0        // eod
};

void GenerateOctreeWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GenerateOctreeWorker *_t = static_cast<GenerateOctreeWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doneGenerateOctreeDataSignal(); break;
        case 1: _t->generateOctreeData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GenerateOctreeWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GenerateOctreeWorker::doneGenerateOctreeDataSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GenerateOctreeWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_GenerateOctreeWorker.data,
    qt_meta_data_GenerateOctreeWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GenerateOctreeWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GenerateOctreeWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GenerateOctreeWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GenerateOctreeWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void GenerateOctreeWorker::doneGenerateOctreeDataSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

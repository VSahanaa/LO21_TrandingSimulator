/****************************************************************************
** Meta object code from reading C++ file 'evolutionviewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TradingSimulator/evolutionviewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'evolutionviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Bougie_t {
    QByteArrayData data[6];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bougie_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bougie_t qt_meta_stringdata_Bougie = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Bougie"
QT_MOC_LITERAL(1, 7, 11), // "clickBougie"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "Bougie*"
QT_MOC_LITERAL(4, 28, 5), // "cours"
QT_MOC_LITERAL(5, 34, 14) // "viewCoursOHLCV"

    },
    "Bougie\0clickBougie\0\0Bougie*\0cours\0"
    "viewCoursOHLCV"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bougie[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Bougie::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Bougie *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickBougie((*reinterpret_cast< Bougie*(*)>(_a[1]))); break;
        case 1: _t->viewCoursOHLCV(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Bougie* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Bougie::*)(Bougie * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Bougie::clickBougie)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Bougie::staticMetaObject = { {
    &QCandlestickSet::staticMetaObject,
    qt_meta_stringdata_Bougie.data,
    qt_meta_data_Bougie,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Bougie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bougie::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Bougie.stringdata0))
        return static_cast<void*>(this);
    return QCandlestickSet::qt_metacast(_clname);
}

int Bougie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCandlestickSet::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Bougie::clickBougie(Bougie * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_EvolutionViewer_t {
    QByteArrayData data[6];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EvolutionViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EvolutionViewer_t qt_meta_stringdata_EvolutionViewer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "EvolutionViewer"
QT_MOC_LITERAL(1, 16, 14), // "showCoursOHLCV"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "Bougie*"
QT_MOC_LITERAL(4, 40, 6), // "bougie"
QT_MOC_LITERAL(5, 47, 14) // "saveCoursOHLCV"

    },
    "EvolutionViewer\0showCoursOHLCV\0\0Bougie*\0"
    "bougie\0saveCoursOHLCV"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EvolutionViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       5,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void EvolutionViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EvolutionViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showCoursOHLCV((*reinterpret_cast< Bougie*(*)>(_a[1]))); break;
        case 1: _t->saveCoursOHLCV(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Bougie* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EvolutionViewer::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_EvolutionViewer.data,
    qt_meta_data_EvolutionViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EvolutionViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EvolutionViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EvolutionViewer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EvolutionViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

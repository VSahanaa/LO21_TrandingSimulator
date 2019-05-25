/****************************************************************************
** Meta object code from reading C++ file 'welcome.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TradingSimulator/welcome.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'welcome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Welcome_t {
    QByteArrayData data[14];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Welcome_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Welcome_t qt_meta_stringdata_Welcome = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Welcome"
QT_MOC_LITERAL(1, 8, 19), // "on_Continue_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "on_About_clicked"
QT_MOC_LITERAL(4, 46, 15), // "on_Quit_clicked"
QT_MOC_LITERAL(5, 62, 21), // "on_Simulation_clicked"
QT_MOC_LITERAL(6, 84, 22), // "on_Candlestick_clicked"
QT_MOC_LITERAL(7, 107, 17), // "on_Manuel_clicked"
QT_MOC_LITERAL(8, 125, 15), // "on_Step_clicked"
QT_MOC_LITERAL(9, 141, 15), // "on_Auto_clicked"
QT_MOC_LITERAL(10, 157, 15), // "on_Back_clicked"
QT_MOC_LITERAL(11, 173, 19), // "on_filePath_clicked"
QT_MOC_LITERAL(12, 193, 26), // "on_dispaly_dialog_accepted"
QT_MOC_LITERAL(13, 220, 26) // "on_dispaly_dialog_rejected"

    },
    "Welcome\0on_Continue_clicked\0\0"
    "on_About_clicked\0on_Quit_clicked\0"
    "on_Simulation_clicked\0on_Candlestick_clicked\0"
    "on_Manuel_clicked\0on_Step_clicked\0"
    "on_Auto_clicked\0on_Back_clicked\0"
    "on_filePath_clicked\0on_dispaly_dialog_accepted\0"
    "on_dispaly_dialog_rejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Welcome[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Welcome::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Welcome *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Continue_clicked(); break;
        case 1: _t->on_About_clicked(); break;
        case 2: _t->on_Quit_clicked(); break;
        case 3: _t->on_Simulation_clicked(); break;
        case 4: _t->on_Candlestick_clicked(); break;
        case 5: _t->on_Manuel_clicked(); break;
        case 6: _t->on_Step_clicked(); break;
        case 7: _t->on_Auto_clicked(); break;
        case 8: _t->on_Back_clicked(); break;
        case 9: _t->on_filePath_clicked(); break;
        case 10: _t->on_dispaly_dialog_accepted(); break;
        case 11: _t->on_dispaly_dialog_rejected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Welcome::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Welcome.data,
    qt_meta_data_Welcome,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Welcome::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Welcome::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Welcome.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Welcome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
struct qt_meta_stringdata_Info_t {
    QByteArrayData data[1];
    char stringdata0[5];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Info_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Info_t qt_meta_stringdata_Info = {
    {
QT_MOC_LITERAL(0, 0, 4) // "Info"

    },
    "Info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Info[] = {

 // content:
       8,       // revision
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

void Info::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Info::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Info.data,
    qt_meta_data_Info,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Info::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Info::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Info.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Info::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

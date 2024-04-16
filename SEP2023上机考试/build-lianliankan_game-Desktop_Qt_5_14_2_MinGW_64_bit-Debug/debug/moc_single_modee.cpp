/****************************************************************************
** Meta object code from reading C++ file 'single_modee.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../LAB/lab_linkgame/lianliankan/single_modee.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'single_modee.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_single_modee_t {
    QByteArrayData data[16];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_single_modee_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_single_modee_t qt_meta_stringdata_single_modee = {
    {
QT_MOC_LITERAL(0, 0, 12), // "single_modee"
QT_MOC_LITERAL(1, 13, 7), // "endGame"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "showthing"
QT_MOC_LITERAL(4, 32, 12), // "timedecrease"
QT_MOC_LITERAL(5, 45, 4), // "hint"
QT_MOC_LITERAL(6, 50, 6), // "dehint"
QT_MOC_LITERAL(7, 57, 4), // "plus"
QT_MOC_LITERAL(8, 62, 6), // "tool_s"
QT_MOC_LITERAL(9, 69, 4), // "tool"
QT_MOC_LITERAL(10, 74, 7), // "shuffle"
QT_MOC_LITERAL(11, 82, 7), // "deflash"
QT_MOC_LITERAL(12, 90, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(13, 114, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(14, 138, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(15, 162, 21) // "on_pushButton_clicked"

    },
    "single_modee\0endGame\0\0showthing\0"
    "timedecrease\0hint\0dehint\0plus\0tool_s\0"
    "tool\0shuffle\0deflash\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_single_modee[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    1,   85,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void single_modee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<single_modee *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->endGame(); break;
        case 1: _t->showthing(); break;
        case 2: _t->timedecrease(); break;
        case 3: _t->hint(); break;
        case 4: _t->dehint(); break;
        case 5: _t->plus(); break;
        case 6: _t->tool_s((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->shuffle(); break;
        case 8: _t->deflash(); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        case 10: _t->on_pushButton_3_clicked(); break;
        case 11: _t->on_pushButton_4_clicked(); break;
        case 12: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject single_modee::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_single_modee.data,
    qt_meta_data_single_modee,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *single_modee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *single_modee::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_single_modee.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int single_modee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

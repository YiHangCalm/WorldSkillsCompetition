/****************************************************************************
** Meta object code from reading C++ file 'qrcode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Ltem_Sorting/qrcode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qrcode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QRCode_t {
    QByteArrayData data[11];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QRCode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QRCode_t qt_meta_stringdata_QRCode = {
    {
QT_MOC_LITERAL(0, 0, 6), // "QRCode"
QT_MOC_LITERAL(1, 7, 19), // "on_exButton_Release"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "on_exButton_Pressed"
QT_MOC_LITERAL(4, 48, 21), // "on_slowButton_pressed"
QT_MOC_LITERAL(5, 70, 22), // "on_slowButton_released"
QT_MOC_LITERAL(6, 93, 21), // "on_fastButton_pressed"
QT_MOC_LITERAL(7, 115, 22), // "on_fastButton_released"
QT_MOC_LITERAL(8, 138, 18), // "on_yunting_clicked"
QT_MOC_LITERAL(9, 157, 17), // "on_bishui_clicked"
QT_MOC_LITERAL(10, 175, 17) // "on_baiyun_clicked"

    },
    "QRCode\0on_exButton_Release\0\0"
    "on_exButton_Pressed\0on_slowButton_pressed\0"
    "on_slowButton_released\0on_fastButton_pressed\0"
    "on_fastButton_released\0on_yunting_clicked\0"
    "on_bishui_clicked\0on_baiyun_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QRCode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

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

       0        // eod
};

void QRCode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QRCode *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_exButton_Release(); break;
        case 1: _t->on_exButton_Pressed(); break;
        case 2: _t->on_slowButton_pressed(); break;
        case 3: _t->on_slowButton_released(); break;
        case 4: _t->on_fastButton_pressed(); break;
        case 5: _t->on_fastButton_released(); break;
        case 6: _t->on_yunting_clicked(); break;
        case 7: _t->on_bishui_clicked(); break;
        case 8: _t->on_baiyun_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject QRCode::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QRCode.data,
    qt_meta_data_QRCode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QRCode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QRCode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QRCode.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Mode"))
        return static_cast< Mode*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QRCode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'MyGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGLWidget_t {
    QByteArrayData data[18];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGLWidget_t qt_meta_stringdata_MyGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MyGLWidget"
QT_MOC_LITERAL(1, 11, 9), // "signal2x1"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "signal2x2"
QT_MOC_LITERAL(4, 32, 9), // "signal2x4"
QT_MOC_LITERAL(5, 42, 9), // "signalRed"
QT_MOC_LITERAL(6, 52, 3), // "val"
QT_MOC_LITERAL(7, 56, 11), // "signalGreen"
QT_MOC_LITERAL(8, 68, 10), // "signalBlue"
QT_MOC_LITERAL(9, 79, 8), // "model2x1"
QT_MOC_LITERAL(10, 88, 8), // "model2x2"
QT_MOC_LITERAL(11, 97, 8), // "model2x4"
QT_MOC_LITERAL(12, 106, 7), // "slotRed"
QT_MOC_LITERAL(13, 114, 1), // "r"
QT_MOC_LITERAL(14, 116, 9), // "slotGreen"
QT_MOC_LITERAL(15, 126, 1), // "g"
QT_MOC_LITERAL(16, 128, 8), // "slotBlue"
QT_MOC_LITERAL(17, 137, 1) // "b"

    },
    "MyGLWidget\0signal2x1\0\0signal2x2\0"
    "signal2x4\0signalRed\0val\0signalGreen\0"
    "signalBlue\0model2x1\0model2x2\0model2x4\0"
    "slotRed\0r\0slotGreen\0g\0slotBlue\0b"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       7,    1,   80,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    1,   89,    2, 0x0a /* Public */,
      14,    1,   92,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   17,

       0        // eod
};

void MyGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signal2x1(); break;
        case 1: _t->signal2x2(); break;
        case 2: _t->signal2x4(); break;
        case 3: _t->signalRed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->signalGreen((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->signalBlue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->model2x1(); break;
        case 7: _t->model2x2(); break;
        case 8: _t->model2x4(); break;
        case 9: _t->slotRed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->slotGreen((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->slotBlue((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::signal2x1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::signal2x2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::signal2x4)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::signalRed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::signalGreen)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::signalBlue)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<ExamGLWidget::staticMetaObject>(),
    qt_meta_stringdata_MyGLWidget.data,
    qt_meta_data_MyGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGLWidget.stringdata0))
        return static_cast<void*>(this);
    return ExamGLWidget::qt_metacast(_clname);
}

int MyGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ExamGLWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MyGLWidget::signal2x1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyGLWidget::signal2x2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyGLWidget::signal2x4()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyGLWidget::signalRed(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyGLWidget::signalGreen(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyGLWidget::signalBlue(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

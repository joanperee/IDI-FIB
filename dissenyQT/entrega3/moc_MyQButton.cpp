/****************************************************************************
** Meta object code from reading C++ file 'MyQButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyQButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyQButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyQButton_t {
    QByteArrayData data[15];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQButton_t qt_meta_stringdata_MyQButton = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MyQButton"
QT_MOC_LITERAL(1, 10, 11), // "enviaColor1"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "enviaColor2"
QT_MOC_LITERAL(4, 35, 11), // "enviaColor3"
QT_MOC_LITERAL(5, 47, 19), // "actualitzaComptador"
QT_MOC_LITERAL(6, 67, 9), // "num_trios"
QT_MOC_LITERAL(7, 77, 13), // "reiniciaColor"
QT_MOC_LITERAL(8, 91, 18), // "reiniciarComptador"
QT_MOC_LITERAL(9, 110, 18), // "converteixNumColor"
QT_MOC_LITERAL(10, 129, 5), // "color"
QT_MOC_LITERAL(11, 135, 5), // "jugar"
QT_MOC_LITERAL(12, 141, 10), // "posaColor1"
QT_MOC_LITERAL(13, 152, 10), // "posaColor2"
QT_MOC_LITERAL(14, 163, 10) // "posaColor3"

    },
    "MyQButton\0enviaColor1\0\0enviaColor2\0"
    "enviaColor3\0actualitzaComptador\0"
    "num_trios\0reiniciaColor\0reiniciarComptador\0"
    "converteixNumColor\0color\0jugar\0"
    "posaColor1\0posaColor2\0posaColor3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQButton[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    1,   72,    2, 0x06 /* Public */,
       4,    1,   75,    2, 0x06 /* Public */,
       5,    1,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   81,    2, 0x0a /* Public */,
       8,    0,   82,    2, 0x0a /* Public */,
       9,    1,   83,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x0a /* Public */,
      12,    0,   87,    2, 0x0a /* Public */,
      13,    0,   88,    2, 0x0a /* Public */,
      14,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyQButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyQButton *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->enviaColor1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->enviaColor2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->enviaColor3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->actualitzaComptador((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->reiniciaColor(); break;
        case 5: _t->reiniciarComptador(); break;
        case 6: { QString _r = _t->converteixNumColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->jugar(); break;
        case 8: _t->posaColor1(); break;
        case 9: _t->posaColor2(); break;
        case 10: _t->posaColor3(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::enviaColor1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::enviaColor2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::enviaColor3)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::actualitzaComptador)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyQButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_meta_stringdata_MyQButton.data,
    qt_meta_data_MyQButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyQButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyQButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int MyQButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MyQButton::enviaColor1(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyQButton::enviaColor2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyQButton::enviaColor3(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyQButton::actualitzaComptador(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'addtaskdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "addtaskdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addtaskdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddTaskDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      37,   14,   14,   14, 0x08,
      56,   14,   14,   14, 0x08,
      75,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddTaskDialog[] = {
    "AddTaskDialog\0\0taskBoxIndexChanged()\0"
    "fullScoreChanged()\0timeLimitChanged()\0"
    "memoryLimitChanged()\0"
};

void AddTaskDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddTaskDialog *_t = static_cast<AddTaskDialog *>(_o);
        switch (_id) {
        case 0: _t->taskBoxIndexChanged(); break;
        case 1: _t->fullScoreChanged(); break;
        case 2: _t->timeLimitChanged(); break;
        case 3: _t->memoryLimitChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AddTaskDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddTaskDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddTaskDialog,
      qt_meta_data_AddTaskDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddTaskDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddTaskDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddTaskDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddTaskDialog))
        return static_cast<void*>(const_cast< AddTaskDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddTaskDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

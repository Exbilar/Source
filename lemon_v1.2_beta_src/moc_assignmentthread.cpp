/****************************************************************************
** Meta object code from reading C++ file 'assignmentthread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "assignmentthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'assignmentthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AssignmentThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,
      60,   58,   17,   17, 0x05,
      82,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     102,   17,   17,   17, 0x08,
     119,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AssignmentThread[] = {
    "AssignmentThread\0\0,,,\0"
    "singleCaseFinished(int,int,int,int)\0"
    ",\0compileError(int,int)\0stopJudgingSignal()\0"
    "threadFinished()\0stopJudgingSlot()\0"
};

void AssignmentThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AssignmentThread *_t = static_cast<AssignmentThread *>(_o);
        switch (_id) {
        case 0: _t->singleCaseFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->compileError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->stopJudgingSignal(); break;
        case 3: _t->threadFinished(); break;
        case 4: _t->stopJudgingSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AssignmentThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AssignmentThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AssignmentThread,
      qt_meta_data_AssignmentThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AssignmentThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AssignmentThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AssignmentThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AssignmentThread))
        return static_cast<void*>(const_cast< AssignmentThread*>(this));
    return QThread::qt_metacast(_clname);
}

int AssignmentThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AssignmentThread::singleCaseFinished(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AssignmentThread::compileError(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AssignmentThread::stopJudgingSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

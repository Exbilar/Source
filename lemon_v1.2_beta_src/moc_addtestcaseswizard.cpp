/****************************************************************************
** Meta object code from reading C++ file 'addtestcaseswizard.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "addtestcaseswizard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addtestcaseswizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddTestCasesWizard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      46,   19,   19,   19, 0x08,
      72,   19,   19,   19, 0x08,
     100,   19,   19,   19, 0x08,
     134,   19,   19,   19, 0x08,
     169,   19,   19,   19, 0x08,
     183,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddTestCasesWizard[] = {
    "AddTestCasesWizard\0\0fullScoreChanged(QString)\0"
    "timeLimitChanged(QString)\0"
    "memoryLimitChanged(QString)\0"
    "inputFilesPatternChanged(QString)\0"
    "outputFilesPatternChanged(QString)\0"
    "addArgument()\0deleteArgument()\0"
};

void AddTestCasesWizard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddTestCasesWizard *_t = static_cast<AddTestCasesWizard *>(_o);
        switch (_id) {
        case 0: _t->fullScoreChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->timeLimitChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->memoryLimitChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->inputFilesPatternChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->outputFilesPatternChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->addArgument(); break;
        case 6: _t->deleteArgument(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddTestCasesWizard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddTestCasesWizard::staticMetaObject = {
    { &QWizard::staticMetaObject, qt_meta_stringdata_AddTestCasesWizard,
      qt_meta_data_AddTestCasesWizard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddTestCasesWizard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddTestCasesWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddTestCasesWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddTestCasesWizard))
        return static_cast<void*>(const_cast< AddTestCasesWizard*>(this));
    return QWizard::qt_metacast(_clname);
}

int AddTestCasesWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

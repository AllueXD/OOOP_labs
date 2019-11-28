/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Lab2_NotesApp/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_actNewNote_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 21), // "on_actNewType_clicked"
QT_MOC_LITERAL(4, 56, 20), // "on_actDelete_clicked"
QT_MOC_LITERAL(5, 77, 22), // "on_actEditText_clicked"
QT_MOC_LITERAL(6, 100, 22), // "on_actEditName_clicked"
QT_MOC_LITERAL(7, 123, 18), // "on_archive_clicked"
QT_MOC_LITERAL(8, 142, 17), // "on_addNew_clicked"
QT_MOC_LITERAL(9, 160, 24), // "on_treeNotes_itemClicked"
QT_MOC_LITERAL(10, 185, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(11, 202, 4), // "item"
QT_MOC_LITERAL(12, 207, 6), // "column"
QT_MOC_LITERAL(13, 214, 18), // "ProvideContextMenu"
QT_MOC_LITERAL(14, 233, 3), // "pos"
QT_MOC_LITERAL(15, 237, 22), // "on_saveChanges_clicked"
QT_MOC_LITERAL(16, 260, 8), // "saveNote"
QT_MOC_LITERAL(17, 269, 12), // "saveEditText"
QT_MOC_LITERAL(18, 282, 12), // "saveEditName"
QT_MOC_LITERAL(19, 295, 12) // "saveCategory"

    },
    "MainWindow\0on_actNewNote_clicked\0\0"
    "on_actNewType_clicked\0on_actDelete_clicked\0"
    "on_actEditText_clicked\0on_actEditName_clicked\0"
    "on_archive_clicked\0on_addNew_clicked\0"
    "on_treeNotes_itemClicked\0QTreeWidgetItem*\0"
    "item\0column\0ProvideContextMenu\0pos\0"
    "on_saveChanges_clicked\0saveNote\0"
    "saveEditText\0saveEditName\0saveCategory"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    2,   91,    2, 0x08 /* Private */,
      13,    1,   96,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,
      18,    0,  102,    2, 0x08 /* Private */,
      19,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::QPoint,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actNewNote_clicked(); break;
        case 1: _t->on_actNewType_clicked(); break;
        case 2: _t->on_actDelete_clicked(); break;
        case 3: _t->on_actEditText_clicked(); break;
        case 4: _t->on_actEditName_clicked(); break;
        case 5: _t->on_archive_clicked(); break;
        case 6: _t->on_addNew_clicked(); break;
        case 7: _t->on_treeNotes_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->ProvideContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 9: _t->on_saveChanges_clicked(); break;
        case 10: _t->saveNote(); break;
        case 11: _t->saveEditText(); break;
        case 12: _t->saveEditName(); break;
        case 13: _t->saveCategory(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

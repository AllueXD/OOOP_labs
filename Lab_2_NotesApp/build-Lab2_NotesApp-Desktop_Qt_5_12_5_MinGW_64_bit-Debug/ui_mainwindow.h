/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_note;
    QAction *actionAdd_folder;
    QAction *actionExit;
    QAction *actionShow_by_time;
    QAction *actionstudy;
    QAction *actionwork;
    QAction *actionadd_new_type;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeNotes;
    QPushButton *addNew;
    QPushButton *archive;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *noteName;
    QTextEdit *textNote;
    QPushButton *saveChanges;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSort;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(803, 594);
        actionAdd_note = new QAction(MainWindow);
        actionAdd_note->setObjectName(QString::fromUtf8("actionAdd_note"));
        actionAdd_folder = new QAction(MainWindow);
        actionAdd_folder->setObjectName(QString::fromUtf8("actionAdd_folder"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionShow_by_time = new QAction(MainWindow);
        actionShow_by_time->setObjectName(QString::fromUtf8("actionShow_by_time"));
        actionstudy = new QAction(MainWindow);
        actionstudy->setObjectName(QString::fromUtf8("actionstudy"));
        actionwork = new QAction(MainWindow);
        actionwork->setObjectName(QString::fromUtf8("actionwork"));
        actionadd_new_type = new QAction(MainWindow);
        actionadd_new_type->setObjectName(QString::fromUtf8("actionadd_new_type"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 258, 521));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeNotes = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Your notes:"));
        treeNotes->setHeaderItem(__qtreewidgetitem);
        new QTreeWidgetItem(treeNotes);
        treeNotes->setObjectName(QString::fromUtf8("treeNotes"));
        treeNotes->setColumnCount(1);

        verticalLayout->addWidget(treeNotes);

        addNew = new QPushButton(layoutWidget);
        addNew->setObjectName(QString::fromUtf8("addNew"));

        verticalLayout->addWidget(addNew);

        archive = new QPushButton(layoutWidget);
        archive->setObjectName(QString::fromUtf8("archive"));

        verticalLayout->addWidget(archive);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(280, 10, 511, 521));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        noteName = new QLineEdit(layoutWidget1);
        noteName->setObjectName(QString::fromUtf8("noteName"));
        noteName->setEnabled(false);

        verticalLayout_2->addWidget(noteName);

        textNote = new QTextEdit(layoutWidget1);
        textNote->setObjectName(QString::fromUtf8("textNote"));
        textNote->setEnabled(false);

        verticalLayout_2->addWidget(textNote);

        saveChanges = new QPushButton(centralwidget);
        saveChanges->setObjectName(QString::fromUtf8("saveChanges"));
        saveChanges->setGeometry(QRect(670, 500, 101, 21));
        saveChanges->setInputMethodHints(Qt::ImhHiddenText);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 803, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSort = new QMenu(menubar);
        menuSort->setObjectName(QString::fromUtf8("menuSort"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSort->menuAction());
        menuFile->addAction(actionExit);
        menuSort->addAction(actionShow_by_time);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAdd_note->setText(QApplication::translate("MainWindow", "Add note", nullptr));
        actionAdd_folder->setText(QApplication::translate("MainWindow", "Add folder", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionShow_by_time->setText(QApplication::translate("MainWindow", "Show by time", nullptr));
        actionstudy->setText(QApplication::translate("MainWindow", "study", nullptr));
        actionwork->setText(QApplication::translate("MainWindow", "work", nullptr));
        actionadd_new_type->setText(QApplication::translate("MainWindow", "add new type", nullptr));

        const bool __sortingEnabled = treeNotes->isSortingEnabled();
        treeNotes->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = treeNotes->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "All", nullptr));
        treeNotes->setSortingEnabled(__sortingEnabled);

        addNew->setText(QApplication::translate("MainWindow", "Add new type", nullptr));
        archive->setText(QApplication::translate("MainWindow", "Go to archive", nullptr));
        saveChanges->setText(QApplication::translate("MainWindow", "Save", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuSort->setTitle(QApplication::translate("MainWindow", "Sort", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

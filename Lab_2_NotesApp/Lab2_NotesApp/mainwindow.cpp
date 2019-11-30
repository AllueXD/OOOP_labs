#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contextMenu.h"
#include "additionalFunctions.h"
#include "loadFunctions.h"
#include "saveFunctions.h"
#include "menuBarFunctions.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QAction>
#include <QVector>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->saveChanges->hide();
    ui->treeNotes->itemAt(0,0)->setTextColor(0,"darkred");
    ui->treeNotes->setContextMenuPolicy(Qt::CustomContextMenu);

    QDir notesDir (QDir::current().absolutePath() + "/notes");
    if (!notesDir.exists()) {
        QDir().mkdir(QDir::current().absolutePath() + "/notes");
        QDir().mkdir(QDir::current().absolutePath() + "/notes"+"/All");
    } else {
        QDir AllDir (QDir::current().absolutePath() + "/notes"+"/All");
        if (!AllDir.exists()) {
            QDir().mkdir(QDir::current().absolutePath() + "/notes"+"/All");
        }
    }

    connect(ui->treeNotes,&QTreeWidget::customContextMenuRequested,this,&MainWindow::ProvideContextMenu);
    connect(ui->actionLoad_all, SIGNAL(triggered()), this, SLOT(on_actLoad_all_clicked()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(on_actExit_clicked()));
    connect(ui->actionShow_by_time, SIGNAL(triggered()), this, SLOT(on_actSort_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_archive_clicked()
{
    ui->treeNotes->clear();
    ui->noteName->clear();
    ui->textNote->clear();
    if (MainWindow::isArchiveMode) {
       loadAllFiles(QDir::current().absolutePath()+"/notes/", nullptr);
       ui->archive->setText("Show with archived");
       ui->addNew->setEnabled(true);
    } else {
       loadWithArchived(QDir::current().absolutePath()+"/notes/", nullptr, false);
       ui->archive->setText("Hide archived");
       ui->addNew->setEnabled(false);
    }
    MainWindow::isArchiveMode = !MainWindow::isArchiveMode;

}

void MainWindow::on_saveChanges_clicked()
{
    if (MainWindow::isCategory) {
        saveCategory();
    } else if (MainWindow::isNote) {
        saveNote();
    } else if (MainWindow::isEditText) {
        saveEditText();
    } else if (MainWindow::isEditName) {
        saveEditName();
    }

    ui->textNote->clear();
    ui->noteName->clear();
    ui->noteName->setEnabled(false);
    ui->textNote->setEnabled(false);
    ui->saveChanges->hide();
}

void MainWindow::on_addNew_clicked()
{
    ui->textNote->clear();
    ui->noteName->clear();
    ui->noteName->setEnabled(true);
    ui->textNote->setEnabled(false);
    ui->noteName->setReadOnly(false);
    ui->textNote->setReadOnly(false);
    MainWindow::isCategory = true;
    currItem(nullptr,false);
    ui->saveChanges->show();
}

void MainWindow::on_treeNotes_itemClicked(QTreeWidgetItem *item, int column)
{
    load_note(item, column);
}


#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additionalFunctions.h"

#include <QDebug>
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include <QString>
#include <QStringList>

void MainWindow::on_actNewNote_clicked() {
    ui->noteName->clear();
    ui->textNote->clear();
    ui->noteName->setEnabled(true);
    ui->textNote->setEnabled(true);
    ui->noteName->setReadOnly(false);
    ui->textNote->setReadOnly(false);
    MainWindow::isNote = true;
    ui->saveChanges->show();
}

void MainWindow::on_actNewType_clicked() {
    ui->noteName->clear();
    ui->textNote->clear();
    ui->noteName->setEnabled(true);
    ui->textNote->setEnabled(false);
    ui->noteName->setReadOnly(false);
    ui->textNote->setReadOnly(true);
    MainWindow::isCategory = true;
    ui->saveChanges->show();
}

void delete_item(QTreeWidgetItem* item) {
    if (!isFileNote(item)) {
        QDir dir(QDir::current().absolutePath()+"/notes/"+"All/"+item->text(0));
        dir.removeRecursively();
    } else {
        QFile::remove(QDir::current().absolutePath()+"/notes/"+"All/"+item->text(0)+".txt");
        QFile::remove(QDir::current().absolutePath()+"/notes/"+"All/"+item->text(0)+".archive");
    }
    delete item;
}

void MainWindow::on_actDelete_clicked() {
    QTreeWidgetItem *item = currItem(nullptr, true);

    ui->textNote->clear();
    ui->noteName->clear();

    if (item->parent() == nullptr && item->text(0)=="All") {
        for (int i = 0; i < item->childCount(); i++) {
            delete_item(item->child(0));
       }
        if (item->childCount()!=0) {delete_item(item->child(0));}

    } else {

        QString path = findPath(item);

        if (!isFileNote(item)) {
         QDir dir(path+item->text(0));
         dir.removeRecursively();
        } else {
            QFile::remove(path+item->text(0)+".txt");
            QFile::remove(path+item->text(0)+".archive");
        }

        delete item;
    }
}

void MainWindow::on_actEditText_clicked() {
    QTreeWidgetItem *item = currItem(nullptr, true);
    MainWindow::load_note(item,0);

    ui->textNote->setReadOnly(false);
    ui->textNote->setEnabled(true);
    MainWindow::isEditText = true;
    ui->saveChanges->show();
}

void MainWindow::on_actEditName_clicked() {
    QTreeWidgetItem *item = currItem(nullptr, true);
    MainWindow::load_note(item,0);

    ui->noteName->setReadOnly(false);
    ui->noteName->setEnabled(true);

    ui->textNote->setEnabled(false);

    MainWindow::isEditName = true;
    ui->saveChanges->show();

    ui->textNote->setEnabled(false);
}

void archiveSubFiles (QString path) {

    QDir dir = path;
    QStringList subdirs = dir.entryList();
    foreach (QString curr, subdirs) {
        QString nextPath = dir.absolutePath();
        QString currArchived = curr;
        currArchived.replace(".txt", ".archive");
        nextPath += "/"+curr;
        QFileInfo check_file(nextPath);

       if (check_file.exists() && curr!="." && curr!="..") {
           if (check_file.isFile()) {
            QFile::rename(nextPath, dir.absolutePath()+"/"+currArchived);
           } else {
               archiveSubFiles(nextPath);
           }
       }
    }
}

void MainWindow::on_actMove_clicked() {

    QTreeWidgetItem* item = currItem(nullptr, true);
    QString path = findPath(item);

    if (isFileNote(item)) {
        QFile::rename(path+item->text(0)+".txt", path+item->text(0)+".archive");
    } else {
        QFile ignoreNote (path+item->text(0)+"/.ignore");
        if (!ignoreNote.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::critical(0,"Critical", "Something wrong! Ignore file can't be created!");
        }
        archiveSubFiles(path+item->text(0));
    }

    delete item;
}

void restoreSubFiles (QString path) {
    QDir dir = path;
    QStringList subdirs = dir.entryList();
    foreach (QString curr, subdirs) {
        QString nextPath = dir.absolutePath();
        QString currArchived = curr;
        currArchived.replace(".archive", ".txt");
        nextPath += "/"+curr;
        QFileInfo check_file(nextPath);

       if (check_file.exists() && curr!="." && curr!="..") {
           if (check_file.isFile()) {
            QFile::rename(nextPath, dir.absolutePath()+"/"+currArchived);
           } else {
               restoreSubFiles(nextPath);
           }
       }
    }
}

void MainWindow::changeRestoredColors (QTreeWidgetItem* parent) {
    if (isFileNote(parent)) {
        parent->setTextColor(0,"black");
    } else {
        parent->setTextColor(0, "darkred");
        for (int i = 0; i < parent->childCount(); i++) {
            changeRestoredColors(parent->child(i));
        }
    }
}

void MainWindow::on_actRestore_clicked() {

    QTreeWidgetItem* item = currItem(nullptr, true);
    QString path = findPath(item);

    if (isFileNote(item)) {
        QFile::rename(path+item->text(0)+".archive", path+item->text(0)+".txt");
        item->setTextColor(0,"black");
    } else {
        QFile::remove(path+item->text(0)+"/.ignore");
        restoreSubFiles(path+item->text(0));
        changeRestoredColors(item);
    }
}

void MainWindow::ProvideContextMenu(const QPoint &pos)
{
    QTreeWidget *tree = ui->treeNotes;
    QTreeWidgetItem *item = tree->itemAt(pos);
    if (item == nullptr) {return;}

    qDebug()<<pos<<item->text(0);

    currItem(item, false);

    QMenu menu(this);

    if (!MainWindow::isArchiveMode) {
    if (!isFileNote(item)) {
        QAction *actNewNote = new QAction(QIcon(":/icons/icons/new.ico"), tr("&Add new note"), this); //ADD IMAGES
        connect(actNewNote, SIGNAL(triggered()), this, SLOT(on_actNewNote_clicked()));
        menu.addAction(actNewNote);

        QAction *actNewType = new QAction(QIcon(":/icons/icons/new.ico"), tr("&Add new type"), this);
        connect(actNewType, SIGNAL(triggered()), this, SLOT(on_actNewType_clicked()));
        menu.addAction(actNewType);
    }

    if (currItem(item,true)->text(0)!="All") {

        if (isFileNote(item)) {
            QAction *actEditText = new QAction(QIcon(":/icons/icons/edit.ico"), tr("&Edit note text"), this);
            connect(actEditText, SIGNAL(triggered()), this, SLOT(on_actEditText_clicked()));
            menu.addAction(actEditText);
        }
    }

    QAction *actEditName = new QAction(QIcon(":/icons/icons/edit.ico"), tr("&Edit name"), this);
    connect(actEditName, SIGNAL(triggered()), this, SLOT(on_actEditName_clicked()));
    menu.addAction(actEditName);

    QAction *actMove = new QAction(QIcon(":/icons/icons/archive.ico"), tr("&Move to archive"), this);
    connect(actMove, SIGNAL(triggered()), this, SLOT(on_actMove_clicked()));
    menu.addAction(actMove);
    } else {
        QAction *actRestore = new QAction(QIcon(":/icons/icons/archive.ico"), tr("&Restore"), this);
        connect(actRestore, SIGNAL(triggered()), this, SLOT(on_actRestore_clicked()));
        menu.addAction(actRestore);
    }

    QAction *actDelete = new QAction(QIcon(":/icons/icons/delete.ico"), tr("&Delete"), this);
    connect(actDelete, SIGNAL(triggered()), this, SLOT(on_actDelete_clicked()));
    menu.addAction(actDelete);

    menu.exec(tree->mapToGlobal(pos));
}

#endif // CONTEXTMENU_H

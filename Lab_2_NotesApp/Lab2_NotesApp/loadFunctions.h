#ifndef LOADFUNCTIONS_H
#define LOADFUNCTIONS_H

#include "mainwindow.h"
#include "additionalFunctions.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QTreeWidgetItem>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QColor>
#include <QMessageBox>
#include <QIODevice>
#include <QTextStream>

void MainWindow::loadAllFiles (QDir path, QTreeWidgetItem* parent = nullptr, bool sort_by_time = false) {
    if (QFile::exists(path.absolutePath()+"/.ignore")) {
        return;
    }

    QString pathStr = path.absolutePath()+"/";
    pathStr.replace(QDir::current().absolutePath()+"/notes/", "");
    QString currFolder = "";

    while(!pathStr.isEmpty()) {
        int pos = 0;
        while (pathStr[pos]!='/'){
            currFolder+= pathStr[pos];
            pos++;
        }
        pathStr.replace(currFolder+"/", "");
        if (!pathStr.isEmpty()) {
            currFolder.clear();
        }
    }

    QTreeWidgetItem *newItem = nullptr;
    if (!currFolder.isEmpty()) {
        if (parent == nullptr) {
            newItem = new QTreeWidgetItem(ui->treeNotes);
            ui->treeNotes->addTopLevelItem(newItem);
            newItem->setText(0,currFolder);
            newItem->setTextColor(0, "darkred");
        } else {
            newItem = new QTreeWidgetItem(parent);
            newItem->setText(0,currFolder);
            newItem->setTextColor(0, "darkred");
        }
    }

    QStringList subdirs = path.entryList();
    if (sort_by_time) {sortSubList(subdirs,path);}
    foreach (QString curr, subdirs) {
        QString nextPath = path.absolutePath();
        nextPath += "/"+curr;
        QFileInfo check_file(nextPath);

       if (check_file.exists() && curr!="." && curr!="..") {
           if (check_file.isFile()) {
               QString checkArc = curr;
               if (curr.replace(".archive", "") == checkArc) {
                   QTreeWidgetItem *childItem = new QTreeWidgetItem(newItem);
                   childItem->setText(0,curr.replace(".txt", ""));
               }
           } else {
               loadAllFiles(nextPath, newItem, sort_by_time);
           }
       }
    }
}

void MainWindow::loadWithArchived(QDir path, QTreeWidgetItem* parent, bool inArchivedFolder = false, bool sort_by_time = false) {
    if (QFile::exists(path.absolutePath()+"/.ignore")) {
        inArchivedFolder = true;
    }

    QString pathStr = path.absolutePath()+"/";
    pathStr.replace(QDir::current().absolutePath()+"/notes/", "");
    QString currFolder = "";

    while(!pathStr.isEmpty()) {
        int pos = 0;
        while (pathStr[pos]!='/'){
            currFolder+= pathStr[pos];
            pos++;
        }
        pathStr.replace(currFolder+"/", "");
        if (!pathStr.isEmpty()) {
            currFolder.clear();
        }
    }

    QTreeWidgetItem *newItem = nullptr;
    QColor typeColor = "darkred";
    if (inArchivedFolder) {
        typeColor.setRgb(180,116,104);
    }
    if (!currFolder.isEmpty()) {
        if (parent == nullptr) {
            newItem = new QTreeWidgetItem(ui->treeNotes);
            ui->treeNotes->addTopLevelItem(newItem);
            newItem->setText(0,currFolder);
            newItem->setTextColor(0, typeColor);
        } else {
            newItem = new QTreeWidgetItem(parent);
            newItem->setText(0,currFolder);
            newItem->setTextColor(0, typeColor);
        }
    }

    QStringList subdirs = path.entryList();
    if (sort_by_time) {sortSubList(subdirs,path);}
    foreach (QString curr, subdirs) {
        QString nextPath = path.absolutePath();
        nextPath += "/"+curr;
        QFileInfo check_file(nextPath);

       if (check_file.exists() && curr!="." && curr!="..") {
           if (check_file.isFile()) {
               if (curr == ".ignore") {continue;}
               QString checkArc = curr;
               QTreeWidgetItem *childItem = new QTreeWidgetItem(newItem);
               if (curr.replace(".archive", "") == checkArc) {
                   childItem->setText(0,curr.replace(".txt", ""));
                   if (inArchivedFolder) {
                       childItem->setTextColor(0, "grey");
                   }
               } else {
                   childItem->setText(0,curr);
                   childItem->setTextColor(0,"grey");
               }
           } else {
               loadWithArchived(nextPath, newItem, inArchivedFolder);
           }
       }
    }
}

void MainWindow::load_note(QTreeWidgetItem *item, int column) {
    ui->textNote->clear();
    ui->noteName->clear();

    if (!isFileNote(item)) {
        item->setSelected(false);
        return;
    }

    ui->noteName->setEnabled(true);
    ui->textNote->setEnabled(true);
    ui->noteName->setReadOnly(true);
    ui->textNote->setReadOnly(true);
    QString name = item->text(column);

    QString path = findPath(item);
    QFileInfo check_file(path+name+".txt");

    QFile note;
   if (check_file.exists()) {
     note.setFileName(path+name+".txt");
   } else {
      note.setFileName(path+name+".archive");
   }

    ui->noteName->setText(name);

    if (!note.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(0,"Critical", "Something wrong! File with this note can't be open!");
    } else {
        QTextStream in(&note);
        while (!in.atEnd()) {
            ui->textNote->append(in.readLine());
        }
    }
}

#endif // LOADFUNCTIONS_H

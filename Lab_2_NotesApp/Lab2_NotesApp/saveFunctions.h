#ifndef SAVEFUNCTIONS_H
#define SAVEFUNCTIONS_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additionalFunctions.h"
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QMessageBox>
#include <QTreeWidgetItem>

void MainWindow::saveCategory() {
    QString name = ui->noteName->text();
    QTreeWidgetItem* parent = currItem(nullptr,true);

   if (name.isEmpty()) {
        QMessageBox::warning(0,"Restricted name", "You can't have an empty name.");
   } else {
        if (isStringAllowed(name)) {
           if (parent == nullptr) {
               QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(ui->treeNotes);
               ui->treeNotes->addTopLevelItem(topLevelItem);
               topLevelItem->setText(0,name);
               topLevelItem->setTextColor(0, "darkred");
               QDir().mkdir(QDir::current().absolutePath()+"/notes/"+name);
           } else {
               QTreeWidgetItem *item = new QTreeWidgetItem(parent);

               QString path = findPath(item);
               item->setText(0,name);
               item->setTextColor(0, "darkred");

               QDir().mkdir(path+name);
                MainWindow::isCategory = false;
           }
        } else {
            QMessageBox::warning(0, "Restricted name", "You can't have /, \\, ?, *, :, |, \", \', <, >, . in folder name");
        }
   }
}

void MainWindow::saveNote() {
    QTreeWidgetItem* parent = currItem(nullptr,true);
    QString name = ui->noteName->text();
   if (name.isEmpty()) {
       QMessageBox::warning(0, "Restricted name", "You can't have an empty name");
   }
   else {
       if (isStringAllowed(name)) {
           QTreeWidgetItem *item = new QTreeWidgetItem(parent);
           QString path = findPath(item);
           item->setText(0,name);

           QFile note(path+name+".txt");
           if (!note.open(QIODevice::WriteOnly | QIODevice::Text)) {
               QMessageBox::critical(0,"Critical", "Something wrong! File with this note can't be open!");
           } else {
           QTextStream out(&note);
           out << "\n ";
           out << ui->textNote->toPlainText();
           note.close();
           MainWindow::isNote = false;
           }
       } else {
           QMessageBox::warning(0, "Restricted name", "You can't have /, \\, ?, *, :, |, \", \', <, >, . in folder name");
       }
   }
}

void MainWindow::saveEditText() {
   QString name = ui->noteName->text();
   QString path = findPath(currItem(nullptr,true));

   QFile note (path+name+".txt");
   if (!note.open(QIODevice::Append | QIODevice::Text)) {
       QMessageBox::critical(0,"Critical", "Something wrong! File with this note can't be open!");
   } else {
    QTextStream out(&note);
    out<< ui->textNote->toPlainText();
    note.close();
   }

   MainWindow::isEditText = false;
}

void MainWindow::saveEditName() {
   QTreeWidgetItem* item = currItem(nullptr,true);
   QString name = ui->noteName->text();
   if (name.isEmpty()) {
       QMessageBox::warning(0, "Restricted name", "You can't have an empty name");
   } else {
       if (isStringAllowed(name)) {
           QString path = findPath(item);
           if (isFileNote(item)) {
                QFile::rename(path+item->text(0)+".txt", path+name+".txt");
           } else {
               QDir prevName = QDir::current().absolutePath()+"/notes/"+item->text(0);
               QString newName = QDir::current().absolutePath()+"/notes/"+name;
               prevName.rename(QDir::current().absolutePath()+"/notes/"+item->text(0), newName);
           }
           item->setText(0, name);
           MainWindow::isEditName = false;
       } else {
           QMessageBox::warning(0, "Restricted name", "You can't have /, \\, ?, *, :, |, \", \', <, >, . in folder name");
       }
   }
}

#endif // SAVEFUNCTIONS_H

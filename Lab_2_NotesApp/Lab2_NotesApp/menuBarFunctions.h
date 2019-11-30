#ifndef MENUBARFUNCTIONS_H
#define MENUBARFUNCTIONS_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additionalFunctions.h"
#include <QFile>
#include <QFileDevice>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QApplication>
#include <QDir>
#include <algorithm>

void MainWindow::on_actExit_clicked() {
    QApplication::quit();
}

void MainWindow::on_actLoad_all_clicked() {
    ui->treeNotes->clear();
    loadAllFiles(QDir::current().absolutePath()+"/notes/", nullptr, false);
}

void MainWindow::sortSubList (QStringList subdirs, QDir path) {
    std::sort(subdirs.begin(), subdirs.end(), [&path](const QString& left, const QString right)
    {
        QFile leftFile (path.absolutePath()+"/"+left);
        QFile rightFile (path.absolutePath()+"/"+right);
        return (leftFile.fileTime(QFileDevice::FileBirthTime)<rightFile.fileTime(QFileDevice::FileBirthTime));
    });
}

void MainWindow::on_actSort_clicked() {
    ui->treeNotes->clear();
    ui->noteName->clear();
    ui->textNote->clear();

    if (MainWindow::isArchiveMode) {
        loadWithArchived(QDir::current().absolutePath()+"/notes/", nullptr, false, true);

    } else {
        loadAllFiles(QDir::current().absolutePath()+"/notes/", nullptr, true);
    }
}

#endif // MENUBARFUNCTIONS_H

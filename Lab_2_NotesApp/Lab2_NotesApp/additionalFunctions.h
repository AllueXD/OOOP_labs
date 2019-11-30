#ifndef ADDITIONALFUNCTIONS_H
#define ADDITIONALFUNCTIONS_H
#include <QString>
#include <QFile>
#include <QTreeWidgetItem>
#include <QVector>
#include <QDir>

QString findPath (QTreeWidgetItem* item) {
    QString path = QDir::current().absolutePath()+"/notes/";
    QTreeWidgetItem* curr = item->parent();
    QVector<QString> types;

    while (curr != nullptr) {
        types.push_front(curr->text(0)+"/");
        curr = curr->parent();
    }

    for (auto item_type : types) {
        path += item_type;
    }
    return path;
}

bool isFileNote (QTreeWidgetItem* item) {
    QString path = findPath(item);
    return QFile::exists(path+item->text(0)+".txt")||QFile::exists(path+item->text(0)+".archive");
}

QTreeWidgetItem* currItem (QTreeWidgetItem *item, bool get_item) {
    static QTreeWidgetItem *curr;
    if (!get_item) {curr = item;}
    else return curr;
}

bool isStringAllowed (QString name) {
    QString trackChange = name;
    name.replace("/", "");
    name.replace("\\", "");
    name.replace("?", "");
    name.replace("*", "");
    name.replace(":", "");
    name.replace("|", "");
    name.replace("\"", "");
    name.replace("\'", "");
    name.replace("<", "");
    name.replace(">", "");
    name.replace(".", "");
    return (name == trackChange);
}

#endif // ADDITIONALFUNCTIONS_H

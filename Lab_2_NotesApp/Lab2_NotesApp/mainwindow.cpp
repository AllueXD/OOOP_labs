#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTreeView"
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QDebug>
#include<QAction>
#include<QVector>
#include<QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->saveChanges->hide();
    ui->treeNotes->itemAt(0,0)->setTextColor(0,"darkred");
    ui->treeNotes->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeNotes,&QTreeWidget::customContextMenuRequested,this,&MainWindow::ProvideContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem* currItem (QTreeWidgetItem *item, bool get_item) {
    static QTreeWidgetItem *curr;
    if (!get_item) {curr = item;}
    else return curr;
}

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
    if (item->textColor(0) == "darkred") {
        QDir dir(QDir::current().absolutePath()+"/notes/"+"All/"+item->text(0));
        dir.removeRecursively();
    } else {
        QFile::remove(QDir::current().absolutePath()+"/notes/"+"All/"+item->text(0)+".txt");
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

        if (item->textColor(0) == "darkred") {
         QDir dir(path+item->text(0));
         dir.removeRecursively();
        } else { QFile::remove(path+item->text(0)+".txt");}

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

void MainWindow::ProvideContextMenu(const QPoint &pos)
{

    QTreeWidget *tree = ui->treeNotes;
    QTreeWidgetItem *item = tree->itemAt(pos); //DOESN'T WORK IF NO ITEM SELECTED

    qDebug()<<pos<<item->text(0);

    currItem(item, false);

    QMenu menu(this);

    if (item->textColor(0) == "darkred") {
        QAction *actNewNote = new QAction(QIcon(":/Resource/warning32.ico"), tr("&Add new note"), this); //ADD IMAGES
        connect(actNewNote, SIGNAL(triggered()), this, SLOT(on_actNewNote_clicked()));
        menu.addAction(actNewNote);

        QAction *actNewType = new QAction(QIcon(":/Resource/warning32.ico"), tr("&Add new type"), this);
        connect(actNewType, SIGNAL(triggered()), this, SLOT(on_actNewType_clicked()));
        menu.addAction(actNewType);
    }

    if (currItem(item,true)->text(0)!="All") {

        if (item->textColor(0) != "darkred") {
            QAction *actEditText = new QAction(QIcon(":/Resource/warning32.ico"), tr("&Edit note text"), this);
            connect(actEditText, SIGNAL(triggered()), this, SLOT(on_actEditText_clicked()));
            menu.addAction(actEditText);
        }
    }

    QAction *actEditName = new QAction(QIcon(":/Resource/warning32.ico"), tr("&Edit name"), this);
    connect(actEditName, SIGNAL(triggered()), this, SLOT(on_actEditName_clicked()));
    menu.addAction(actEditName);

    QAction *actMove = new QAction(QIcon(":/Resource/warning32.ico"), tr("&Move to archive"), this);
    connect(actMove, SIGNAL(triggered()), this, SLOT(on_actMove_clicked()));
    menu.addAction(actMove);

    QAction *actDelete = new QAction(QIcon(":/Resource/warning32.ico"), tr("&Delete"), this);
    connect(actDelete, SIGNAL(triggered()), this, SLOT(on_actDelete_clicked()));
    menu.addAction(actDelete);

    menu.exec(tree->mapToGlobal(pos));
}


void MainWindow::on_archive_clicked()
{

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

void MainWindow::saveCategory() {
    QString name = ui->noteName->text();
    QTreeWidgetItem* parent = currItem(nullptr,true);

   if (name.size() != 0) {
       if (parent == nullptr) {
           QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(ui->treeNotes);
           ui->treeNotes->addTopLevelItem(topLevelItem);
           topLevelItem->setText(0,name);
           topLevelItem->setTextColor(0, "darkred");
           QDir().mkdir(QDir::current().absolutePath()+"/notes/"+name);
       } else {
           QTreeWidgetItem *item = new QTreeWidgetItem(parent);

           QString path = QDir::current().absolutePath()+"/notes/";
           QTreeWidgetItem* curr = parent;
           QVector<QString> types;

           while (curr != nullptr) {
               types.push_front(curr->text(0)+"/");
               curr = curr->parent();
           }

           for (auto item_type : types) {
               path += item_type;
           }
           item->setText(0,name);
           item->setTextColor(0, "darkred");

           QDir().mkdir(path+name);
       }
   } else {
        //add warning
   }

   MainWindow::isCategory = false;
}

void MainWindow::saveNote() {
    QTreeWidgetItem* parent = currItem(nullptr,true);
    QString name = ui->noteName->text();
   if (name.size() == 0) {
       //warning .... add later
   }
   else {
       QTreeWidgetItem *item = new QTreeWidgetItem(parent);
       QString path = QDir::current().absolutePath()+"/notes/";
       QTreeWidgetItem* curr = parent;
       QVector<QString> types;

       while (curr != nullptr) {
           types.push_front(curr->text(0)+"/");
           curr = curr->parent();
       }

       for (auto item_type : types) {
           path += item_type;
       }
       item->setText(0,name);

       QFile note (path+name+".txt");
       if (!note.open(QIODevice::WriteOnly | QIODevice::Text)) {
           //write warning for check
       } else {
       QTextStream out(&note);
       out << ui->textNote->toPlainText();
       note.close();
       }
   }

   MainWindow::isNote = false;
}

void MainWindow::saveEditText() {
   QString name = ui->noteName->text();
   QString path = QDir::current().absolutePath()+"/notes/";
   QTreeWidgetItem* curr = currItem(nullptr, true)->parent();
   QVector<QString> types;

   while (curr != nullptr) {
       types.push_front(curr->text(0)+"/");
       curr = curr->parent();
   }

   for (auto item_type : types) {
       path += item_type;
   }
   QFile note (path+name+".txt"); //add archive and category
   if (!note.open(QIODevice::Append | QIODevice::Text)) {
       //write warning for check
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

   QFile::rename(QDir::current().absolutePath()+"/notes/"+item->text(0)+".txt", QDir::current().absolutePath()+"/notes/"+name+".txt");
   item->setText(0, name);
   MainWindow::isEditName = false;

}

void MainWindow::load_note(QTreeWidgetItem *item, int column) {
    ui->textNote->clear();
    ui->noteName->clear();

    if (item->textColor(0) == "darkred") {
        item->setSelected(false);
        return;
    }

    ui->noteName->setEnabled(true);
    ui->textNote->setEnabled(true);
    ui->noteName->setReadOnly(true);
    ui->textNote->setReadOnly(true);
    QString name = item->text(column);

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

    QFile note (path+name+".txt");

    ui->noteName->setText(name);

    if (!note.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //enter warning here
    } else {
        QTextStream in(&note);
        while (!in.atEnd()) {
            ui->textNote->append(in.readLine());
        }
    }
}

void MainWindow::on_treeNotes_itemClicked(QTreeWidgetItem *item, int column)
{
    load_note(item, column);
}


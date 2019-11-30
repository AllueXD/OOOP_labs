#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QPoint>
#include <QDir>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void load_note(QTreeWidgetItem *item, int column);
    void save_catogery();
    bool isCategory = false;
    bool isNote = false;
    bool isEditText = false;
    bool isEditName = false;
    bool isArchiveMode = false;

private slots:

    void ProvideContextMenu(const QPoint &pos);
    void on_actNewNote_clicked();
    void on_actNewType_clicked();
    void on_actDelete_clicked();
    void on_actEditText_clicked();
    void on_actEditName_clicked();
    void on_actMove_clicked();
    void on_actRestore_clicked();

    void on_actLoad_all_clicked();
    void on_actExit_clicked();
    void on_actSort_clicked();

    void on_archive_clicked();
    void on_addNew_clicked();
    void on_treeNotes_itemClicked(QTreeWidgetItem *item, int column);
    void on_saveChanges_clicked();

    void changeRestoredColors (QTreeWidgetItem* parent);
    void sortSubList (QStringList subdirs, QDir path);
    void loadAllFiles (QDir path, QTreeWidgetItem* parent, bool sort_by_time);
    void loadWithArchived(QDir path, QTreeWidgetItem* parent, bool inArchivedFolder, bool sort_by_time);

    void saveNote();
    void saveEditText();
    void saveEditName();
    void saveCategory();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

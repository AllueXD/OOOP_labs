#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QAction>

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

private slots:

    void on_actNewNote_clicked();
    void on_actNewType_clicked();
    void on_actDelete_clicked();
    void on_actEditText_clicked();
    void on_actEditName_clicked();

    void on_archive_clicked();

    void on_addNew_clicked();

    void on_treeNotes_itemClicked(QTreeWidgetItem *item, int column);

    void ProvideContextMenu(const QPoint &pos);

    void on_saveChanges_clicked();

    void saveNote();
    void saveEditText();
    void saveEditName();
    void saveCategory();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

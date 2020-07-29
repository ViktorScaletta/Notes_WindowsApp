#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newnote.h"
#include "noteeditor.h"
#include <QDebug>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateListNotes();

private slots:
    void on_newNote_triggered();

    void on_exitButton_triggered();

    void on_updateButton_triggered();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionthrhrt_triggered();

private:
    Ui::MainWindow *ui;
    NewNote *newnoteui;
    NoteEditor *noteeditorui;
};
#endif // MAINWINDOW_H

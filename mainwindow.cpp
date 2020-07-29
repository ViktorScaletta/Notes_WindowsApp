#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateListNotes();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateListNotes()
{
    DbManager db;

    QStringList listNotes = db.showAllNotes();

    ui->listWidget->clear();

    for(auto item: listNotes)
        new QListWidgetItem(item, ui->listWidget);
}


void MainWindow::on_newNote_triggered()
{
//    NewNote newnote;
//    newnote.setModal(true);
//    newnote.exec();
    newnoteui = new NewNote(this);
    newnoteui->show();
}

void MainWindow::on_exitButton_triggered()
{
    QApplication::quit();
}

void MainWindow::on_updateButton_triggered()
{
    updateListNotes();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString nameNote = item->text();

    noteeditorui = new NoteEditor(this, nameNote);
    noteeditorui->show();
}

void MainWindow::on_actionthrhrt_triggered()
{

}

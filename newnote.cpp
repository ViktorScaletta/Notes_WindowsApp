#include "newnote.h"
#include "mainwindow.h"
#include "ui_newnote.h"
#include "dbmanager.h"
#include <QMessageBox>


NewNote::NewNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNote)
{
    ui->setupUi(this);
}

NewNote::~NewNote()
{
    delete ui;
}

void NewNote::on_saveNoteButton_clicked()
{
    DbManager db;

    QString nameNoteField = ui->nameNoteField->text();
    QString textNoteField = ui->textNoteField->toPlainText();

    if (db.isOpen())
    {
        db.createTable();
        if (db.addNote(nameNoteField, textNoteField))
        {
            NewNote::close();
        }
        else
        {
            QMessageBox::warning(this, "Error", "A note with this name already exists. \n Enter a different name.");
        }

    }
    else
    {
        qDebug() << "Database is not open!";
    }

}

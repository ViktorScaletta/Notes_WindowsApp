#include "noteeditor.h"
#include "ui_noteeditor.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QDebug>

NoteEditor::NoteEditor(QWidget *parent, QString nameNote) :
    QDialog(parent),
    ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
    DbManager db;

    QStringList noteList = db.noteReturn(nameNote);

    id = noteList[0].toInt();
    ui->nameNoteField->setText(noteList[1]);
    ui->textNoteField->setText(noteList[2]);
}

NoteEditor::~NoteEditor()
{
    delete ui;
}

void NoteEditor::on_saveNoteButton_clicked()
{
    DbManager db;

    QString nameNoteField = ui->nameNoteField->text();
    QString textNoteField = ui->textNoteField->toPlainText();

    if (db.isOpen())
    {
        db.createTable();
        if (db.editNote(nameNoteField, textNoteField, id))
        {
            NoteEditor::close();
        }
        else
        {
        QMessageBox::warning(this, "Ошибка", "Заметка с таким названием уже существует. \n Введите другое имя для вашей заметки.");
        }

    }
    else
    {
        qDebug() << "Database is not open!";
    }
}

void NoteEditor::on_deleteNoteButton_clicked()
{
    DbManager db;

    QString nameNoteField = ui->nameNoteField->text();
    QString textNoteField = ui->textNoteField->toPlainText();

    if (db.isOpen())
    {
        db.createTable();
        if (db.removeNote(nameNoteField))
        {
            NoteEditor::close();
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

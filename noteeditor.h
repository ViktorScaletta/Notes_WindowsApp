#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QDialog>

namespace Ui {
class NoteEditor;
}

class NoteEditor : public QDialog
{
    Q_OBJECT

public:
    explicit NoteEditor(QWidget *parent = nullptr, QString nameNote="");
    ~NoteEditor();
    int id;

private slots:
    void on_saveNoteButton_clicked();

    void on_deleteNoteButton_clicked();

private:
    Ui::NoteEditor *ui;
};

#endif // NOTEEDITOR_H

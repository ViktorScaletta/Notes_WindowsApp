#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase>

static QString path = "D://Notes.db";

class DbManager
{
public:
    DbManager();
    ~DbManager();
    static void connection();
    bool isOpen() const;
    bool createTable();
    bool addNote(const QString& name_note, const QString& text_note);
    bool editNote(const QString& name_note, const QString& text_note, const int ID);
    bool removeNote(const QString& name_note);
    void showNote(const QString& name);
    QStringList showAllNotes() const;
    void removeAllNotes() const;
    QStringList noteReturn(const QString& nameNote);
    bool noteExists(const QString& name_note)  const;
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

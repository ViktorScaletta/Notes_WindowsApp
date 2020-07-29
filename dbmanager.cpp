#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
        qDebug() << m_db;
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE Notes(id INTEGER PRIMARY KEY, name_note varchar(100), text_note TEXT);");

    if (query.exec())
    {
        success = true;
    }
    return success;
}

bool DbManager::addNote(const QString& name_note, const QString& text_note)
{
   bool success = false;

   if (!name_note.isEmpty() && !noteExists(name_note))
   {
       QSqlQuery queryAdd;
       queryAdd.prepare("INSERT INTO Notes (name_note, text_note) "
                        "VALUES (:name_note, :text_note)");
       queryAdd.bindValue(":name_note", name_note);
       queryAdd.bindValue(":text_note", text_note);

       if(queryAdd.exec())
       {
           queryAdd.next();
           success = true;
       }
       else
       {
           qDebug() << "add note failed: " << queryAdd.lastError();
           qDebug() << queryAdd.exec();
       }
   }
   else if (noteExists(name_note))
   {
       qDebug() << "add note failed: name already exists";
   }
   else
   {
       qDebug() << "add note failed: name cannot be empty";
   }

   return success;
}

bool DbManager::editNote(const QString& name_note, const QString& text_note, const int ID)
{
   bool success = false;

   if (!name_note.isEmpty())
   {
       QSqlQuery queryEdit;

       queryEdit.prepare("UPDATE Notes SET name_note=:name, text_note=:text WHERE ID = (:ID)");

       queryEdit.bindValue(":name", name_note);
       queryEdit.bindValue(":text", text_note);
       queryEdit.bindValue(":ID", ID);

       success = queryEdit.exec();
   }
   else
   {
       qDebug() << "edit note failed: name cannot be empty";
   }

   return success;
}

bool DbManager::removeNote(const QString& name_note)
{
    bool success = false;

    if (noteExists(name_note))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM Notes WHERE name_note = (:name)");
        queryDelete.bindValue(":name", name_note);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove note failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove note failed: note doesn't exist";
    }

    return success;
}

QStringList DbManager::showAllNotes() const
{
    QStringList notesList;

    QSqlQuery query("SELECT * FROM Notes");
    int idName = query.record().indexOf("name_note");

    while (query.next())
    {
        QString name = query.value(idName).toString();
        notesList.append(name);
    }
    return notesList;
}

void DbManager::removeAllNotes() const
{
    qDebug() << "Removing list of notes";
    QSqlQuery query("DELETE FROM Notes");
    query.exec();
}

QStringList DbManager::noteReturn(const QString& nameNote)
{
    QSqlQuery returnQuery;
    returnQuery.prepare("SELECT * FROM Notes WHERE name_note = (:name)");
    returnQuery.bindValue(":name", nameNote);

    QString name, text;
    QStringList noteList;

    if (returnQuery.exec())
    {
        if (returnQuery.next())
        {
            QString id = returnQuery.value(0).toString();
            noteList.append(id);
            QString name = returnQuery.value(1).toString();
            noteList.append(name);
            QString text = returnQuery.value(2).toString();
            noteList.append(text);
        }
    }

    return noteList;
}

bool DbManager::noteExists(const QString& name_note) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name_note FROM Notes WHERE name_note = (:name)");
    checkQuery.bindValue(":name", name_note);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "note exists failed: " << checkQuery.lastError();
    }

    return exists;
}

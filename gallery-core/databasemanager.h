#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include "albumdao.h"

class QSqlDatabase;
const QString DB_FILENAME= "gallery.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& path= DB_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

public:
    const AlbumDao albumDao;

private:
    QSqlDatabase* mDatabase;
};

#endif // DATABASEMANAGER_H

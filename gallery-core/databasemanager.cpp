#include "databasemanager.h"

#include <QSqlDatabase>

/**
 * @brief DatabaseManager::instance
 * @return
 */
DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

/**
 * @brief DatabaseManager::~DatabaseManager
 */
DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}

/**
 * @brief DatabaseManager::DatabaseManager
 * @param path
 */
DatabaseManager::DatabaseManager(const QString &path):
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    albumDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();

    albumDao.init();
}

#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

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
 * @brief DatabaseManager::debugQuery
 * @param query
 */
void DatabaseManager::debugQuery(QSqlQuery query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
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
    albumDao(*mDatabase),
    pictureDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);

    bool openStatus = mDatabase->open();
    qDebug() << "Database connection: " << (openStatus ? "OK" : "Error");

    albumDao.init();
    pictureDao.init();
}

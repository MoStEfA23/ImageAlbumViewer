#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>

/**
 * @brief DatabaseManager::instance
 * @return
 */
DatabaseManager &DatabaseManager::instance()
{
#if defined(Q_OS_ANDROID)
    QFile dbFile(":/database/"+ DB_FILENAME);
    QString destination = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation).
            append("/" + DB_FILENAME );

    if(QFile::exists(destination))
    {
        dbFile.copy(destination);
        QFile::setPermissions(destination,
                        QFile::WriteOwner | QFile::ReadOwner);
    }

    static DatabaseManager singleton(destination);
#else
    static DatabaseManager singleton;
#endif
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

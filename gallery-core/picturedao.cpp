#include "picturedao.h"

#include "picture.h"
#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QDebug>


const QString PICTURE_DATABASENAME = "pictures";

/**
 * @brief PictureDao::PictureDao
 * @param database
 */
PictureDao::PictureDao(QSqlDatabase &database):
    mDatabase(database)
{

}

/**
 * @brief PictureDao::init
 */
void PictureDao::init() const
{
    if(!mDatabase.tables().contains(PICTURE_DATABASENAME))
    {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures")
                   + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   + "album_id INTEGER, "
                   + "url TEXT)");
        DatabaseManager::debugQuery(query);
    }
}

/**
 * @brief PictureDao::addPictureInAlbum
 * @param albumId
 * @param picture
 */
void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO pictures (album_id, url) values (:albumId, :url)");
    query.bindValue(":albumId", albumId);
    query.bindValue(":url", picture.fileURL());

    query.exec();
    DatabaseManager::debugQuery(query);
    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);
}

/**
 * @brief PictureDao::removePicture
 * @param pictureId
 */
void PictureDao::removePicture(int pictureId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE pictures where id = :id");
    query.bindValue(":id", pictureId);

    query.exec();
}

/**
 * @brief PictureDao::removePicturesForAlbum
 * @param albumId
 */
void PictureDao::removePicturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE album_id = :albumd_id");
    query.bindValue(":album_id", albumId);
    query.exec();
}

/**
 * @brief PictureDao::picturesForAlbum
 * @param albumId
 * @return
 */
std::unique_ptr<std::vector<std::unique_ptr<Picture> > > PictureDao::picturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> list(new std::vector<std::unique_ptr<Picture>>());
    while(query.next()) {
        std::unique_ptr<Picture> picture(new Picture());
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileURL(query.value("url").toString());
        list->push_back(std::move(picture));
    }
    return list;
}


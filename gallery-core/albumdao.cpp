#include "albumdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "album.h"

const QString ALBUM_DATABASENAME = "albums";
/**
 * @brief AlbumDao::AlbumDao
 * @param database
 */
AlbumDao::AlbumDao(QSqlDatabase &database):
    mDatabase(database)
{

}

/**
 * @brief AlbumDao::init
 */
void AlbumDao::init() const
{
    if(!mDatabase.tables().contains(ALBUM_DATABASENAME))
    {
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    }
}

/**
 * @brief AlbumDao::addAlbum
 * @param newAlbum
 */
void AlbumDao::addAlbum(Album &newAlbum) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO albums name values (:name)");
    query.bindValue(":name", newAlbum.name());
    query.exec();

    newAlbum.setId(query.lastInsertId().toInt());
}

/**
 * @brief AlbumDao::updateAlbum
 * @param album
 */
void AlbumDao::updateAlbum(const Album &album)
{

}

/**
 * @brief AlbumDao::albums
 * @return
 */
QVector<Album *> AlbumDao::albums()
{
   QSqlQuery query("SELECT * FROM albums", mDatabase);
   query.exec();
   QVector<Album*> albums;

   while (query.next()) {
        Album* album = new Album();

        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());

        albums.append(album);
   }

   return albums;
}

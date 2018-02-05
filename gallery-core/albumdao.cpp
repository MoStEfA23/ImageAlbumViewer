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
void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums SET name = :name WHERE id= :id");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
}

/**
 * @brief AlbumDao::removeAlbum
 * @param albumId
 */
void AlbumDao::removeAlbum(int albumId) const
{
   QSqlQuery query(mDatabase);
   query.prepare("DELETE FROM albums WHERE id= :id");
   query.bindValue(":id", albumId);

   query.exec();
}

/**
 * @brief AlbumDao::albums
 * @return
 */
std::unique_ptr<std::vector<std::unique_ptr<Album> > > AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums", mDatabase);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> list(new std::vector<std::unique_ptr<Album>>());
    while(query.next()) {
        std::unique_ptr<Album> album(new Album());
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list->push_back(std::move(album));
    }
    return list;
}



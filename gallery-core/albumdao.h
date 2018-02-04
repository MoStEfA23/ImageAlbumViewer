#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <QVector>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
    AlbumDao(QSqlDatabase& database);
    void init() const;

    void addAlbum(Album& newAlbum) const;
    void updateAlbum(const Album &album);
    void removeAlbum(int albumId);
    QVector<Album*> albums();

private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDAO_H

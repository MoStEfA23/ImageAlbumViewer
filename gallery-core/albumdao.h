#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <QVector>
#include <memory>

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
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDAO_H

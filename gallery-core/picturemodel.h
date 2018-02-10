#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery-core_global.h"
#include "picture.h"

class AlbumModel;
class DatabaseManager;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PictureRole{
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };

    PictureModel(const AlbumModel& albumModel, QObject* parent = 0);
    QModelIndex addPicture(const Picture& picture);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    Q_INVOKABLE void setAlbumId(int id);
    void clearAlbum();

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addPictureFromUrl(const QUrl& url);

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDb;
    int mAlbumId;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> mPictures;
};

#endif // PICTUREMODEL_H

#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QAbstractListModel>
#include <QHash>

#include <memory>
#include <vector>

#include "gallery-core_global.h"
#include "album.h"
#include "databasemanager.h"

class GALLERYCORESHARED_EXPORT AlbumModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        IdRole = Qt::UserRole + 1,
        NameRole,
    };

    AlbumModel(QObject* parent = 0);

    Q_INVOKABLE QModelIndex addAlbum(const Album& album);
    Q_INVOKABLE void addAlbumFromName(const QString& name);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isIndexValid(const QModelIndex& modelIndex) const;

private:
    DatabaseManager& mDb;
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> mAlbums;
};

#endif // ALBUMMODEL_H

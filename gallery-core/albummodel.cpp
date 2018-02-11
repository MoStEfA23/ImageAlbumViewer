#include "albummodel.h"

/**
 * @brief AlbumModel::AlbumModel
 */
AlbumModel::AlbumModel(QObject* parent):
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbums(mDb.albumDao.albums())
{

}


/**
 * @brief AlbumModel::addAlbum
 * @param album
 * @return
 */
QModelIndex AlbumModel::addAlbum(const Album &album)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::unique_ptr<Album> newAlbum(new Album(album));
    mDb.albumDao.addAlbum(*newAlbum);
    mAlbums->push_back(std::move(newAlbum));
    endInsertRows();

    return index(rowIndex, 0);
}


/**
 * @brief AlbumModel::addAlbumFromName
 * @param name
 */
void AlbumModel::addAlbumFromName(const QString &name)
{
   addAlbum(Album(name));
}

/**
 * @brief AlbumModel::rowCount
 * @return
 */
int AlbumModel::rowCount(const QModelIndex& parent) const
{
    return mAlbums->size();
}

/**
 * @brief AlbumModel::data
 * @param index
 * @param role
 * @return
 */
QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
    if(!isIndexValid(index))
    {
        return QVariant();
    }

    const Album& album = *mAlbums->at(index.row());

    switch (role) {
    case IdRole:
        return album.id();
        break;
    case NameRole:
        return album.name();
        break;
    default:
        return QVariant();
    }
}

/**
 * @brief AlbumModel::setData
 * @param index
 * @param value
 * @param role
 * @return
 */
bool AlbumModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!isIndexValid(index) || role != Roles::NameRole)
    {
        return false;
    }

    Album& album = *mAlbums->at(index.row());
    album.setName(value.toString());
    mDb.albumDao.updateAlbum(album);
    emit dataChanged(index, index);

    return true;
}

/**
 * @brief AlbumModel::removeRows
 * @param row
 * @param count
 * @param parent
 * @return
 */
bool AlbumModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if((row < 0) || (row >= rowCount()) || (count < 0) || (row+count) > rowCount())
    {
        return false;
    }

    beginRemoveRows(parent, row, row+count);
    int countLeft = count;

    while (countLeft--) {
        const Album& album = *mAlbums->at(row + countLeft);
        mDb.albumDao.removeAlbum(album.id());
    }

    mAlbums->erase(mAlbums->begin() + row, mAlbums->begin() + row + count);

    endRemoveRows();

    return true;
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";

    return roles;
}

/**
 * @brief AlbumModel::rename
 * @param newName
 */
void AlbumModel::rename(const int row, const QString &newName)
{
   setData(index(row), newName, Roles::NameRole);
}

bool AlbumModel::isIndexValid(const QModelIndex &index) const
{
    if (index.row() < 0 ||
            index.row() >= rowCount() ||
            !index.isValid())
    {
        return false;
    }
    return true;
}

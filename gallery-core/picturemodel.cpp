#include "picturemodel.h"

#include "databasemanager.h"
#include "albummodel.h"
#include "picturedao.h"

/**
 * @brief PictureModel::PictureModel
 * @param albumModel
 * @param parent
 */
PictureModel::PictureModel(const AlbumModel &albumModel, QObject *parent):
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbumId(-1),
    mPictures(new std::vector<std::unique_ptr<Picture>>())
{
    connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}


/**
 * @brief PictureModel::addPicture
 * @param picture
 * @return
 */
QModelIndex PictureModel::addPicture(const Picture &picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    std::unique_ptr<Picture>newPicture(new Picture(picture));
    mDb.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures->push_back(std::move(newPicture));
    endInsertRows();
    return index(rows, 0);
}

/**
 * @brief PictureModel::rowCount
 * @param parent
 * @return
 */
int PictureModel::rowCount(const QModelIndex &parent) const
{
   return mPictures->size();
}

/**
 * @brief PictureModel::data
 * @param index
 * @param role
 * @return
 */
QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const Picture& picture = *mPictures->at(index.row());
    switch (role) {
        case Qt::DisplayRole:
            return picture.fileURL().fileName();
            break;

        case PictureRole::UrlRole:
            return picture.fileURL();
            break;

        case PictureRole::FilePathRole:
            return picture.fileURL().toLocalFile();
            break;


        default:
            return QVariant();
    }
}

/**
 * @brief PictureModel::removeRows
 * @param row
 * @param parent
 * @return
 */
bool PictureModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while(countLeft--) {
        const Picture& picture = *mPictures->at(row + countLeft);
        mDb.pictureDao.removePicture(picture.id());
    }
    mPictures->erase(mPictures->begin() + row,
                    mPictures->begin() + row + count);
    endRemoveRows();

    return true;
}

/**
 * @brief PictureModel::setAlbumId
 * @param id
 */
void PictureModel::setAlbumId(int id)
{
    beginResetModel();
    mAlbumId = id;
    loadPictures(id);
    endResetModel();
}

/**
 * @brief PictureModel::clearAlbum
 */
void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

/**
 * @brief PictureModel::roleNames
 * @return
 */
QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PictureRole::FilePathRole] = "filepath";

    return roles;
}

/**
 * @brief PictureModel::deletePicturesForAlbum
 */
void PictureModel::deletePicturesForAlbum()
{
   mDb.pictureDao.removePicturesForAlbum(mAlbumId);
   clearAlbum();
}

/**
 * @brief PictureModel::loadPictures
 * @param albumId
 */
void PictureModel::loadPictures(int albumId)
{
   if(mAlbumId<= 0)
   {
        mPictures.reset(new std::vector<std::unique_ptr<Picture>> ());
        return;
   }

   mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

/**
 * @brief PictureModel::isIndexValid
 * @param index
 * @return
 */
bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    if (index.row() < 0
            || index.row() >= rowCount(index)
            || !index.isValid()) {
        return false;
    }
    return true;
}

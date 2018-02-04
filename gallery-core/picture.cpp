#include "picture.h"

/**
 * @brief Picture::Picture
 * @param filePath
 */
Picture::Picture(const QString &filePath):
    Picture(QUrl::fromLocalFile(filePath))
{

}

/**
 * @brief Picture::Picture
 * @param fileUrl
 */
Picture::Picture(const QUrl &fileUrl):
    mId(-1),
    mAlbumId(-1),
    mFileURL(fileUrl)
{

}

/**
 * @brief Picture::id
 * @return
 */
int Picture::id() const
{
    return mId;
}

/**
 * @brief Picture::setId
 * @param id
 */
void Picture::setId(int id)
{
    mId = id;
}

/**
 * @brief Picture::albumId
 * @return
 */
int Picture::albumId() const
{
    return mAlbumId;
}

/**
 * @brief Picture::setAlbumId
 * @param albumId
 */
void Picture::setAlbumId(int albumId)
{
    mAlbumId = albumId;
}

/**
 * @brief Picture::fileURL
 * @return
 */
QUrl Picture::fileURL() const
{
    return mFileURL;
}

/**
 * @brief Picture::setFileURL
 * @param fileURL
 */
void Picture::setFileURL(const QUrl &fileURL)
{
    mFileURL = fileURL;
}

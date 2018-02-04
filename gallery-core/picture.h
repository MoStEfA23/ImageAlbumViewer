#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl>

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Picture
{
public:
    Picture(const QString& filePath = "");
    Picture(const QUrl& fileUrl);


    int id() const;
    void setId(int id);

    int albumId() const;
    void setAlbumId(int albumId);

    QUrl fileURL() const;
    void setFileURL(const QUrl &fileURL);

private:
    int mId;
    int mAlbumId;
    QUrl mFileURL;
};

#endif // PICTURE_H

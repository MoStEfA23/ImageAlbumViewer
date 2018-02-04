#ifndef ALBUM_H
#define ALBUM_H

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Album
{

public:
    explicit Album(const QString &name = "");


private:
    int mId;
    QString mName;
};

#endif // ALBUM_H

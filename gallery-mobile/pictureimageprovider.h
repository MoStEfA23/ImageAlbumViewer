#ifndef PICTUREIMAGEPROVIDER_H
#define PICTUREIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QCache>

class PictureModel;

class PictureImageProvider : public QQuickImageProvider
{
public:
    PictureImageProvider(PictureModel* pictureModel);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

    QPixmap* pictureFromCache(const QString& filepath, const QString& pictureSize);

public:
    static const QSize THUMBNAIL_SIZE;
private:
    PictureModel* mPictureModel;
    QCache<QString, QPixmap> mPicturesCache;
};

#endif // PICTUREIMAGEPROVIDER_H

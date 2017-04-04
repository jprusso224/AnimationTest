#ifndef ANIMATIONFRAMELAYER_H
#define ANIMATIONFRAMELAYER_H

#include "GameTypes.h"

#include <QHash>

/*
 * AnimationFrameLayer
 */
class AnimationFrameLayer
{
public:
    AnimationFrameLayer();
    AnimationFrameLayer(const QString &layerNameIn, const quint8 &zOrderIn);

    virtual ~AnimationFrameLayer();

    const Z_Order getZOrder() const;
    const QString getLayerName() const;
    const QHash<QString, QString> getLayerImageHash() const;

    void insertFrameLayerImage(QString objectKey, QString imgName);

private:
    QString layerName = "";
    Z_Order zOrder = 0;
    GameBoolean active = GAME_FALSE;

    QHash<QString, QString> layerImgHashTable;
};

#endif // ANIMATIONFRAMELAYER_H

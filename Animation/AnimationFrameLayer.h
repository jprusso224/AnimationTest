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

    const QString getLayerName();
    const QHash<QString, QString> getLayerImageHash();
    void insertFrameLayerImage(QString objectKey, QString imgName);

private:
    QString layerName = "";
    quint8 zOrder = 0;
    GameBoolean active = GAME_FALSE;

    QHash<QString, QString> layerImgHashTable;
};

#endif // ANIMATIONFRAMELAYER_H

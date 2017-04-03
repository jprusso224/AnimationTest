#include "AnimationFrameLayer.h"

AnimationFrameLayer::AnimationFrameLayer()
{
}

AnimationFrameLayer::AnimationFrameLayer(const QString &layerNameIn, const quint8 &zOrderIn)
    : layerName(layerNameIn), zOrder(zOrderIn)
{
}

AnimationFrameLayer::~AnimationFrameLayer()
{
}

const QString AnimationFrameLayer::getLayerName()
{
    return layerName;
}

const QHash<QString, QString> AnimationFrameLayer::getLayerImageHash()
{
    return layerImgHashTable;
}

void AnimationFrameLayer::insertFrameLayerImage(QString objectKey, QString imgName)
{
    layerImgHashTable.insert(objectKey, imgName);
}

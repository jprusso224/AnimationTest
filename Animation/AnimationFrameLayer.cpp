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

const Z_Order AnimationFrameLayer::getZOrder() const
{
    return zOrder;
}

const QString AnimationFrameLayer::getLayerName() const
{
    return layerName;
}

const QHash<QString, QString> AnimationFrameLayer::getLayerImageHash() const
{
    return layerImgHashTable;
}

void AnimationFrameLayer::insertFrameLayerImage(QString objectKey, QString imgName)
{
    layerImgHashTable.insert(objectKey, imgName);
}

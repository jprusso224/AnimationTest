#include "AnimationFrame.h"

AnimationFrame::AnimationFrame()
{

}

AnimationFrame::AnimationFrame(const QString &frameIdIn, const QString &imgLocIn)
    : frameID(frameIdIn), imageLocation(imgLocIn)
{

}

AnimationFrame::~AnimationFrame()
{

}

const QString AnimationFrame::getImageLocation() const
{
    return imageLocation;
}

const QList<QSharedPointer<AnimationFrameLayer>> AnimationFrame::getFrameLayerList() const
{
    return frameLayerList;
}

void AnimationFrame::appendFrameLayer(const QSharedPointer<AnimationFrameLayer> &layer)
{
    frameLayerList.append(layer);
}

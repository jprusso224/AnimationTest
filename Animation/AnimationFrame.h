#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include "GameTypes.h"
#include "AnimationFrameLayer.h"

#include <QString>
#include <QSharedPointer>


/*
 * AnimationFrame
 */
class AnimationFrame
{
public:
    AnimationFrame();
    AnimationFrame(const QString &frameIdIn, const QString &imgLocIn);
    virtual ~AnimationFrame();

    const QString getImageLocation() const;
    const QList<QSharedPointer<AnimationFrameLayer>> getFrameLayerList() const;
    void appendFrameLayer(const QSharedPointer<AnimationFrameLayer> &layer);

private:
    QString frameID = "";
    QString imageLocation = "";
    QList<QSharedPointer<AnimationFrameLayer>> frameLayerList;
};

#endif // ANIMATIONFRAME_H

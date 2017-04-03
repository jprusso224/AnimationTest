#ifndef FRAMECONFIGURATIONLOADER_H
#define FRAMECONFIGURATIONLOADER_H

#include "AnimationFrame.h"
#include "GameItem/GameItemRegestry.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QSharedPointer>

class FrameConfigurationLoader
{
public:
    FrameConfigurationLoader(const QString &animationFrameFileIn, QSharedPointer<GameItemRegestry> itemRegestryIn);

    virtual ~FrameConfigurationLoader();

    const QList<QSharedPointer<AnimationFrame>> getFrameList() const;

    GameBoolean loadFramesFromXml();

private:

    void readNextFrameElement();

    /*Tag handlers*/
    void processFrameTag();
    void processFrameLayerTag();
    void processLayerImgTag();

    QList<QSharedPointer<AnimationFrame>> frameList;

    QScopedPointer<QXmlStreamReader> xmlReader; /*xml parser*/

    QSharedPointer<QFile> animationFrameFile; /*file to be parsed*/

    QSharedPointer<AnimationFrame> workingFrame;
    QSharedPointer<AnimationFrameLayer> workingFrameLayer;

    QSharedPointer<GameItemRegestry> itemRegestry;

    static const QString FRAME_TAG;
    static const QString FRAME_ID_ATTR;
    static const QString IMG_LOC_ATTR;

    static const QString FRAME_LAYER_TAG;
    static const QString LAYER_ID_ATTR;
    static const QString Z_ORDER_ATTR;

    static const QString LAYER_IMG_TAG;
    static const QString OBJECT_KEY_ATTR;
    static const QString IMG_NAME_ATTR;

};

#endif // FRAMECONFIGURATIONLOADER_H

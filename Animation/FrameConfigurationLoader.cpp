#include "FrameConfigurationLoader.h"

#include <QDebug>

const QString FrameConfigurationLoader::FRAME_TAG = QString("frame");
const QString FrameConfigurationLoader::FRAME_ID_ATTR = QString("frame-id");
const QString FrameConfigurationLoader::IMG_LOC_ATTR = QString("img-location");

const QString FrameConfigurationLoader::FRAME_LAYER_TAG = QString("frame-layer");
const QString FrameConfigurationLoader::LAYER_ID_ATTR = QString("layer-name");
const QString FrameConfigurationLoader::Z_ORDER_ATTR = QString("z-order");

const QString FrameConfigurationLoader::LAYER_IMG_TAG = QString("layer-img");
const QString FrameConfigurationLoader::OBJECT_KEY_ATTR = QString("object-key");
const QString FrameConfigurationLoader::IMG_NAME_ATTR = QString("img");

FrameConfigurationLoader::FrameConfigurationLoader(const QString &animationFrameFileIn,
                                                   QSharedPointer<GameItemRegestry> itemRegestryIn)
    :    itemRegestry(itemRegestryIn)
{
    animationFrameFile = QSharedPointer<QFile>::create(animationFrameFileIn);

    QScopedPointer<QXmlStreamReader> xmlReaderSwap(new QXmlStreamReader(animationFrameFile.data()));
    xmlReader.swap(xmlReaderSwap);
}

FrameConfigurationLoader::~FrameConfigurationLoader()
{

}

const QList<QSharedPointer<AnimationFrame>> FrameConfigurationLoader::getFrameList() const
{
    return frameList;
}

GameBoolean FrameConfigurationLoader::loadFramesFromXml()
{
    GameBoolean success = GAME_TRUE;

    if(!animationFrameFile.data()->open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open frame file";
        success = GAME_FALSE;
    }

    if(itemRegestry.isNull())
    {
        qDebug() << "Item regestry is NULL";
        success = GAME_FALSE;
    }

    if(success)
    {
        while(!xmlReader->atEnd())
        {
            if(xmlReader->readNextStartElement())
            {
                readNextFrameElement();
            }
        }
    }

    animationFrameFile.data()->close();

    return success;
}

void FrameConfigurationLoader::readNextFrameElement()
{
    QStringRef tagName = xmlReader->name();

    if(tagName.compare(FRAME_TAG) == 0)
    {
        processFrameTag();
    }
    else if(tagName.compare(FRAME_LAYER_TAG) == 0)
    {
        processFrameLayerTag();
    }
    else if(tagName.compare(LAYER_IMG_TAG) == 0)
    {
        processLayerImgTag();
    }
    else
    {
        qDebug() << "Unrecognized XML Tag: " << tagName;
    }
}

void FrameConfigurationLoader::processFrameTag()
{
    //MAKE SURE TO SET THE WORKING FRAME!!!
    QStringRef attrName;

    GameBoolean frameIdSet = GAME_FALSE;
    GameBoolean imgLocSet = GAME_FALSE;
    QString frameId = "";
    QString imgLoc = "";

    QXmlStreamAttributes attrs = xmlReader->attributes();
    for(QXmlStreamAttribute attr : attrs)
    {
        attrName = attr.name();

        if(attrName.compare(FRAME_ID_ATTR) == 0)
        {
            frameId = attr.value().toString();
            frameIdSet = GAME_TRUE;
        }
        else if(attrName.compare(IMG_LOC_ATTR) == 0)
        {
            imgLoc = attr.value().toString();
            imgLocSet = GAME_TRUE;
        }
        else
        {
            qDebug() << "Unrecognized Frame Attribute: " << attrName;
        }
    }

    if(imgLocSet && imgLocSet)
    {
        QSharedPointer<AnimationFrame> frameConfig = QSharedPointer<AnimationFrame>::create(frameId,imgLoc);
        frameList.append(frameConfig);
        workingFrame = frameConfig;
    }
}

void FrameConfigurationLoader::processFrameLayerTag()
{
    QStringRef attrName;

    GameBoolean layerNameSet = GAME_FALSE;
    GameBoolean zOrderSet = GAME_FALSE;
    QString layerName = "";
    quint8 zOrder = 0;

    QXmlStreamAttributes attrs = xmlReader->attributes();
    for(QXmlStreamAttribute attr : attrs)
    {
        attrName = attr.name();

        if(attrName.compare(LAYER_ID_ATTR) == 0)
        {
            layerName = attr.value().toString();
            layerNameSet = GAME_TRUE;
        }
        else if(attrName.compare(Z_ORDER_ATTR) == 0)
        {
            zOrder = static_cast<quint8>(attr.value().toInt());
            zOrderSet = GAME_TRUE;
        }
        else
        {
            qDebug() << "Unrecognized Frame Layer Attribute: " << attrName;
        }
    }

    if(zOrderSet && layerNameSet)
    {
        QSharedPointer<AnimationFrameLayer> frameLayer = QSharedPointer<AnimationFrameLayer>::create(layerName, zOrder);
        workingFrame->appendFrameLayer(frameLayer);
        workingFrameLayer = frameLayer;
    }
}

void FrameConfigurationLoader::processLayerImgTag()
{
    QStringRef attrName;

    GameBoolean objectKeySet = GAME_FALSE;
    GameBoolean imgNameSet = GAME_FALSE;
    QString objectKey = "";
    QString imgName = "";

    QXmlStreamAttributes attrs = xmlReader->attributes();
    for(QXmlStreamAttribute attr : attrs)
    {
        attrName = attr.name();

        if(attrName.compare(OBJECT_KEY_ATTR) == 0)
        {
            objectKey = attr.value().toString();
            objectKeySet = GAME_TRUE;
        }
        else if(attrName.compare(IMG_NAME_ATTR) == 0)
        {
            imgName = attr.value().toString();
            imgNameSet = GAME_TRUE;
        }
        else
        {
            qDebug() << "Unrecognized Layer Image Attribute: " << attrName;
        }
    }

    if(objectKeySet && imgNameSet)
    {
        if(itemRegestry->isItemRegestered(objectKey))
        {
            workingFrameLayer->insertFrameLayerImage(objectKey, imgName);
        }
        else
        {
            qDebug() << "Layer image belongs to unrecognized object: " << objectKey;
        }
    }
}


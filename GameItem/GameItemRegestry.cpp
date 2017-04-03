#include "GameItemRegestry.h"

#include <QDebug>

const QString GameItemRegestry::ITEM_TAG = QString("item");
const QString GameItemRegestry::OBJECT_KEY_ATTR = QString("object-key");

GameItemRegestry::GameItemRegestry(const QString &itemRegestryFileIn)
{
    itemRegestryFile = QSharedPointer<QFile>::create(itemRegestryFileIn);

    QScopedPointer<QXmlStreamReader> xmlReaderSwap(new QXmlStreamReader(itemRegestryFile.data()));
    xmlReader.swap(xmlReaderSwap);
}

GameItemRegestry::~GameItemRegestry()
{
    itemList.clear();
}

GameBoolean GameItemRegestry::loadItemRegestryFromXml()
{
    bool success = GAME_TRUE;

    if(!itemRegestryFile->open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open item regestry file";
        success = GAME_FALSE;
    }

    if(success)
    {
        while(!xmlReader->atEnd())
        {
            if(xmlReader->readNextStartElement())
            {
                if(xmlReader->name().compare(ITEM_TAG) == 0)
                {
                    QXmlStreamAttributes attrs = xmlReader->attributes();
                    for(QXmlStreamAttribute attr : attrs)
                    {
                        if(attr.name().compare(OBJECT_KEY_ATTR) == 0)
                        {
                            QSharedPointer<GameItem> gameItem = QSharedPointer<GameItem>::create(attr.value().toString());
                            if(!itemList.contains(*gameItem.data()))
                            {
                                itemList.append(*gameItem.data());
                            }
                            else
                            {
                                qDebug() << "item entry already exists, no duplicates!";
                            }
                        }
                        else
                        {
                            qDebug() << "item entry has no object key!";
                        }

                    }
                }
            }
        }
    }

    return success;
}

GameBoolean GameItemRegestry::isItemRegestered(const GameItem &itemIn)
{
    return itemList.contains(itemIn);
}

GameBoolean GameItemRegestry::isItemRegestered(const QString &itemIn)
{
    GameItem lookUpItem(itemIn);

    return itemList.contains(lookUpItem);
}

const QList<GameItem> GameItemRegestry::getItemList()
{
    return itemList;
}

#ifndef GAMEITEMREGESTRY_H
#define GAMEITEMREGESTRY_H

#include "GameItem.h"
#include "GameTypes.h"
#include <QList>
#include <QFile>
#include <QXmlStreamReader>
#include <QScopedPointer>
#include <QSharedPointer>

class GameItemRegestry
{
public:
    GameItemRegestry(const QString &itemRegestryFileIn);
    virtual ~GameItemRegestry();

    GameBoolean isItemRegestered(const GameItem &itemIn);
    GameBoolean isItemRegestered(const QString &itemIn);

    const QList<GameItem> getItemList();

    GameBoolean loadItemRegestryFromXml();

private:
    QList<GameItem> itemList;

    QScopedPointer<QXmlStreamReader> xmlReader; /*xml parser*/

    QSharedPointer<QFile> itemRegestryFile; /*file to be parsed*/

    static const QString ITEM_TAG;
    static const QString OBJECT_KEY_ATTR;

};

#endif // GAMEITEMREGESTRY_H

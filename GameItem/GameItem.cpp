#include "GameItem.h"

GameItem::GameItem(const QString &keyIn) : key(keyIn)
{
}

bool GameItem::operator ==(const GameItem &other)
{
    return QString::compare(this->key, other.key, Qt::CaseInsensitive) == 0;
}

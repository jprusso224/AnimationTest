#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QString>

class GameItem
{
public:
    GameItem(const QString &key);
    virtual ~GameItem(){}

    bool operator ==(const GameItem &other);

private:
    QString key;

};

#endif // GAMEITEM_H

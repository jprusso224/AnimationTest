#ifndef GAMETYPES_H
#define GAMETYPES_H

#include <QtGlobal>

typedef bool GameBoolean;
typedef quint8 Z_Order;

static const GameBoolean GAME_TRUE = true;
static const GameBoolean GAME_FALSE = false;

//TODO: Random Number Generator... What could go wrong.
static const GameBoolean GAME_MAYBE = false;
static const GameBoolean GAME_PROBABLY = true;
static const GameBoolean GAME_UNLIKELY = false;

enum class InputAction : quint8
{
    UNKNOWN = 0,
    EXIT,
    CHANGE_RACE,
    CHANGE_TORSO,
    CHANGE_LEGGINGS,
    CHANGE_FOOTWEAR,
    CHANGE_HANDWEAR,
    CHANGE_ITEM
};

#endif // GAMETYPES_H

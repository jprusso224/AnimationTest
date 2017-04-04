SDL_PATH = C:\SDL\SDL2-2.0.4
SDL_IMG_PATH = C:\SDL\SDL2_image-2.0.1
SDL_MIXER_PATH = C:\SDL\SDL2_mixer-2.0.1
SDL_GFX_PATH = C:\SDL\SDL2_gfx-1.0.1

QT += core xml

TEMPLATE = app
TARGET = AnimationTest
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += qt

INCLUDEPATH += $${SDL_PATH}\include \
            $${SDL_IMG_PATH}\include \
            $${SDL_MIXER_PATH}\include \
            $${SDL_GFX_PATH}

LIBS += -L$${SDL_PATH}\lib\x64 \
    -L$${SDL_IMG_PATH}\lib\x64 \
    -L$${SDL_MIXER_PATH}\lib\x64 \
    -lSDL2 \
    -lSDL2main \
    -lSDL2_image \
    -lSDL2_mixer

SOURCES += main.cpp \
    GameItem/GameItem.cpp \
    GameItem/GameItemRegestry.cpp \
    Animation/AnimationFrame.cpp \
    Animation/FrameConfigurationLoader.cpp \
    Animation/AnimationFrameLayer.cpp \
    ImageRenderer.cpp \
    Input/InputHandler.cpp \
    Utilities/GameTimer.cpp

HEADERS += \
    GameItem/GameItem.h \
    GameItem/GameItemRegestry.h \
    Animation/AnimationFrame.h \
    GameTypes.h \
    Animation/FrameConfigurationLoader.h \
    Animation/AnimationFrameLayer.h \
    ImageRenderer.h \
    Input/InputHandler.h \
    Utilities/GameTimer.h

DISTFILES += \
    Resources/ItemRegestry.xml \
    Resources/Animations.xml \
    Resources/Sprites/Player/ReadyWest/Ready_West_Basic_Boots.png \
    Resources/Sprites/Player/ReadyWest/Ready_West_Basic_Gloves.png \
    Resources/Sprites/Player/ReadyWest/Ready_West_Basic_Leggings.png \
    Resources/Sprites/Player/ReadyWest/Ready_West_Basic_Sword.png \
    Resources/Sprites/Player/ReadyWest/Ready_West_Basic_Torso.png \
    Resources/Sprites/Player/ReadyWest/Tonosian_Ready_West_Base.png

#include <QCoreApplication>

#include <windows.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <QDebug>
#include <QTimer>

#include "GameItem/GameItemRegestry.h"
#include "Animation/FrameConfigurationLoader.h"
#include "ImageRenderer.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    QString itemFileName("Resources\\ItemRegestry.xml");
    QString frameFileName("Resources\\Animations.xml");

    QSharedPointer<GameItemRegestry> itemRegestry = QSharedPointer<GameItemRegestry>::create(itemFileName);

    itemRegestry->loadItemRegestryFromXml();

    QSharedPointer<FrameConfigurationLoader> frameConfigLoader = QSharedPointer<FrameConfigurationLoader>::create(frameFileName, itemRegestry);

    frameConfigLoader->loadFramesFromXml();

    /*
     * Now lets try and draw a single animation frame...
     */

    SDL_Renderer *renderer = nullptr;

    GameBoolean sdlLoadSuccess = GAME_TRUE;

    if( SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        qDebug() << QString("SDL could not initialize! SDL_Error: %0").arg(SDL_GetError());
        sdlLoadSuccess = GAME_FALSE;
    }
    else
    {
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            qDebug() << QString("SDL_image could not initialize! SDL_image Error: %0").arg(IMG_GetError());
            sdlLoadSuccess = GAME_FALSE;
        }

        //Create window
        SDL_Window* window = SDL_CreateWindow( "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            qDebug() << QString("Window could not be created! SDL_Error: %0").arg(SDL_GetError());
            sdlLoadSuccess = GAME_FALSE;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  );
            if(renderer == nullptr)
            {
                qDebug() << QString("Failed to create renderer");
                sdlLoadSuccess = GAME_FALSE;
            }
            else
            {
                SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
            }
        }

        if(sdlLoadSuccess)
        {

            ImageRenderer *imgRenderer = new ImageRenderer(renderer);
            /*
             * Now its time to draw... Layer by layer, first img in each QHash.
             */
            const QList<QSharedPointer<AnimationFrame>> frameList = frameConfigLoader->getFrameList();
            const AnimationFrame frameToDraw = *frameList.constFirst().data();

            const QString frameImageLoc = frameToDraw.getImageLocation();

            const QList<QSharedPointer<AnimationFrameLayer>> layerList = frameToDraw.getFrameLayerList();

            for(QSharedPointer<AnimationFrameLayer> layer : layerList)
            {
                const QHash<QString, QString> imgLayerHash = layer.data()->getLayerImageHash();

                /*
                 * Determing equipment
                 */
                QString layerName = layer.data()->getLayerName();
                QString itemEquip = "";

                if(layerName.compare(QString("torso-layer")) == 0)
                {
                    itemEquip = QString("basic-armor");
                }
                else if (layerName.compare(QString("leg-layer")) == 0)
                {
                    itemEquip = QString("basic-leggings");
                }
                else if (layerName.compare(QString("feet-layer")) == 0)
                {
                    itemEquip = QString("basic-boots");
                }
                else if (layerName.compare(QString("hands-layer")) == 0)
                {
                    itemEquip = QString("basic-gloves");
                }
                else if (layerName.compare(QString("item-layer")) == 0)
                {
                    itemEquip = QString("basic-sword");
                }
                else if (layerName.compare(QString("race-layer")) == 0)
                {
                    itemEquip = QString("race-tonosian");
                }
                else
                {
                    //no-op
                }

                if(imgLayerHash.contains(itemEquip))
                {
                    QString imgNameToDraw = imgLayerHash.value(itemEquip);
                    QString imgPath = frameImageLoc + imgNameToDraw;

                    SDL_Texture* txt = imgRenderer->renderImage(imgPath);

                    if(txt != nullptr)
                    {
                            SDL_Rect srcRect;
                            srcRect.h = 32;
                            srcRect.w = 32;
                            srcRect.x = 0;
                            srcRect.y = 0;

                            SDL_Rect dstRect;
                            dstRect.h = 32;
                            dstRect.w = 32;
                            dstRect.x = 0;
                            dstRect.y = 0;

                            SDL_RenderCopy(renderer, txt, &srcRect, &dstRect);
                    }
                    else
                    {
                        qDebug() << IMG_GetError();
                    }

                }
            }

            SDL_RenderPresent( renderer );
            SDL_RenderClear( renderer );

            Sleep(3000);
        }

    }

    /*Goodbye*/
    SDL_Quit();
    IMG_Quit();

    return 0;
}

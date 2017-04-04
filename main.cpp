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
#include "Input/InputHandler.h"
#include "Utilities/GameTimer.h"
#include "ImageRenderer.h"

static const quint32 FRAME_RATE_MS = 300;
static const quint32 SCREEN_WIDTH = 500;
static const quint32 SCREEN_HEIGHT = 500;

QMap<Z_Order, SDL_Texture*> createTextureMapFromFrame(ImageRenderer* imgRenderer, const AnimationFrame &frame)
{

    QMap<Z_Order, SDL_Texture*> zOrderTextureMap;

    const QString frameImageLoc = frame.getImageLocation();

    const QList<QSharedPointer<AnimationFrameLayer>> layerList = frame.getFrameLayerList();

    for(QSharedPointer<AnimationFrameLayer> layer : layerList)
    {
        const QHash<QString, QString> imgLayerHash = layer.data()->getLayerImageHash();

        /*
         * Determing equipment
         */
        Z_Order zOrder = layer.data()->getZOrder();
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

            SDL_Texture* texture = imgRenderer->renderImage(imgPath);

            if(texture == nullptr)
            {
                qDebug() << IMG_GetError();
            }
            else
            {
                zOrderTextureMap.insert(zOrder, texture);
            }
        }
    }

    return zOrderTextureMap;
}

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
        SDL_Window* window = SDL_CreateWindow( "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

            InputHandler* inputHandler = new InputHandler();

            ImageRenderer *imgRenderer = new ImageRenderer(renderer);
            /*
             * Now its time to draw... Layer by layer, first img in each QHash.
             */
            const QList<QSharedPointer<AnimationFrame>> frameList = frameConfigLoader->getFrameList();

            quint8 numFrames = frameList.length();
            quint8 frameIdx = 0;

            /*Initialize game loop timer at fixed frame rate*/
            GameTimer gameUpdateTimer;
            gameUpdateTimer.start(FRAME_RATE_MS);
            quint64 currentTime_ms = SDL_GetTicks();
            quint64 elapsedTime_ms = 0;

            /********* THIS IS THE MAIN GAME LOOP ********************/
            qDebug() << QString("Entering main loop!");

            GameBoolean done = GAME_FALSE;
            while (!done)
            {
                // message processing
                InputAction input = inputHandler->processInput();
                if(input == InputAction::EXIT)
                {
                    done = GAME_TRUE;
                    break;
                }

                //compute elapsed time
                currentTime_ms = SDL_GetTicks();

                //always update the game loop timer!
                gameUpdateTimer.update(currentTime_ms - elapsedTime_ms);

                elapsedTime_ms = currentTime_ms;

                //Allow game to continue if game loop timer expires
                if(gameUpdateTimer.isExpired())
                {
                    //render the game
                    const QSharedPointer<AnimationFrame> frameToDraw = frameList.at(frameIdx);

                    QMap<Z_Order, SDL_Texture*> zOrderTextureMap = createTextureMapFromFrame(imgRenderer, *frameToDraw.data());

                    for(SDL_Texture* txt : zOrderTextureMap)
                    {
                        if(txt != nullptr)
                        {
                            SDL_Rect srcRect = {0,0,32,32};
                            SDL_Rect dstRect = {(SCREEN_WIDTH/2)-64,(SCREEN_HEIGHT/2)-64,64,64};
                            SDL_RenderCopy(renderer, txt, &srcRect, &dstRect);
                        }
                    }

                    SDL_RenderPresent( renderer );
                    SDL_RenderClear( renderer );

                    //restart the game loop timer
                    gameUpdateTimer.start(FRAME_RATE_MS);

                    //update frame Idx
                    frameIdx++;
                    if(frameIdx >= numFrames)
                    {
                        frameIdx = 0;
                    }
                }
            }
            /*********END MAIN LOOP***********************************/

            }
        }

    /*Goodbye*/
    SDL_Quit();
    IMG_Quit();

    return 0;
}

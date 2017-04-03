#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <QString>

class ImageRenderer
{
public:
    ImageRenderer(SDL_Renderer* rendererIn);

    SDL_Texture* renderImage(const QString &fileNameIn);

private:
    SDL_Renderer* renderer;
};

#endif // IMAGERENDERER_H

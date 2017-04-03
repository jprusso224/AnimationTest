#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(SDL_Renderer* rendererIn) : renderer(rendererIn)
{

}

SDL_Texture* ImageRenderer::renderImage(const QString &fileNameIn)
{
    return IMG_LoadTexture(renderer, fileNameIn.toStdString().c_str());
}

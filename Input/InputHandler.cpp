#include <QDebug>

#include "InputHandler.h"

InputHandler::InputHandler()
{
//no op
}

InputHandler::~InputHandler()
{
//no op
}

bool InputHandler::init()
{
   return true;
}

InputAction InputHandler::processInput()
{
   InputAction result = InputAction::UNKNOWN;
   SDL_Event event;

   SDL_PollEvent(&event);
   // check for messages
   switch (event.type)
   {
   case SDL_QUIT:
       result = InputAction::EXIT;
       break;

   // check for keypresses
   case SDL_KEYDOWN:
   {
       switch(event.key.keysym.sym)
       {
       case SDLK_ESCAPE:
           result = InputAction::EXIT;
           break;
       case SDLK_w:
       case SDLK_a:
       case SDLK_s:
       case SDLK_d:
           //Unimplemented.
           break;
       case SDLK_SPACE:
           //Unimplemented.
           break;
       case SDLK_1:
           result = InputAction::CHANGE_RACE;
           break;
       case SDLK_2:
           result = InputAction::CHANGE_TORSO;
           break;
       case SDLK_3:
           result = InputAction::CHANGE_LEGGINGS;
           break;
       case SDLK_4:
           result = InputAction::CHANGE_FOOTWEAR;
           break;
       case SDLK_5:
           result = InputAction::CHANGE_HANDWEAR;
           break;
       case SDLK_6:
           result = InputAction::CHANGE_ITEM;
           break;
       default:
           break;
       }
       break;
   }
   case SDL_KEYUP:
   {
       switch(event.key.keysym.sym)
       {
       case SDLK_w:
           //Unimplemented.
           break;
       case SDLK_a:
           //Unimplemented.
           break;
       case SDLK_s:
           //Unimplemented.
           break;
       case SDLK_d:
           //Unimplemented.
           break;
       case SDLK_SPACE:
           //Unimplemented.
           break;
       default:
           break;
       }
       break;
   }
   default:

       break;
   } // end switch

   return result;
}

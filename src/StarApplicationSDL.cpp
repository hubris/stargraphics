#include <StarGraphics/StarApplicationSDL.h>
#include <SDL.h>

#include <StarUtils/StarExceptions.h>

namespace Star
{
  /*******************************************************************************/
  ApplicationSDL::ApplicationSDL(int resx, int resy, const std::string& name,
                                 bool fullscreen)
    : Application(resx, resy, name, fullscreen)
  {
    if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_NOPARACHUTE) == -1 )
      throw SDLException("SDL init error: ");
  }

  /*******************************************************************************/
  void
  ApplicationSDL::setupVideo()
  {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int flags = SDL_OPENGL;
    if( m_fullscreen )
      flags |= SDL_FULLSCREEN;

    if(!SDL_SetVideoMode(m_width, m_height, 32, flags))
    {
      SDL_Quit();
      throw SDLException("Can't set video mode: ");
    }
  }

  /*******************************************************************************/
  void
  ApplicationSDL::exitVideo()
  {
    SDL_Quit();
  }

  /*******************************************************************************/
  void
  ApplicationSDL::swapBuffer()
  {
    SDL_GL_SwapBuffers();
  }

  /*******************************************************************************/
  void
  ApplicationSDL::processEvents()
  {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type){
      case SDL_QUIT:
        halt(0);
        break;
      case SDL_VIDEORESIZE:
      {
        resizeEvent(event.resize.w, event.resize.h);
        break;
      }
      }
    }
  }
}

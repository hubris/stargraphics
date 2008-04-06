#ifndef STARAPPLICATIONSDL_H
#define STARAPPLICATIONSDL_H

#include <StarGraphics/StarApplication.h>

namespace Star
{
  class ApplicationSDL : public Application
  {
  public:
    ApplicationSDL(int resx, int resy, const std::string& name, bool fullscreen = false);
    virtual ~ApplicationSDL() {}

  protected:
    /**
     * Render the frame
     * @param elapsedTime is the time in second neeeded to render last frame
     */
    virtual void render(float elapsedTime) = 0;

    /**
     * Create and display the screen
     */
    virtual void setupVideo();

    /**
     * Release all resources needed by screen
     */
    virtual void exitVideo();

    /**
     * Swap front & back buffer
     */
    virtual void swapBuffer();
  };
}

#endif

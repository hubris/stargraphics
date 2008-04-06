#ifndef EMPTYAPP_H
#define EMPTYAPP_H

#include <StarGraphics.h>

class EmptyApp : public Star::ApplicationSDL
{
public:
  EmptyApp(int resx, int resy, const std::string& name,
           bool fullscreen = false) : ApplicationSDL(resx, resy, name, fullscreen) {}

  void render(float elapsedTime);
};

#endif

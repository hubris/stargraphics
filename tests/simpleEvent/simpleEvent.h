#ifndef SIMPLEAPP_H
#define SIMPLEAPP_H

#include <StarGraphics.h>
#include <StarInput.h>

class SimpleEvent : public Star::ApplicationSDL, Star::MouseListener
{
public:
  SimpleEvent(int resx, int resy, const std::string& name,
              bool fullscreen = false);

  void render(float elapsedTime);

  virtual void mouseMoved(const Star::MouseMoveEvent& e);
};

#endif

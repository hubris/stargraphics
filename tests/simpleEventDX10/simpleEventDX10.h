#ifndef SIMPLEAPP_H
#define SIMPLEAPP_H

#include <StarGraphics.h>
#include <StarInput.h>

class SimpleEventDX10 : public Star::ApplicationDX10, Star::MouseListener
{
public:
  SimpleEventDX10(HINSTANCE hInst, int resx, int resy, const std::string& name,
                  bool fullscreen = false);

  void render(double elapsedTime);

  virtual void mouseMoved(const Star::MouseMoveEvent& e);
};

#endif

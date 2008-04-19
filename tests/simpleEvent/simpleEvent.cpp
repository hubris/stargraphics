#include "simpleEvent.h"

#include <GL/gl.h>

#include <iostream>

/******************************************************************************/
SimpleEvent::SimpleEvent(int resx, int resy, const std::string& name,
              bool fullscreen) : ApplicationSDL(resx, resy, name, fullscreen)
{
  g_StarMouse.addListener(this);
}

/******************************************************************************/
void
SimpleEvent::render(double elapsedTime)
{
   glClearColor(0, 1, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
}

/******************************************************************************/
void
SimpleEvent::mouseMoved(const Star::MouseMoveEvent& e)
{
  int x, y;
  int relX, relY;
  e.getPosition(x, y);
  e.getRelativePosition(relX, relY);
  std::cout << "Mouse position: " << x << " " << y << " ";
  std::cout << "Mouse relative move: " << relX << " " << relY << std::endl;
}

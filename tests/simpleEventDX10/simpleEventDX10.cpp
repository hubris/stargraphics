#include "simpleEventDX10.h"

#include <StarMath/StarVec4.h>

#include <iostream>

/******************************************************************************/
SimpleEventDX10::SimpleEventDX10(HINSTANCE hInst, int resx, int resy, 
                                 const std::string& name,
                                 bool fullscreen) 
 : ApplicationDX10(hInst, resx, resy, name, fullscreen)
{
  g_StarMouse.addListener(this);
}

/******************************************************************************/
void
SimpleEventDX10::render(double elapsedTime)
{  
  Star::float4 color(0.f, 1.f, 0.f, 1.f);  
  m_renderDeviceDX10->clearRenderTargetView(color);  
}

/******************************************************************************/
void
SimpleEventDX10::mouseMoved(const Star::MouseMoveEvent& e)
{
  int x, y;
  int relX, relY;
  e.getPosition(x, y);
  e.getRelativePosition(relX, relY);
  std::cout << "Mouse position: " << x << " " << y << " ";
  std::cout << "Mouse relative move: " << relX << " " << relY << std::endl;
}

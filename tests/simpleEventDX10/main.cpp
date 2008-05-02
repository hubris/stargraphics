#include "simpleEventDX10.h"

#include <StarUtils/StarExceptions.h>

Star::Application*
createApplication(int argc, char** argv, HINSTANCE hInst)
{ 
  return new SimpleEventDX10(hInst, 800, 600, "EmptyApp", true);   
}

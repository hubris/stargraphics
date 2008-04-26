#include "simpleEvent.h"

#include <StarUtils/StarExceptions.h>

Star::Application*
createApplication(int argc, char** argv, HINSTANCE hInst)
{ 
  return new SimpleEvent(800, 600, "EmptyApp");   
}
